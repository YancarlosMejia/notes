import java.util.*;

public class WLPPGen {

    Scanner in = new Scanner(System.in);
    boolean stateDCL = false;
    boolean stateTYPE = false;
    boolean stateNAME = false;
    HashMap<String, String> symbols = new HashMap<String, String>();
    String type;
    String name;
    HashMap<String, Integer> offset = new HashMap<String, Integer>();
    int framePointer = 0;
    int whileCount = 0;   
    int ifCount = 0;    

    // The set of terminal symbols in the WLPP grammar.
    Set<String> terminals = new HashSet<String>(Arrays.asList("BOF", "BECOMES", 
         "COMMA", "ELSE", "EOF", "EQ", "GE", "GT", "ID", "IF", "INT", "LBRACE", 
         "LE", "LPAREN", "LT", "MINUS", "NE", "NUM", "PCT", "PLUS", "PRINTLN",
         "RBRACE", "RETURN", "RPAREN", "SEMI", "SLASH", "STAR", "WAIN", "WHILE",
         "AMP", "LBRACK", "RBRACK", "NEW", "DELETE", "NULL"));

    Set<String> typed = new HashSet<String>(Arrays.asList("expr", "term", "factor", "test"));


    // Data structure for storing the parse tree.
    public class Tree {
        List<String> rule = new ArrayList<String>();

        ArrayList<Tree> children = new ArrayList<Tree>();

        // Does this node's rule match otherRule?
        boolean matches(String otherRule) {
            return tokenize(otherRule).equals(rule);
        }
    }

    // Divide a string into a list of tokens.
    List<String> tokenize(String line) {
        List<String> ret = new ArrayList<String>();
        ret = Arrays.asList(line.split(" "));
        return ret;
    }

    // Read and return wlppi parse tree
    Tree readParse(String lhs) {
        String line = in.nextLine();
        List<String> tokens = tokenize(line);
        addSymbol(tokens);
        Tree ret = new Tree();
        ret.rule = tokens;
        if (!terminals.contains(lhs)) {
            Scanner sc = new Scanner(line);
            sc.next(); // discard lhs
            while (sc.hasNext()) {
                String s = sc.next();
                ret.children.add(readParse(s));
            }
        }
        return ret;
    }

    public void addSymbol(List<String> tokens) {
        if(tokens.get(0).equals("dcl")){
            stateDCL = true;
            return;
        }
        else if (stateDCL) {
             if (tokens.get(0).equals("type")) {
                stateTYPE = true;
                stateDCL = false;
                if(tokens.size() > 2) {
                    type = "int*";
                }
                else {
                    type = "int";
                }
             }
            return;
        }
        else if (stateTYPE){
            if(tokens.get(0).equals("ID")){
                stateTYPE = false;
                name = tokens.get(1);
                if(symbols.containsKey(name)){
                    System.err.println("ERROR duplicate declaration " + name + " already exists");
                    System.exit(1);
                }
                symbols.put(name, type);
                return;
            }
        }
    }


    public String getNameLValue(Tree t) {
        if(t.rule.get(1).equals("ID")){
            return t.children.get(0).rule.get(1);
        }
        else if (t.rule.get(1).equals("STAR")){
            return getNameFactor(t.children.get(1));
        }
        else if(t.rule.get(1).equals("LPAREN")){
            return getNameLValue(t.children.get(1));
        }
        return "";
    }

    public String getNameFactor(Tree t) {
        if(t.rule.get(1).equals("ID")){
        System.out.println("baaaaaaaaaaaaaaaaaaaaaaaa");
            return t.children.get(0).rule.get(1);
        }
        else if(t.rule.get(1).equals("LPAREN")){
            return getNameExpr(t.children.get(1));
        }
        else if(t.rule.get(1).equals("AMP")) {
            return getNameLValue(t.children.get(1));
        }
        else if(t.rule.get(1).equals("STAR")) {
            return getNameFactor(t.children.get(1));
        }
        return "";
    }

    public String getNameExpr(Tree t) {
        return getNameTerm(t.children.get(0));
    }

    public String getNameTerm(Tree t) {
        return getNameFactor(t.children.get(0));
    }

    public void push(int a) {
        System.out.println("sw $" + a + ", -4($30)");
        System.out.println("sub $30, $30, $4");
    }

    public void pop(int a) {
        System.out.println("lw $" + a + ", 0($30)");
        System.out.println("add $30, $30, $4");
    }

    public void printDCLS (Tree t) {
        if(t.rule.size()<2) {
            return;
        }
        else if(t.rule.contains("NUM")){
            printDCLS(t.children.get(0));
            int val = Integer.parseInt(t.children.get(3).rule.get(1));
            String name = t.children.get(1).children.get(1).rule.get(1);
            System.out.println("lis $3");
            System.out.println(".word " + val);
            push(3);
            framePointer -= 4;
            offset.put(name, framePointer);
        }
        else if(t.rule.contains("NULL")){
            printDCLS(t.children.get(0));
            String name = t.children.get(1).children.get(1).rule.get(1);
            System.out.println("lis $3");
            System.out.println(".word 0");
            push(3);
            framePointer -= 4;
            offset.put(name, framePointer);
        }
    }

