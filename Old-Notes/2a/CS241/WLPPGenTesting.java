import java.util.*;

public class WLPPGenTesting {

    Scanner in = new Scanner(System.in);
    boolean stateDCL = false;
    boolean stateTYPE = false;
    boolean stateNAME = false;
    HashMap<String, String> symbols = new HashMap<String, String>();
    String type;
    String name;
    

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
    public boolean checkIDs(Tree t) {
        if(t.rule.get(0).equals("ID")) {
            if(!symbols.containsKey(t.rule.get(1))) {
                System.err.println("ERROR " + t.rule.get(1) + " isnt declared");
                System.exit(1);
            }
        }
        else {
            for(Tree s : t.children) {
                checkIDs(s);
            }
        }
        return true;
    }


    public boolean checkDCLS(Tree t) {
        System.err.print("checkDCLS ");
        for(String b : t.rule) {
            System.err.print(b + " ");
        }
        System.err.println("");
        if(t.rule.size()<2) {
            return true;
        }
        else{
            String a = getTypeDCL(t.children.get(1));
            boolean b = checkDCLS(t.children.get(0));
            if(t.rule.contains("NUM")) {
                return a.equals("int") && b;
            }
            else if(t.rule.contains("NULL")) {
                return a.equals("int*") && b;
            }
            else {
                System.err.println("Something broke dcls");
                System.exit(1);
            }
        }
        return false;
    }

    public boolean checkStatements(Tree t) {
        if(t.rule.size()<2){
            return true;
        }
        else {
            return (checkStatements(t.children.get(0)) && checkStatement(t.children.get(1)));
        }
    }

    public boolean checkStatement(Tree t) {
        System.err.println("");
        System.err.println("checkStatements ");
        for(String s: t.rule){
            System.err.print(s + " ");
        }
        System.err.println(" ");
        if(t.rule.get(1).equals("lvalue")) {
            String a = getTypeLValue(t.children.get(0));
            String b = getTypeExpr(t.children.get(2));
            return a.equals(b);
        }
        else if(t.rule.get(1).equals("IF")) {
            return checkTest(t.children.get(2)) && checkStatements(t.children.get(5)) && checkStatements(t.children.get(9));
        }
        else if(t.rule.get(1).equals("WHILE")) {
            return checkTest(t.children.get(2)) && checkStatements(t.children.get(5));
        }
        else if(t.rule.get(1).equals("PRINTLN")) {
            return getTypeExpr(t.children.get(2)).equals("int");
        }
        else if(t.rule.get(1).equals("DELETE")) {
            return getTypeExpr(t.children.get(3)).equals("int*");
        }
        else {
            System.err.println("Something broke");
            System.exit(1);
        }
        return false;
    }

    public boolean checkTest(Tree t) {
        String a = getTypeExpr(t.children.get(0));
        String b = getTypeExpr(t.children.get(2));
        if(!a.equals(b)) {
            System.err.println("ERROR: TEST " + a + " isnt " + b);
            System.exit(1);
            return false;
        }
        else {
            return true;       
        }
    }
    
    public String getTypeDCL(Tree t) {
        System.err.print("getTypeDCL ");
            for(String s : t.rule){
                System.err.print(s + " ");
            }
            System.err.println("");
        return getTypeType(t.children.get(0));
    }

    public String getTypeExpr(Tree t) {
        System.err.print("getTypeExpr ");
                    for(String s : t.rule){
                System.err.print(s + " ");
            }
            System.err.println("");
        if(t.rule.get(1).equals("term")) {
            return getTypeTerm(t.children.get(0));
        }
        else {
            String a = getTypeExpr(t.children.get(0));
            String b = getTypeTerm(t.children.get(2));
            if(t.rule.get(1).equals("PLUS")){
                if(a.equals("int*") && b.equals("int*")) {
                    System.err.println("ERROR EXPR+");
                    System.exit(1);
                }
                else if (a.equals("int") && b.equals("int")) {
                    return "int";
                }
                else {
                    return "int*";
                }
            }
            else {
                if(a.equals("int") && b.equals("int*")) {
                    System.err.println("ERROR EXPR-");
                }
                else if (a.equals("int*") && b.equals("int")) {
                    return "int*";
                }
                else {
                    return "int";
                }
            }
        }
        return "";
    }