    public void printStatements (Tree t) {
        if(t.rule.size()<2) {
            return;
        }
        else if(t.rule.get(1).equals("statements")){
            printStatements(t.children.get(0));
            printStatement(t.children.get(1));
        }
    }   

    public String printTest (Tree t, String label) {
        printExpr(t.children.get(0));
        push(3);
        printExpr(t.children.get(2));
        pop(5);
        String name = getNameExpr(t.children.get(0));
        String type = symbols.get(name);
        if(t.rule.contains("EQ")) {
            if(type.equals("int")){
                System.out.println("slt $8, $3, $5");
                System.out.println("slt $9, $5, $3");
                System.out.println("add $6, $9, $8");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount;
            }
            else{
                System.out.println("sltu $8, $3, $5");
                System.out.println("sltu $9, $5, $3");
                System.out.println("add $6, $9, $8");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount;
            }
        }
        else if(t.rule.contains("NE")) {
            if(type.equals("int")){
                System.out.println("slt $8, $3, $5");
                System.out.println("slt $9, $5, $7");
                System.out.println("add $6, $9, $9");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;
            }
            else{
                System.out.println("sltu $8, $3, $5");
                System.out.println("sltu $9, $5, $7");
                System.out.println("add $6, $9, $9");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;
            }
        }
        else if(t.rule.contains("LT")) {
            if(type.equals("int")){
                System.out.println("slt $6, $5, $3");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;
            }
            else {
                System.out.println("sltu $6, $5, $3");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;
            }            
        }
        else if(t.rule.contains("LE")) {
            if(type.equals("int")){
                System.out.println("slt $6, $3, $5");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount; 
            }
            else {
                System.out.println("sltu $6, $3, $5");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount;
            }
        }
        else if(t.rule.contains("GE")) {
            if(type.equals("int")){
                System.out.println("slt $3, $5, $3");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount;
            }
            else {
                System.out.println("sltu $3, $5, $3");
                System.out.println("bne $6, $0, " + label);
                return "beq $6, $0, endElse" + ifCount;
            }
        }
        else if(t.rule.contains("GT")) {
            if(type.equals("int")){    
                System.out.println("slt $3, $3, $5");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;                
            }
            else {
                System.out.println("sltu $3, $3, $5");
                System.out.println("beq $6, $0, " + label);
                return "bne $6, $0, endElse" + ifCount;                
            }
        }
        return "";
    }

    public String startsWith (Tree t) {
        if(t.rule.get(1).equals("LPAREN")) {
            return startsWith(t.children.get(1));
        }
        else {
            return t.rule.get(1);
        }
    }


    public void printStatement (Tree t) {
        if(t.rule.get(1).equals("PRINTLN")){
            printExpr(t.children.get(2));
            System.out.println("add $1, $3, $0");
            push(31);
            System.out.println("jalr $28");
            pop(31);
        }
        else if(t.rule.get(1).equals("lvalue")) {
            if(startsWith(t.children.get(0)).equals("STAR")){
                printLValue(t.children.get(0));
                push(3);
                printExpr(t.children.get(2));
                pop(5);
                System.out.println("sw $3, 0($5)");

            /*String name = getNameLValue(t.children.get(0));
            int off = offset.get(name);
            String type = symbols.get(name);
            if(startsWith(t.children.get(0)).equals("STAR")){
                System.out.println("lis $5");
                System.out.println(".word " + off);
                System.out.println("add $5, $5, $29");
                System.out.println("lw $8, 0($5)");
                printExpr(t.children.get(2));
                System.out.println("sw $3, 0($8)");
            }*/
            }
            else {
                printExpr(t.children.get(2));
                System.out.println("sw $3, " + offset.get(name) + "($29)");
            }
        }

        else if(t.rule.get(1).equals("WHILE")) {
            whileCount +=1;
            System.out.println("beginWhile" + whileCount + ":");
            printTest(t.children.get(2), "endWhile");
            printStatements(t.children.get(5));
            System.out.println("beq $0, $0, beginWhile" + whileCount);
            System.out.println("endWhile" + whileCount + ":");
            whileCount -=1;
        }
        else if(t.rule.get(1).equals("IF")) {
            ifCount += 1;
            String end = printTest(t.children.get(2), "endIf");
            printStatements(t.children.get(5));
            System.out.println("endIf" + ifCount + ":");
            System.out.println(end);
            printStatements(t.children.get(9));
            System.out.println("endElse" + ifCount + ":");  
            ifCount -= 1;            
        }
        else if(t.rule.get(1).equals("DELETE")) {
            printExpr(t.children.get(3));
            System.out.println("add $1, $3, $0");
            push(31);
            System.out.println("jalr $26");
            pop(31);
        }

    }

    public void printID (Tree t) {
        String id = t.rule.get(1);
        int off = offset.get(id);
        System.out.println("lw $3, " + off + "($29)");

    }

    public void printLValue(Tree t) {
        if(t.rule.get(1).equals("ID")) {
            printID(t.children.get(0));
        }
        else if(t.rule.get(1).equals("LPAREN")) {
            printLValue(t.children.get(1));
        }
        else if (t.rule.get(1).equals("STAR")) {
            printFactor(t.children.get(1));
            System.out.println("lw $3, 0($3)");
        }
    }


    public void printFactor(Tree t) {
        if(t.rule.get(1).equals("ID")) {
           printID(t.children.get(0));
        }
        else if (t.rule.get(1).equals("LPAREN")){
            printExpr(t.children.get(1));
        }
       else if(t.rule.get(1).equals("NUM")){
            System.out.println("lis $3");
            System.out.println(".word " + t.children.get(0).rule.get(1));
        }
        else if(t.rule.get(1).equals("NULL")){
            System.out.println("lis $3");
            System.out.println(".word 0");
        }
        else if(t.rule.get(1).equals("AMP")){
            printLValue(t.children.get(1));
            String name = getNameLValue(t.children.get(1));
            int off = offset.get(name);
            System.out.println("lis $3");
            System.out.println(".word " + off);
            System.out.println("add $3, $29, $3");

        }
        else if(t.rule.get(1).equals("STAR")) {
            printFactor(t.children.get(1));
            System.out.println("lw $3, 0($3)");
        }
        else if(t.rule.get(1).equals("NEW")) {
            printExpr(t.children.get(3));
            System.out.println("add $1, $3, $0");
            push(31);
            System.out.println("jalr $27");
            pop(31);
        }

    }

    public void printTerm (Tree t) {
        if(t.rule.get(1).equals("factor")) {
            printFactor(t.children.get(0));
        }
        else {
            printTerm(t.children.get(0));
            push(3);
            printFactor(t.children.get(2));
            pop(5);
            if(t.rule.get(2).equals("STAR")) {
                System.out.println("multu $3, $5");
                System.out.println("mflo $3");
            }
            else if (t.rule.get(2).equals("SLASH")) {
                System.out.println("divu $5, $3");
                System.out.println("mflo $3");
            }
            else{
                System.out.println("divu $5, $3");
                System.out.println("mfhi $3");            
            }
        }
    }

    public void printExpr(Tree t) {
        if(t.rule.get(1).equals("term")) {
            printTerm(t.children.get(0));
        }
        else {
            printExpr(t.children.get(0));
            push(3);
            String name1 = getNameExpr(t.children.get(0));  
            String name2 = getNameTerm(t.children.get(2));
System.out.println(name2);
            if(symbols.get(name1).equals("int*") || symbols.get(name2).equals("int*")){
                if(symbols.get(name1).equals("int")) {
                    System.out.println("mult $3, $4");
                    System.out.println("mflo $3");
                }
                printTerm(t.children.get(2));
                if(symbols.get(name2).equals("int")) {
                    System.out.println("mult $3, $4");
                    System.out.println("mflo $3");
                }
                pop(5);
            }
            else {
            
                printTerm(t.children.get(2));
                pop(5);
            }
            if(t.rule.get(2).equals("PLUS")) {
                System.out.println("add $3, $5, $3");
            }
            else{ 
                System.out.println("sub $3, $5, $3");
            }
        }
    }

    public void print(Tree t) { 
        System.out.println(".import print");
        System.out.println(".import new");
        System.out.println(".import init");
        System.out.println(".import delete");
        System.out.println("add $29, $30, $0");
        System.out.println("lis $4");
        System.out.println(".word 4");
        System.out.println("lis $11");
        System.out.println(".word 1");
        System.out.println("lis $28");
        System.out.println(".word print");
        System.out.println("lis $27");
        System.out.println(".word new");
        System.out.println("lis $26");
        System.out.println(".word delete");
        push(1);
        String a = t.children.get(3).children.get(1).rule.get(1);
        framePointer -= 4;
        offset.put(a, framePointer);
        push(2);
        String b = t.children.get(5).children.get(1).rule.get(1);
        framePointer -= 4;    
        offset.put(b, framePointer);
        if(symbols.get(a).equals("int")) {
            System.out.println("add $2, $0, $0");
        }
        push(31);
        System.out.println("lis $3");
        System.out.println(".word init");
        System.out.println("jalr $3");
        pop(31);
        printDCLS(t.children.get(8));
        printStatements(t.children.get(9));
        printExpr(t.children.get(11));  
        System.out.println("jr $31");
    }

    // Main program
    public static final void main(String args[]) {
        new WLPPGen().go();
    }

    public void go() {
        Tree s = readParse("S");
        print(s.children.get(1));
    }
}