    public String getTypeTerm(Tree t) {
        System.err.print("getTypeTerm ");
                    for(String s : t.rule){
                System.err.print(s + " ");
            }
            System.err.println("");
        if(t.rule.get(1).equals("factor")) {
            return getTypeFactor(t.children.get(0));
        }
        else {
            String a = getTypeTerm(t.children.get(0));
            String b = getTypeFactor(t.children.get(2));
            if(a.equals("int*") || b.equals("int*")) {
                System.err.println("ERROR TERM: " + a + " " + b);
                System.exit(1);
            }
            return "int";   
        }
    }

    public String getTypeFactor(Tree t){
                    System.err.print("getTypeFactor ");
        for(String s : t.rule){
                System.err.print(s + " ");
            }
                        System.err.println("");

        if(t.rule.get(1).equals("ID")) {
            return getTypeID(t.children.get(0));
        }
        else if (t.rule.get(1).equals("NUM")) {
            return "int";
        }
        else if (t.rule.get(1).equals("NULL")) {
            return "int*";
        }
        else if (t.rule.get(1).equals("LPAREN")) {
            return getTypeExpr(t.children.get(1));
        }
        else if (t.rule.get(1).equals("AMP")) {
            String a = getTypeLValue(t.children.get(1));
            if(a.equals("int*")) {
                System.err.println("ERROR AMP:");
                System.exit(1);
            }
            else {
                return "int*";
            }
        }
        else if(t.rule.get(1).equals("STAR")) {
            String a = getTypeFactor(t.children.get(1));
            if(a.equals("int")) {
                System.err.println("ERROR * factor");
                System.exit(1);
            }
            else {
                return "int";
            }
        }
        else if(t.rule.get(1).equals("NEW")) {
            String a = getTypeExpr(t.children.get(3));
            if(!a.equals("int")) {
                System.err.println("ERROR new int []");
                System.exit(1);
            }
            else {
                return "int*";
            }
        }
        else{
            System.err.println("Something broke factor");
            System.exit(1);
        }
        return "";
    }

    public String getTypeLValue(Tree t) {
        System.err.print("getTypeLValue ");

        for(String s : t.rule) {
            System.err.print(s + " ");
        }
        System.err.println("");
        if(t.rule.get(1).equals("ID")) {
            return getTypeID(t.children.get(0));
        }
        else if (t.rule.get(1).equals("STAR")) {
            String a = getTypeFactor(t.children.get(1));
            if(a.equals("int")) {
                System.err.println("ERROR STAR factor");
                System.exit(1);
            }
            else {
                return "int";
            }
        }
        else if (t.rule.get(1).equals("LPAREN")) {
            return getTypeLValue(t.children.get(1));
        }
        else {
            System.err.println("Something broke lvalue");
            System.exit(1);
        }
        return "";
    }

    public String getTypeType(Tree t) {
        System.err.print("getTypeType ");

        for(String s : t.rule){
                System.err.print(s + " ");
            }
                    System.err.println("");
        if(t.rule.size() > 2) {
            return "int*";
        }
        else{
            return "int";
        }
    }

    public String getTypeID(Tree t) {
        System.err.print("getTypeID ");

        for(String s : t.rule){
                System.err.print(s + " ");
            }
        System.err.println("");
        System.err.println(t.rule.get(1) + " = " + symbols.get(t.rule.get(1)));

        return symbols.get(t.rule.get(1));
    }

    // Main program
    public static final void main(String args[]) {
        new WLPPGenTesting().go();
    }

    public void go() {
        Tree s = readParse("S");
        checkIDs(s);
        s = s.children.get(1);
        System.err.println("");
        System.err.println("CHECKING 5 DCL");
        boolean a = getTypeDCL(s.children.get(5)).equals("int");
        System.err.println("");
        System.err.println("CHECKING 8 DCLS");
        boolean b = checkDCLS(s.children.get(8));
        System.err.println("");
        System.err.println("CHECKING 9 STATEMENTS");
        boolean c = checkStatements(s.children.get(9));
        System.err.println("");        
        System.err.println("CHECKING 11 EXPR");
        boolean d = getTypeExpr(s.children.get(11)).equals("int");
        System.err.println(a + " " + b + " " + c + " " + d);
        if(a && b && c && d) {
            for (Map.Entry<String, String> entry : symbols.entrySet()) {
                System.err.println(entry.getKey() + " " + entry.getValue());
            }
        }
        else {
            System.err.println("ERROR some type is wrong");
            System.exit(1);
        }
    }
}