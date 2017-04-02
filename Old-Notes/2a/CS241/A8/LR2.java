import java.util.*;
import java.io.*;

public class LR2 {
    public static void main(String[] args){
        new LR2().run();
    }
    ArrayList<String> terms = new ArrayList<String>();
    ArrayList<String> nonterms = new ArrayList<String>();
    ArrayList<String> prods = new ArrayList<String>();
    ArrayList<Transition> table = new ArrayList<Transition>();
    ArrayList<Token> input = new ArrayList<Token>();
    ArrayList<String> rhderiv = new ArrayList<String>();
    String start = "S";

    
    public void run(){
        getTerms(); 
        getNonTerms();
        getProds();
        getTable();
        getInput();
        rhderiv = getRightDerivation();
        Tree t = lrdo();
        traverse(t);
    }  
    
    public class Tree {
        String rule;
        LinkedList<Tree> children = new LinkedList<Tree>();
    }


    // output leftmost derivation of tree t with indentation d
    public void traverse(Tree t) {
        System.out.println(t.rule); // print root
        String[] chunked = t.rule.split(" ");
        for(int i = 1; i < chunked.length; i++) {
            if(terms.contains(chunked[i])){
                System.out.println(chunked[i] + " " + input.get(0).lexeme);
                input.remove(0);
            }
            else {
                traverse(t.children.getFirst());
                t.children.remove();                
            }
        }

    }

    // pop rhs and accumulate subtress, push new tree node
    public void popper(Stack<Tree> stack, List<String> rhs, String rule) {
        Tree n = new Tree();
        n.rule = rule;
        for(String s : rhs) {
            n.children.addFirst(stack.pop());
        }
        stack.push(n);
    }

    // build tree from remaining input
    public Tree lrdo() {
        Stack<Tree> stack = new Stack<Tree>();
        String l; // lhs symbol
        for(String f : rhderiv) {
            List<String> r = new ArrayList<String>(); // rhs symbols
            Scanner sc = new Scanner(f);
            l = sc.next(); // lhs symbol
            while(sc.hasNext()) {
                String s = sc.next();
                if(nonterms.contains(s)) r.add(s); // only non-terms
            }
            popper(stack, r, f); // reduce rule
            if(start.equals(l)) { break; }
        }
        return stack.peek();
    }   

    public ArrayList<String> getRightDerivation (){
        Stack<Integer> state = new Stack<Integer>();
        Stack<String> symbol = new Stack<String>();
        ArrayList<String> print = new ArrayList<String>();
        state.push(0);
        symbol.push("BOF");
        for(int i = 0; i<input.size(); i++) {
            try {
                Transition next = findTransition(state.peek(), input.get(i).type, table);
                if(next.type.equals("SHIFT")) {
                    symbol.push(next.stuff);
                    state.push(next.toState);
                }
                else{
                    String [] change = prods.get(next.toState).split(" ");
                    for(int j = 0; j < change.length-1; j++){
                        symbol.pop();
                        state.pop();
                    }
                    print.add(prods.get(next.toState));
                    symbol.push(change[0]);
                    state.push(findTransition(state.peek(), change[0], table).toState);


                    while(findTransition(state.peek(), input.get(i).type, table).type.equals("REDUCE")){
                        next = findTransition(state.peek(), input.get(i).type, table);
                        change = prods.get(next.toState).split(" ");
                        for(int j = 0; j < change.length-1; j++){
                            symbol.pop();
                            state.pop();
                        }
                        print.add(prods.get(next.toState));
                        symbol.push(change[0]);
                        state.push(findTransition(state.peek(), change[0], table).toState);

                    }
                    next = findTransition(state.peek(), input.get(i).type, table);
                    symbol.push(next.stuff);
                    state.push(next.toState);
                }

            }
            catch (Exception e) {
                int line = i + 1;
                System.err.println("ERROR at " + line + " " + state.peek() + input.get(i).type);
                System.exit(0);
            }
        }
        print.add("S BOF procedure EOF");
        return print;
    }

    public class Transition {
        int fromState;
        String stuff;
        String type;
        int toState;
        Transition(int fromState, String stuff, int toState, String type) {
            this.fromState = fromState;
            this.stuff = stuff;
            this.type = type;
            this.toState = toState;
        }
    }
    public Transition findTransition(int state, String blah, ArrayList<Transition> table) {
        for( int j = 0; j < table.size(); j++) {
            Transition t = table.get(j);
            if(t.fromState == state && t.stuff.equals(blah)) {
                return t;
            }
        }
        return null;
    }
    public class Token {
        String type;
        String lexeme;
        Token(String type, String lexeme){
            this.type =type;
            this.lexeme = lexeme;
        }
    }
    public void getInput(){
        input.add(new Token("BOF", "BOF"));
        Scanner in  = new Scanner(System.in);
        while(in.hasNext()){
            String [] temp = in.nextLine().split(" ");
            input.add(new Token (temp[0], temp[1]));
        } 
        input.add(new Token ("EOF", "EOF"));
    } 


    public void getTerms() {
        terms.add("AMP");
        terms.add("BECOMES");
        terms.add("BOF");
        terms.add("COMMA");
        terms.add("DELETE");
        terms.add("ELSE");
        terms.add("EOF");
        terms.add("EQ");
        terms.add("GE");
        terms.add("GT");
        terms.add("ID");
        terms.add("IF");
        terms.add("INT");
        terms.add("LBRACE");
        terms.add("LBRACK");
        terms.add("LE");
        terms.add("LPAREN");
        terms.add("LT");
        terms.add("MINUS");
        terms.add("NE");
        terms.add("NEW");
        terms.add("NULL");
        terms.add("NUM");
        terms.add("PCT");
        terms.add("PLUS");
        terms.add("PRINTLN");
        terms.add("RBRACE");
        terms.add("RBRACK");
        terms.add("RETURN");
        terms.add("RPAREN");
        terms.add("SEMI");
        terms.add("SLASH");
        terms.add("STAR");
        terms.add("WAIN");
        terms.add("WHILE");
    }

    public void getNonTerms() {
        nonterms.add("dcl");
        nonterms.add("dcls");
        nonterms.add("expr");
        nonterms.add("factor");
        nonterms.add("lvalue");
        nonterms.add("procedure");
        nonterms.add("statement");
        nonterms.add("statements");
        nonterms.add("term");
        nonterms.add("test");
        nonterms.add("type");
    }

    public void getProds(){
        prods.add("S BOF procedure EOF");
        prods.add("procedure INT WAIN LPAREN dcl COMMA dcl RPAREN LBRACE dcls statements RETURN expr SEMI RBRACE");
        prods.add("type INT");
        prods.add("type INT STAR");
        prods.add("dcls");
        prods.add("dcls dcls dcl BECOMES NUM SEMI");
        prods.add("dcls dcls dcl BECOMES NULL SEMI");
        prods.add("dcl type ID");
        prods.add("statements");
        prods.add("statements statements statement");
        prods.add("statement lvalue BECOMES expr SEMI");
        prods.add("statement IF LPAREN test RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE");
        prods.add("statement WHILE LPAREN test RPAREN LBRACE statements RBRACE");
        prods.add("statement PRINTLN LPAREN expr RPAREN SEMI");
        prods.add("statement DELETE LBRACK RBRACK expr SEMI");
        prods.add("test expr EQ expr");
        prods.add("test expr NE expr");
        prods.add("test expr LT expr");
        prods.add("test expr LE expr");
        prods.add("test expr GE expr");
        prods.add("test expr GT expr");
        prods.add("expr term");
        prods.add("expr expr PLUS term");
        prods.add("expr expr MINUS term");
        prods.add("term factor");
        prods.add("term term STAR factor");
        prods.add("term term SLASH factor");
        prods.add("term term PCT factor");
        prods.add("factor ID");
        prods.add("factor NUM");
        prods.add("factor NULL");
        prods.add("factor LPAREN expr RPAREN");
        prods.add("factor AMP lvalue");
        prods.add("factor STAR factor");
        prods.add("factor NEW INT LBRACK expr RBRACK");
        prods.add("lvalue ID");
        prods.add("lvalue STAR factor");
        prods.add("lvalue LPAREN lvalue RPAREN");
    }

    public void getTable (){

        table.add(new Transition(0, "BOF", 99, "SHIFT"));
        table.add(new Transition(1, "BECOMES", 29, "REDUCE"));
        table.add(new Transition(1, "EQ", 29, "REDUCE"));
        table.add(new Transition(1, "GE", 29, "REDUCE"));
        table.add(new Transition(1, "GT", 29, "REDUCE"));
        table.add(new Transition(1, "LE", 29, "REDUCE"));
        table.add(new Transition(1, "LT", 29, "REDUCE"));
        table.add(new Transition(1, "MINUS", 29, "REDUCE"));
        table.add(new Transition(1, "NE", 29, "REDUCE"));
        table.add(new Transition(1, "PCT", 29, "REDUCE"));
        table.add(new Transition(1, "PLUS", 29, "REDUCE"));
        table.add(new Transition(1, "RBRACK", 29, "REDUCE"));
        table.add(new Transition(1, "RPAREN", 29, "REDUCE"));
        table.add(new Transition(1, "SEMI", 29, "REDUCE"));
        table.add(new Transition(1, "SLASH", 29, "REDUCE"));
        table.add(new Transition(1, "STAR", 29, "REDUCE"));
        table.add(new Transition(10, "DELETE", 11, "REDUCE"));
        table.add(new Transition(10, "ID", 11, "REDUCE"));
        table.add(new Transition(10, "IF", 11, "REDUCE"));
        table.add(new Transition(10, "LPAREN", 11, "REDUCE"));
        table.add(new Transition(10, "PRINTLN", 11, "REDUCE"));
        table.add(new Transition(10, "RBRACE", 11, "REDUCE"));
        table.add(new Transition(10, "RETURN", 11, "REDUCE"));
        table.add(new Transition(10, "STAR", 11, "REDUCE"));
        table.add(new Transition(10, "WHILE", 11, "REDUCE"));
        table.add(new Transition(100, "DELETE", 8, "REDUCE"));
        table.add(new Transition(100, "ID", 8, "REDUCE"));
        table.add(new Transition(100, "IF", 8, "REDUCE"));
        table.add(new Transition(100, "LPAREN", 8, "REDUCE"));
        table.add(new Transition(100, "PRINTLN", 8, "REDUCE"));
        table.add(new Transition(100, "RBRACE", 8, "REDUCE"));
        table.add(new Transition(100, "RETURN", 8, "REDUCE"));
        table.add(new Transition(100, "STAR", 8, "REDUCE"));
        table.add(new Transition(100, "statements", 72, "SHIFT"));
        table.add(new Transition(100, "WHILE", 8, "REDUCE"));
        table.add(new Transition(101, "DELETE", 8, "REDUCE"));
        table.add(new Transition(101, "ID", 8, "REDUCE"));
        table.add(new Transition(101, "IF", 8, "REDUCE"));
        table.add(new Transition(101, "LPAREN", 8, "REDUCE"));
        table.add(new Transition(101, "PRINTLN", 8, "REDUCE"));
        table.add(new Transition(101, "RBRACE", 8, "REDUCE"));
        table.add(new Transition(101, "RETURN", 8, "REDUCE"));
        table.add(new Transition(101, "STAR", 8, "REDUCE"));
        table.add(new Transition(101, "statements", 71, "SHIFT"));
        table.add(new Transition(101, "WHILE", 8, "REDUCE"));
        table.add(new Transition(103, "DELETE", 8, "REDUCE"));
        table.add(new Transition(103, "ID", 8, "REDUCE"));
        table.add(new Transition(103, "IF", 8, "REDUCE"));
        table.add(new Transition(103, "LPAREN", 8, "REDUCE"));
        table.add(new Transition(103, "PRINTLN", 8, "REDUCE"));
        table.add(new Transition(103, "RBRACE", 8, "REDUCE"));
        table.add(new Transition(103, "RETURN", 8, "REDUCE"));
        table.add(new Transition(103, "STAR", 8, "REDUCE"));
        table.add(new Transition(103, "statements", 73, "SHIFT"));
        table.add(new Transition(103, "WHILE", 8, "REDUCE"));
        table.add(new Transition(104, "RBRACK", 27, "SHIFT"));
        table.add(new Transition(105, "DELETE", 10, "REDUCE"));
        table.add(new Transition(105, "ID", 10, "REDUCE"));
        table.add(new Transition(105, "IF", 10, "REDUCE"));
        table.add(new Transition(105, "LPAREN", 10, "REDUCE"));
        table.add(new Transition(105, "PRINTLN", 10, "REDUCE"));
        table.add(new Transition(105, "RBRACE", 10, "REDUCE"));
        table.add(new Transition(105, "RETURN", 10, "REDUCE"));
        table.add(new Transition(105, "STAR", 10, "REDUCE"));
        table.add(new Transition(105, "WHILE", 10, "REDUCE"));
        table.add(new Transition(106, "DELETE", 14, "REDUCE"));
        table.add(new Transition(106, "ID", 14, "REDUCE"));
        table.add(new Transition(106, "IF", 14, "REDUCE"));
        table.add(new Transition(106, "LPAREN", 14, "REDUCE"));
        table.add(new Transition(106, "PRINTLN", 14, "REDUCE"));
        table.add(new Transition(106, "RBRACE", 14, "REDUCE"));
        table.add(new Transition(106, "RETURN", 14, "REDUCE"));
        table.add(new Transition(106, "STAR", 14, "REDUCE"));
        table.add(new Transition(106, "WHILE", 14, "REDUCE"));
        table.add(new Transition(11, "BECOMES", 30, "REDUCE"));
        table.add(new Transition(11, "EQ", 30, "REDUCE"));
        table.add(new Transition(11, "GE", 30, "REDUCE"));
        table.add(new Transition(11, "GT", 30, "REDUCE"));
        table.add(new Transition(11, "LE", 30, "REDUCE"));
        table.add(new Transition(11, "LT", 30, "REDUCE"));
        table.add(new Transition(11, "MINUS", 30, "REDUCE"));
        table.add(new Transition(11, "NE", 30, "REDUCE"));
        table.add(new Transition(11, "PCT", 30, "REDUCE"));
        table.add(new Transition(11, "PLUS", 30, "REDUCE"));
        table.add(new Transition(11, "RBRACK", 30, "REDUCE"));
        table.add(new Transition(11, "RPAREN", 30, "REDUCE"));
        table.add(new Transition(11, "SEMI", 30, "REDUCE"));
        table.add(new Transition(11, "SLASH", 30, "REDUCE"));
        table.add(new Transition(11, "STAR", 30, "REDUCE"));
        table.add(new Transition(12, "BECOMES", 28, "REDUCE"));
        table.add(new Transition(12, "EQ", 28, "REDUCE"));
        table.add(new Transition(12, "GE", 28, "REDUCE"));
        table.add(new Transition(12, "GT", 28, "REDUCE"));
        table.add(new Transition(12, "LE", 28, "REDUCE"));
        table.add(new Transition(12, "LT", 28, "REDUCE"));
        table.add(new Transition(12, "MINUS", 28, "REDUCE"));
        table.add(new Transition(12, "NE", 28, "REDUCE"));
        table.add(new Transition(12, "PCT", 28, "REDUCE"));
        table.add(new Transition(12, "PLUS", 28, "REDUCE"));
        table.add(new Transition(12, "RBRACK", 28, "REDUCE"));
        table.add(new Transition(12, "RPAREN", 28, "REDUCE"));
        table.add(new Transition(12, "SEMI", 28, "REDUCE"));
        table.add(new Transition(12, "SLASH", 28, "REDUCE"));
        table.add(new Transition(12, "STAR", 28, "REDUCE"));
        table.add(new Transition(13, "AMP", 26, "SHIFT"));
        table.add(new Transition(13, "expr", 89, "SHIFT"));
        table.add(new Transition(13, "factor", 15, "SHIFT"));
        table.add(new Transition(13, "ID", 12, "SHIFT"));
        table.add(new Transition(13, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(13, "NEW", 3, "SHIFT"));
        table.add(new Transition(13, "NULL", 11, "SHIFT"));
        table.add(new Transition(13, "NUM", 1, "SHIFT"));
        table.add(new Transition(13, "STAR", 14, "SHIFT"));
        table.add(new Transition(13, "term", 19, "SHIFT"));
        table.add(new Transition(14, "AMP", 26, "SHIFT"));
        table.add(new Transition(14, "factor", 6, "SHIFT"));
        table.add(new Transition(14, "ID", 12, "SHIFT"));
        table.add(new Transition(14, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(14, "NEW", 3, "SHIFT"));
        table.add(new Transition(14, "NULL", 11, "SHIFT"));
        table.add(new Transition(14, "NUM", 1, "SHIFT"));
        table.add(new Transition(14, "STAR", 14, "SHIFT"));
        table.add(new Transition(15, "EQ", 24, "REDUCE"));
        table.add(new Transition(15, "GE", 24, "REDUCE"));
        table.add(new Transition(15, "GT", 24, "REDUCE"));
        table.add(new Transition(15, "LE", 24, "REDUCE"));
        table.add(new Transition(15, "LT", 24, "REDUCE"));
        table.add(new Transition(15, "MINUS", 24, "REDUCE"));
        table.add(new Transition(15, "NE", 24, "REDUCE"));
        table.add(new Transition(15, "PCT", 24, "REDUCE"));
        table.add(new Transition(15, "PLUS", 24, "REDUCE"));
        table.add(new Transition(15, "RBRACK", 24, "REDUCE"));
        table.add(new Transition(15, "RPAREN", 24, "REDUCE"));
        table.add(new Transition(15, "SEMI", 24, "REDUCE"));
        table.add(new Transition(15, "SLASH", 24, "REDUCE"));
        table.add(new Transition(15, "STAR", 24, "REDUCE"));
        table.add(new Transition(16, "AMP", 26, "SHIFT"));
        table.add(new Transition(16, "expr", 92, "SHIFT"));
        table.add(new Transition(16, "factor", 15, "SHIFT"));
        table.add(new Transition(16, "ID", 12, "SHIFT"));
        table.add(new Transition(16, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(16, "NEW", 3, "SHIFT"));
        table.add(new Transition(16, "NULL", 11, "SHIFT"));
        table.add(new Transition(16, "NUM", 1, "SHIFT"));
        table.add(new Transition(16, "STAR", 14, "SHIFT"));
        table.add(new Transition(16, "term", 19, "SHIFT"));
        table.add(new Transition(17, "AMP", 26, "SHIFT"));
        table.add(new Transition(17, "expr", 96, "SHIFT"));
        table.add(new Transition(17, "factor", 15, "SHIFT"));
        table.add(new Transition(17, "ID", 12, "SHIFT"));
        table.add(new Transition(17, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(17, "NEW", 3, "SHIFT"));
        table.add(new Transition(17, "NULL", 11, "SHIFT"));
        table.add(new Transition(17, "NUM", 1, "SHIFT"));
        table.add(new Transition(17, "STAR", 14, "SHIFT"));
        table.add(new Transition(17, "term", 19, "SHIFT"));
        table.add(new Transition(18, "AMP", 26, "SHIFT"));
        table.add(new Transition(18, "expr", 57, "SHIFT"));
        table.add(new Transition(18, "factor", 15, "SHIFT"));
        table.add(new Transition(18, "ID", 12, "SHIFT"));
        table.add(new Transition(18, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(18, "NEW", 3, "SHIFT"));
        table.add(new Transition(18, "NULL", 11, "SHIFT"));
        table.add(new Transition(18, "NUM", 1, "SHIFT"));
        table.add(new Transition(18, "STAR", 14, "SHIFT"));
        table.add(new Transition(18, "term", 19, "SHIFT"));
        table.add(new Transition(19, "EQ", 21, "REDUCE"));
        table.add(new Transition(19, "GE", 21, "REDUCE"));
        table.add(new Transition(19, "GT", 21, "REDUCE"));
        table.add(new Transition(19, "LE", 21, "REDUCE"));
        table.add(new Transition(19, "LT", 21, "REDUCE"));
        table.add(new Transition(19, "MINUS", 21, "REDUCE"));
        table.add(new Transition(19, "NE", 21, "REDUCE"));
        table.add(new Transition(19, "PCT", 32, "SHIFT"));
        table.add(new Transition(19, "PLUS", 21, "REDUCE"));
        table.add(new Transition(19, "RBRACK", 21, "REDUCE"));
        table.add(new Transition(19, "RPAREN", 21, "REDUCE"));
        table.add(new Transition(19, "SEMI", 21, "REDUCE"));
        table.add(new Transition(19, "SLASH", 54, "SHIFT"));
        table.add(new Transition(19, "STAR", 46, "SHIFT"));
        table.add(new Transition(2, "AMP", 26, "SHIFT"));
        table.add(new Transition(2, "factor", 59, "SHIFT"));
        table.add(new Transition(2, "ID", 12, "SHIFT"));
        table.add(new Transition(2, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(2, "NEW", 3, "SHIFT"));
        table.add(new Transition(2, "NULL", 11, "SHIFT"));
        table.add(new Transition(2, "NUM", 1, "SHIFT"));
        table.add(new Transition(2, "STAR", 14, "SHIFT"));
        table.add(new Transition(20, "SEMI", 74, "SHIFT"));
        table.add(new Transition(21, "AMP", 26, "SHIFT"));
        table.add(new Transition(21, "expr", 94, "SHIFT"));
        table.add(new Transition(21, "factor", 15, "SHIFT"));
        table.add(new Transition(21, "ID", 12, "SHIFT"));
        table.add(new Transition(21, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(21, "NEW", 3, "SHIFT"));
        table.add(new Transition(21, "NULL", 11, "SHIFT"));
        table.add(new Transition(21, "NUM", 1, "SHIFT"));
        table.add(new Transition(21, "STAR", 14, "SHIFT"));
        table.add(new Transition(21, "term", 19, "SHIFT"));
        table.add(new Transition(22, "AMP", 26, "SHIFT"));
        table.add(new Transition(22, "factor", 15, "SHIFT"));
        table.add(new Transition(22, "ID", 12, "SHIFT"));
        table.add(new Transition(22, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(22, "NEW", 3, "SHIFT"));
        table.add(new Transition(22, "NULL", 11, "SHIFT"));
        table.add(new Transition(22, "NUM", 1, "SHIFT"));
        table.add(new Transition(22, "STAR", 14, "SHIFT"));
        table.add(new Transition(22, "term", 78, "SHIFT"));
        table.add(new Transition(23, "EQ", 17, "SHIFT"));
        table.add(new Transition(23, "GE", 16, "SHIFT"));
        table.add(new Transition(23, "GT", 7, "SHIFT"));
        table.add(new Transition(23, "LE", 24, "SHIFT"));
        table.add(new Transition(23, "LT", 21, "SHIFT"));
        table.add(new Transition(23, "MINUS", 25, "SHIFT"));
        table.add(new Transition(23, "NE", 37, "SHIFT"));
        table.add(new Transition(23, "PLUS", 22, "SHIFT"));
        table.add(new Transition(24, "AMP", 26, "SHIFT"));
        table.add(new Transition(24, "expr", 93, "SHIFT"));
        table.add(new Transition(24, "factor", 15, "SHIFT"));
        table.add(new Transition(24, "ID", 12, "SHIFT"));
        table.add(new Transition(24, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(24, "NEW", 3, "SHIFT"));
        table.add(new Transition(24, "NULL", 11, "SHIFT"));
        table.add(new Transition(24, "NUM", 1, "SHIFT"));
        table.add(new Transition(24, "STAR", 14, "SHIFT"));
        table.add(new Transition(24, "term", 19, "SHIFT"));
        table.add(new Transition(25, "AMP", 26, "SHIFT"));
        table.add(new Transition(25, "factor", 15, "SHIFT"));
        table.add(new Transition(25, "ID", 12, "SHIFT"));
        table.add(new Transition(25, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(25, "NEW", 3, "SHIFT"));
        table.add(new Transition(25, "NULL", 11, "SHIFT"));
        table.add(new Transition(25, "NUM", 1, "SHIFT"));
        table.add(new Transition(25, "STAR", 14, "SHIFT"));
        table.add(new Transition(25, "term", 79, "SHIFT"));
        table.add(new Transition(26, "ID", 53, "SHIFT"));
        table.add(new Transition(26, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(26, "lvalue", 90, "SHIFT"));
        table.add(new Transition(26, "STAR", 2, "SHIFT"));
        table.add(new Transition(27, "AMP", 26, "SHIFT"));
        table.add(new Transition(27, "expr", 55, "SHIFT"));
        table.add(new Transition(27, "factor", 15, "SHIFT"));
        table.add(new Transition(27, "ID", 12, "SHIFT"));
        table.add(new Transition(27, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(27, "NEW", 3, "SHIFT"));
        table.add(new Transition(27, "NULL", 11, "SHIFT"));
        table.add(new Transition(27, "NUM", 1, "SHIFT"));
        table.add(new Transition(27, "STAR", 14, "SHIFT"));
        table.add(new Transition(27, "term", 19, "SHIFT"));
        table.add(new Transition(28, "RBRACE", 31, "SHIFT"));
        table.add(new Transition(29, "ID", 3, "REDUCE"));
        table.add(new Transition(3, "INT", 33, "SHIFT"));
        table.add(new Transition(30, "ID", 53, "SHIFT"));
        table.add(new Transition(30, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(30, "lvalue", 69, "SHIFT"));
        table.add(new Transition(30, "STAR", 2, "SHIFT"));
        table.add(new Transition(31, "EOF", 1, "REDUCE"));
        table.add(new Transition(32, "AMP", 26, "SHIFT"));
        table.add(new Transition(32, "factor", 42, "SHIFT"));
        table.add(new Transition(32, "ID", 12, "SHIFT"));
        table.add(new Transition(32, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(32, "NEW", 3, "SHIFT"));
        table.add(new Transition(32, "NULL", 11, "SHIFT"));
        table.add(new Transition(32, "NUM", 1, "SHIFT"));
        table.add(new Transition(32, "STAR", 14, "SHIFT"));
        table.add(new Transition(33, "LBRACK", 83, "SHIFT"));
        table.add(new Transition(34, "SEMI", 4, "SHIFT"));
        table.add(new Transition(35, "LBRACE", 103, "SHIFT"));
        table.add(new Transition(36, "BECOMES", 31, "REDUCE"));
        table.add(new Transition(36, "EQ", 31, "REDUCE"));
        table.add(new Transition(36, "GE", 31, "REDUCE"));
        table.add(new Transition(36, "GT", 31, "REDUCE"));
        table.add(new Transition(36, "LE", 31, "REDUCE"));
        table.add(new Transition(36, "LT", 31, "REDUCE"));
        table.add(new Transition(36, "MINUS", 31, "REDUCE"));
        table.add(new Transition(36, "NE", 31, "REDUCE"));
        table.add(new Transition(36, "PCT", 31, "REDUCE"));
        table.add(new Transition(36, "PLUS", 31, "REDUCE"));
        table.add(new Transition(36, "RBRACK", 31, "REDUCE"));
        table.add(new Transition(36, "RPAREN", 31, "REDUCE"));
        table.add(new Transition(36, "SEMI", 31, "REDUCE"));
        table.add(new Transition(36, "SLASH", 31, "REDUCE"));
        table.add(new Transition(36, "STAR", 31, "REDUCE"));
        table.add(new Transition(37, "AMP", 26, "SHIFT"));
        table.add(new Transition(37, "expr", 95, "SHIFT"));
        table.add(new Transition(37, "factor", 15, "SHIFT"));
        table.add(new Transition(37, "ID", 12, "SHIFT"));
        table.add(new Transition(37, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(37, "NEW", 3, "SHIFT"));
        table.add(new Transition(37, "NULL", 11, "SHIFT"));
        table.add(new Transition(37, "NUM", 1, "SHIFT"));
        table.add(new Transition(37, "STAR", 14, "SHIFT"));
        table.add(new Transition(37, "term", 19, "SHIFT"));
        table.add(new Transition(38, "LPAREN", 48, "SHIFT"));
        table.add(new Transition(39, "ID", 2, "REDUCE"));
        table.add(new Transition(39, "STAR", 29, "SHIFT"));
        table.add(new Transition(4, "DELETE", 6, "REDUCE"));
        table.add(new Transition(4, "ID", 6, "REDUCE"));
        table.add(new Transition(4, "IF", 6, "REDUCE"));
        table.add(new Transition(4, "INT", 6, "REDUCE"));
        table.add(new Transition(4, "LPAREN", 6, "REDUCE"));
        table.add(new Transition(4, "PRINTLN", 6, "REDUCE"));
        table.add(new Transition(4, "RETURN", 6, "REDUCE"));
        table.add(new Transition(4, "STAR", 6, "REDUCE"));
        table.add(new Transition(4, "WHILE", 6, "REDUCE"));
        table.add(new Transition(40, "EQ", 25, "REDUCE"));
        table.add(new Transition(40, "GE", 25, "REDUCE"));
        table.add(new Transition(40, "GT", 25, "REDUCE"));
        table.add(new Transition(40, "LE", 25, "REDUCE"));
        table.add(new Transition(40, "LT", 25, "REDUCE"));
        table.add(new Transition(40, "MINUS", 25, "REDUCE"));
        table.add(new Transition(40, "NE", 25, "REDUCE"));
        table.add(new Transition(40, "PCT", 25, "REDUCE"));
        table.add(new Transition(40, "PLUS", 25, "REDUCE"));
        table.add(new Transition(40, "RBRACK", 25, "REDUCE"));
        table.add(new Transition(40, "RPAREN", 25, "REDUCE"));
        table.add(new Transition(40, "SEMI", 25, "REDUCE"));
        table.add(new Transition(40, "SLASH", 25, "REDUCE"));
        table.add(new Transition(40, "STAR", 25, "REDUCE"));
        table.add(new Transition(41, "EQ", 26, "REDUCE"));
        table.add(new Transition(41, "GE", 26, "REDUCE"));
        table.add(new Transition(41, "GT", 26, "REDUCE"));
        table.add(new Transition(41, "LE", 26, "REDUCE"));
        table.add(new Transition(41, "LT", 26, "REDUCE"));
        table.add(new Transition(41, "MINUS", 26, "REDUCE"));
        table.add(new Transition(41, "NE", 26, "REDUCE"));
        table.add(new Transition(41, "PCT", 26, "REDUCE"));
        table.add(new Transition(41, "PLUS", 26, "REDUCE"));
        table.add(new Transition(41, "RBRACK", 26, "REDUCE"));
        table.add(new Transition(41, "RPAREN", 26, "REDUCE"));
        table.add(new Transition(41, "SEMI", 26, "REDUCE"));
        table.add(new Transition(41, "SLASH", 26, "REDUCE"));
        table.add(new Transition(41, "STAR", 26, "REDUCE"));
        table.add(new Transition(42, "EQ", 27, "REDUCE"));
        table.add(new Transition(42, "GE", 27, "REDUCE"));
        table.add(new Transition(42, "GT", 27, "REDUCE"));
        table.add(new Transition(42, "LE", 27, "REDUCE"));
        table.add(new Transition(42, "LT", 27, "REDUCE"));
        table.add(new Transition(42, "MINUS", 27, "REDUCE"));
        table.add(new Transition(42, "NE", 27, "REDUCE"));
        table.add(new Transition(42, "PCT", 27, "REDUCE"));
        table.add(new Transition(42, "PLUS", 27, "REDUCE"));
        table.add(new Transition(42, "RBRACK", 27, "REDUCE"));
        table.add(new Transition(42, "RPAREN", 27, "REDUCE"));
        table.add(new Transition(42, "SEMI", 27, "REDUCE"));
        table.add(new Transition(42, "SLASH", 27, "REDUCE"));
        table.add(new Transition(42, "STAR", 27, "REDUCE"));
        table.add(new Transition(43, "NULL", 34, "SHIFT"));
        table.add(new Transition(43, "NUM", 51, "SHIFT"));
        table.add(new Transition(44, "WAIN", 75, "SHIFT"));
        table.add(new Transition(45, "BECOMES", 37, "REDUCE"));
        table.add(new Transition(45, "EQ", 37, "REDUCE"));
        table.add(new Transition(45, "GE", 37, "REDUCE"));
        table.add(new Transition(45, "GT", 37, "REDUCE"));
        table.add(new Transition(45, "LE", 37, "REDUCE"));
        table.add(new Transition(45, "LT", 37, "REDUCE"));
        table.add(new Transition(45, "MINUS", 37, "REDUCE"));
        table.add(new Transition(45, "NE", 37, "REDUCE"));
        table.add(new Transition(45, "PCT", 37, "REDUCE"));
        table.add(new Transition(45, "PLUS", 37, "REDUCE"));
        table.add(new Transition(45, "RBRACK", 37, "REDUCE"));
        table.add(new Transition(45, "RPAREN", 37, "REDUCE"));
        table.add(new Transition(45, "SEMI", 37, "REDUCE"));
        table.add(new Transition(45, "SLASH", 37, "REDUCE"));
        table.add(new Transition(45, "STAR", 37, "REDUCE"));
        table.add(new Transition(46, "AMP", 26, "SHIFT"));
        table.add(new Transition(46, "factor", 40, "SHIFT"));
        table.add(new Transition(46, "ID", 12, "SHIFT"));
        table.add(new Transition(46, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(46, "NEW", 3, "SHIFT"));
        table.add(new Transition(46, "NULL", 11, "SHIFT"));
        table.add(new Transition(46, "NUM", 1, "SHIFT"));
        table.add(new Transition(46, "STAR", 14, "SHIFT"));
        table.add(new Transition(47, "AMP", 26, "SHIFT"));
        table.add(new Transition(47, "expr", 23, "SHIFT"));
        table.add(new Transition(47, "factor", 15, "SHIFT"));
        table.add(new Transition(47, "ID", 12, "SHIFT"));
        table.add(new Transition(47, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(47, "NEW", 3, "SHIFT"));
        table.add(new Transition(47, "NULL", 11, "SHIFT"));
        table.add(new Transition(47, "NUM", 1, "SHIFT"));
        table.add(new Transition(47, "STAR", 14, "SHIFT"));
        table.add(new Transition(47, "term", 19, "SHIFT"));
        table.add(new Transition(47, "test", 76, "SHIFT"));
        table.add(new Transition(48, "AMP", 26, "SHIFT"));
        table.add(new Transition(48, "expr", 23, "SHIFT"));
        table.add(new Transition(48, "factor", 15, "SHIFT"));
        table.add(new Transition(48, "ID", 12, "SHIFT"));
        table.add(new Transition(48, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(48, "NEW", 3, "SHIFT"));
        table.add(new Transition(48, "NULL", 11, "SHIFT"));
        table.add(new Transition(48, "NUM", 1, "SHIFT"));
        table.add(new Transition(48, "STAR", 14, "SHIFT"));
        table.add(new Transition(48, "term", 19, "SHIFT"));
        table.add(new Transition(48, "test", 77, "SHIFT"));
        table.add(new Transition(49, "AMP", 26, "SHIFT"));
        table.add(new Transition(49, "expr", 56, "SHIFT"));
        table.add(new Transition(49, "factor", 15, "SHIFT"));
        table.add(new Transition(49, "ID", 12, "SHIFT"));
        table.add(new Transition(49, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(49, "NEW", 3, "SHIFT"));
        table.add(new Transition(49, "NULL", 11, "SHIFT"));
        table.add(new Transition(49, "NUM", 1, "SHIFT"));
        table.add(new Transition(49, "STAR", 14, "SHIFT"));
        table.add(new Transition(49, "term", 19, "SHIFT"));
        table.add(new Transition(5, "DELETE", 5, "REDUCE"));
        table.add(new Transition(5, "ID", 5, "REDUCE"));
        table.add(new Transition(5, "IF", 5, "REDUCE"));
        table.add(new Transition(5, "INT", 5, "REDUCE"));
        table.add(new Transition(5, "LPAREN", 5, "REDUCE"));
        table.add(new Transition(5, "PRINTLN", 5, "REDUCE"));
        table.add(new Transition(5, "RETURN", 5, "REDUCE"));
        table.add(new Transition(5, "STAR", 5, "REDUCE"));
        table.add(new Transition(5, "WHILE", 5, "REDUCE"));
        table.add(new Transition(50, "EOF", 102, "SHIFT"));
        table.add(new Transition(51, "SEMI", 5, "SHIFT"));
        table.add(new Transition(52, "LPAREN", 47, "SHIFT"));
        table.add(new Transition(53, "BECOMES", 35, "REDUCE"));
        table.add(new Transition(53, "EQ", 35, "REDUCE"));
        table.add(new Transition(53, "GE", 35, "REDUCE"));
        table.add(new Transition(53, "GT", 35, "REDUCE"));
        table.add(new Transition(53, "LE", 35, "REDUCE"));
        table.add(new Transition(53, "LT", 35, "REDUCE"));
        table.add(new Transition(53, "MINUS", 35, "REDUCE"));
        table.add(new Transition(53, "NE", 35, "REDUCE"));
        table.add(new Transition(53, "PCT", 35, "REDUCE"));
        table.add(new Transition(53, "PLUS", 35, "REDUCE"));
        table.add(new Transition(53, "RBRACK", 35, "REDUCE"));
        table.add(new Transition(53, "RPAREN", 35, "REDUCE"));
        table.add(new Transition(53, "SEMI", 35, "REDUCE"));
        table.add(new Transition(53, "SLASH", 35, "REDUCE"));
        table.add(new Transition(53, "STAR", 35, "REDUCE"));
        table.add(new Transition(54, "AMP", 26, "SHIFT"));
        table.add(new Transition(54, "factor", 41, "SHIFT"));
        table.add(new Transition(54, "ID", 12, "SHIFT"));
        table.add(new Transition(54, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(54, "NEW", 3, "SHIFT"));
        table.add(new Transition(54, "NULL", 11, "SHIFT"));
        table.add(new Transition(54, "NUM", 1, "SHIFT"));
        table.add(new Transition(54, "STAR", 14, "SHIFT"));
        table.add(new Transition(55, "MINUS", 25, "SHIFT"));
        table.add(new Transition(55, "PLUS", 22, "SHIFT"));
        table.add(new Transition(55, "SEMI", 106, "SHIFT"));
        table.add(new Transition(56, "MINUS", 25, "SHIFT"));
        table.add(new Transition(56, "PLUS", 22, "SHIFT"));
        table.add(new Transition(56, "RPAREN", 20, "SHIFT"));
        table.add(new Transition(57, "MINUS", 25, "SHIFT"));
        table.add(new Transition(57, "PLUS", 22, "SHIFT"));
        table.add(new Transition(57, "SEMI", 105, "SHIFT"));
        table.add(new Transition(58, "BECOMES", 43, "SHIFT"));
        table.add(new Transition(59, "BECOMES", 36, "REDUCE"));
        table.add(new Transition(59, "EQ", 36, "REDUCE"));
        table.add(new Transition(59, "GE", 36, "REDUCE"));
        table.add(new Transition(59, "GT", 36, "REDUCE"));
        table.add(new Transition(59, "LE", 36, "REDUCE"));
        table.add(new Transition(59, "LT", 36, "REDUCE"));
        table.add(new Transition(59, "MINUS", 36, "REDUCE"));
        table.add(new Transition(59, "NE", 36, "REDUCE"));
        table.add(new Transition(59, "PCT", 36, "REDUCE"));
        table.add(new Transition(59, "PLUS", 36, "REDUCE"));
        table.add(new Transition(59, "RBRACK", 36, "REDUCE"));
        table.add(new Transition(59, "RPAREN", 36, "REDUCE"));
        table.add(new Transition(59, "SEMI", 36, "REDUCE"));
        table.add(new Transition(59, "SLASH", 36, "REDUCE"));
        table.add(new Transition(59, "STAR", 36, "REDUCE"));
        table.add(new Transition(6, "BECOMES", 33, "REDUCE"));
        table.add(new Transition(6, "EQ", 33, "REDUCE"));
        table.add(new Transition(6, "GE", 33, "REDUCE"));
        table.add(new Transition(6, "GT", 33, "REDUCE"));
        table.add(new Transition(6, "LE", 33, "REDUCE"));
        table.add(new Transition(6, "LT", 33, "REDUCE"));
        table.add(new Transition(6, "MINUS", 33, "REDUCE"));
        table.add(new Transition(6, "NE", 33, "REDUCE"));
        table.add(new Transition(6, "PCT", 33, "REDUCE"));
        table.add(new Transition(6, "PLUS", 33, "REDUCE"));
        table.add(new Transition(6, "RBRACK", 33, "REDUCE"));
        table.add(new Transition(6, "RPAREN", 33, "REDUCE"));
        table.add(new Transition(6, "SEMI", 33, "REDUCE"));
        table.add(new Transition(6, "SLASH", 33, "REDUCE"));
        table.add(new Transition(6, "STAR", 33, "REDUCE"));
        table.add(new Transition(60, "RPAREN", 65, "SHIFT"));
        table.add(new Transition(61, "LBRACK", 104, "SHIFT"));
        table.add(new Transition(62, "COMMA", 98, "SHIFT"));
        table.add(new Transition(63, "ID", 81, "SHIFT"));
        table.add(new Transition(64, "MINUS", 25, "SHIFT"));
        table.add(new Transition(64, "PLUS", 22, "SHIFT"));
        table.add(new Transition(64, "SEMI", 28, "SHIFT"));
        table.add(new Transition(65, "LBRACE", 85, "SHIFT"));
        table.add(new Transition(66, "DELETE", 9, "REDUCE"));
        table.add(new Transition(66, "ID", 9, "REDUCE"));
        table.add(new Transition(66, "IF", 9, "REDUCE"));
        table.add(new Transition(66, "LPAREN", 9, "REDUCE"));
        table.add(new Transition(66, "PRINTLN", 9, "REDUCE"));
        table.add(new Transition(66, "RBRACE", 9, "REDUCE"));
        table.add(new Transition(66, "RETURN", 9, "REDUCE"));
        table.add(new Transition(66, "STAR", 9, "REDUCE"));
        table.add(new Transition(66, "WHILE", 9, "REDUCE"));
        table.add(new Transition(67, "dcl", 58, "SHIFT"));
        table.add(new Transition(67, "DELETE", 8, "REDUCE"));
        table.add(new Transition(67, "ID", 8, "REDUCE"));
        table.add(new Transition(67, "IF", 8, "REDUCE"));
        table.add(new Transition(67, "INT", 39, "SHIFT"));
        table.add(new Transition(67, "LPAREN", 8, "REDUCE"));
        table.add(new Transition(67, "PRINTLN", 8, "REDUCE"));
        table.add(new Transition(67, "RBRACE", 8, "REDUCE"));
        table.add(new Transition(67, "RETURN", 8, "REDUCE"));
        table.add(new Transition(67, "STAR", 8, "REDUCE"));
        table.add(new Transition(67, "statements", 97, "SHIFT"));
        table.add(new Transition(67, "type", 63, "SHIFT"));
        table.add(new Transition(67, "WHILE", 8, "REDUCE"));
        table.add(new Transition(68, "BECOMES", 18, "SHIFT"));
        table.add(new Transition(69, "RPAREN", 45, "SHIFT"));
        table.add(new Transition(7, "AMP", 26, "SHIFT"));
        table.add(new Transition(7, "expr", 91, "SHIFT"));
        table.add(new Transition(7, "factor", 15, "SHIFT"));
        table.add(new Transition(7, "ID", 12, "SHIFT"));
        table.add(new Transition(7, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(7, "NEW", 3, "SHIFT"));
        table.add(new Transition(7, "NULL", 11, "SHIFT"));
        table.add(new Transition(7, "NUM", 1, "SHIFT"));
        table.add(new Transition(7, "STAR", 14, "SHIFT"));
        table.add(new Transition(7, "term", 19, "SHIFT"));
        table.add(new Transition(70, "dcl", 62, "SHIFT"));
        table.add(new Transition(70, "INT", 39, "SHIFT"));
        table.add(new Transition(70, "type", 63, "SHIFT"));
        table.add(new Transition(71, "DELETE", 61, "SHIFT"));
        table.add(new Transition(71, "ID", 53, "SHIFT"));
        table.add(new Transition(71, "IF", 52, "SHIFT"));
        table.add(new Transition(71, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(71, "lvalue", 68, "SHIFT"));
        table.add(new Transition(71, "PRINTLN", 82, "SHIFT"));
        table.add(new Transition(71, "RBRACE", 8, "SHIFT"));
        table.add(new Transition(71, "STAR", 2, "SHIFT"));
        table.add(new Transition(71, "statement", 66, "SHIFT"));
        table.add(new Transition(71, "WHILE", 38, "SHIFT"));
        table.add(new Transition(72, "DELETE", 61, "SHIFT"));
        table.add(new Transition(72, "ID", 53, "SHIFT"));
        table.add(new Transition(72, "IF", 52, "SHIFT"));
        table.add(new Transition(72, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(72, "lvalue", 68, "SHIFT"));
        table.add(new Transition(72, "PRINTLN", 82, "SHIFT"));
        table.add(new Transition(72, "RBRACE", 9, "SHIFT"));
        table.add(new Transition(72, "STAR", 2, "SHIFT"));
        table.add(new Transition(72, "statement", 66, "SHIFT"));
        table.add(new Transition(72, "WHILE", 38, "SHIFT"));
        table.add(new Transition(73, "DELETE", 61, "SHIFT"));
        table.add(new Transition(73, "ID", 53, "SHIFT"));
        table.add(new Transition(73, "IF", 52, "SHIFT"));
        table.add(new Transition(73, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(73, "lvalue", 68, "SHIFT"));
        table.add(new Transition(73, "PRINTLN", 82, "SHIFT"));
        table.add(new Transition(73, "RBRACE", 10, "SHIFT"));
        table.add(new Transition(73, "STAR", 2, "SHIFT"));
        table.add(new Transition(73, "statement", 66, "SHIFT"));
        table.add(new Transition(73, "WHILE", 38, "SHIFT"));
        table.add(new Transition(74, "DELETE", 13, "REDUCE"));
        table.add(new Transition(74, "ID", 13, "REDUCE"));
        table.add(new Transition(74, "IF", 13, "REDUCE"));
        table.add(new Transition(74, "LPAREN", 13, "REDUCE"));
        table.add(new Transition(74, "PRINTLN", 13, "REDUCE"));
        table.add(new Transition(74, "RBRACE", 13, "REDUCE"));
        table.add(new Transition(74, "RETURN", 13, "REDUCE"));
        table.add(new Transition(74, "STAR", 13, "REDUCE"));
        table.add(new Transition(74, "WHILE", 13, "REDUCE"));
        table.add(new Transition(75, "LPAREN", 70, "SHIFT"));
        table.add(new Transition(76, "RPAREN", 86, "SHIFT"));
        table.add(new Transition(77, "RPAREN", 87, "SHIFT"));
        table.add(new Transition(78, "EQ", 22, "REDUCE"));
        table.add(new Transition(78, "GE", 22, "REDUCE"));
        table.add(new Transition(78, "GT", 22, "REDUCE"));
        table.add(new Transition(78, "LE", 22, "REDUCE"));
        table.add(new Transition(78, "LT", 22, "REDUCE"));
        table.add(new Transition(78, "MINUS", 22, "REDUCE"));
        table.add(new Transition(78, "NE", 22, "REDUCE"));
        table.add(new Transition(78, "PCT", 32, "SHIFT"));
        table.add(new Transition(78, "PLUS", 22, "REDUCE"));
        table.add(new Transition(78, "RBRACK", 22, "REDUCE"));
        table.add(new Transition(78, "RPAREN", 22, "REDUCE"));
        table.add(new Transition(78, "SEMI", 22, "REDUCE"));
        table.add(new Transition(78, "SLASH", 54, "SHIFT"));
        table.add(new Transition(78, "STAR", 46, "SHIFT"));
        table.add(new Transition(79, "EQ", 23, "REDUCE"));
        table.add(new Transition(79, "GE", 23, "REDUCE"));
        table.add(new Transition(79, "GT", 23, "REDUCE"));
        table.add(new Transition(79, "LE", 23, "REDUCE"));
        table.add(new Transition(79, "LT", 23, "REDUCE"));
        table.add(new Transition(79, "MINUS", 23, "REDUCE"));
        table.add(new Transition(79, "NE", 23, "REDUCE"));
        table.add(new Transition(79, "PCT", 32, "SHIFT"));
        table.add(new Transition(79, "PLUS", 23, "REDUCE"));
        table.add(new Transition(79, "RBRACK", 23, "REDUCE"));
        table.add(new Transition(79, "RPAREN", 23, "REDUCE"));
        table.add(new Transition(79, "SEMI", 23, "REDUCE"));
        table.add(new Transition(79, "SLASH", 54, "SHIFT"));
        table.add(new Transition(79, "STAR", 46, "SHIFT"));
        table.add(new Transition(8, "ELSE", 35, "SHIFT"));
        table.add(new Transition(80, "BECOMES", 34, "REDUCE"));
        table.add(new Transition(80, "EQ", 34, "REDUCE"));
        table.add(new Transition(80, "GE", 34, "REDUCE"));
        table.add(new Transition(80, "GT", 34, "REDUCE"));
        table.add(new Transition(80, "LE", 34, "REDUCE"));
        table.add(new Transition(80, "LT", 34, "REDUCE"));
        table.add(new Transition(80, "MINUS", 34, "REDUCE"));
        table.add(new Transition(80, "NE", 34, "REDUCE"));
        table.add(new Transition(80, "PCT", 34, "REDUCE"));
        table.add(new Transition(80, "PLUS", 34, "REDUCE"));
        table.add(new Transition(80, "RBRACK", 34, "REDUCE"));
        table.add(new Transition(80, "RPAREN", 34, "REDUCE"));
        table.add(new Transition(80, "SEMI", 34, "REDUCE"));
        table.add(new Transition(80, "SLASH", 34, "REDUCE"));
        table.add(new Transition(80, "STAR", 34, "REDUCE"));
        table.add(new Transition(81, "BECOMES", 7, "REDUCE"));
        table.add(new Transition(81, "COMMA", 7, "REDUCE"));
        table.add(new Transition(81, "RPAREN", 7, "REDUCE"));
        table.add(new Transition(82, "LPAREN", 49, "SHIFT"));
        table.add(new Transition(83, "AMP", 26, "SHIFT"));
        table.add(new Transition(83, "expr", 88, "SHIFT"));
        table.add(new Transition(83, "factor", 15, "SHIFT"));
        table.add(new Transition(83, "ID", 12, "SHIFT"));
        table.add(new Transition(83, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(83, "NEW", 3, "SHIFT"));
        table.add(new Transition(83, "NULL", 11, "SHIFT"));
        table.add(new Transition(83, "NUM", 1, "SHIFT"));
        table.add(new Transition(83, "STAR", 14, "SHIFT"));
        table.add(new Transition(83, "term", 19, "SHIFT"));
        table.add(new Transition(84, "AMP", 26, "SHIFT"));
        table.add(new Transition(84, "expr", 64, "SHIFT"));
        table.add(new Transition(84, "factor", 15, "SHIFT"));
        table.add(new Transition(84, "ID", 12, "SHIFT"));
        table.add(new Transition(84, "LPAREN", 13, "SHIFT"));
        table.add(new Transition(84, "NEW", 3, "SHIFT"));
        table.add(new Transition(84, "NULL", 11, "SHIFT"));
        table.add(new Transition(84, "NUM", 1, "SHIFT"));
        table.add(new Transition(84, "STAR", 14, "SHIFT"));
        table.add(new Transition(84, "term", 19, "SHIFT"));
        table.add(new Transition(85, "dcls", 67, "SHIFT"));
        table.add(new Transition(85, "DELETE", 4, "REDUCE"));
        table.add(new Transition(85, "ID", 4, "REDUCE"));
        table.add(new Transition(85, "IF", 4, "REDUCE"));
        table.add(new Transition(85, "INT", 4, "REDUCE"));
        table.add(new Transition(85, "LPAREN", 4, "REDUCE"));
        table.add(new Transition(85, "PRINTLN", 4, "REDUCE"));
        table.add(new Transition(85, "RETURN", 4, "REDUCE"));
        table.add(new Transition(85, "STAR", 4, "REDUCE"));
        table.add(new Transition(85, "WHILE", 4, "REDUCE"));
        table.add(new Transition(86, "LBRACE", 101, "SHIFT"));
        table.add(new Transition(87, "LBRACE", 100, "SHIFT"));
        table.add(new Transition(88, "MINUS", 25, "SHIFT"));
        table.add(new Transition(88, "PLUS", 22, "SHIFT"));
        table.add(new Transition(88, "RBRACK", 80, "SHIFT"));
        table.add(new Transition(89, "MINUS", 25, "SHIFT"));
        table.add(new Transition(89, "PLUS", 22, "SHIFT"));
        table.add(new Transition(89, "RPAREN", 36, "SHIFT"));
        table.add(new Transition(9, "DELETE", 12, "REDUCE"));
        table.add(new Transition(9, "ID", 12, "REDUCE"));
        table.add(new Transition(9, "IF", 12, "REDUCE"));
        table.add(new Transition(9, "LPAREN", 12, "REDUCE"));
        table.add(new Transition(9, "PRINTLN", 12, "REDUCE"));
        table.add(new Transition(9, "RBRACE", 12, "REDUCE"));
        table.add(new Transition(9, "RETURN", 12, "REDUCE"));
        table.add(new Transition(9, "STAR", 12, "REDUCE"));
        table.add(new Transition(9, "WHILE", 12, "REDUCE"));
        table.add(new Transition(90, "BECOMES", 32, "REDUCE"));
        table.add(new Transition(90, "EQ", 32, "REDUCE"));
        table.add(new Transition(90, "GE", 32, "REDUCE"));
        table.add(new Transition(90, "GT", 32, "REDUCE"));
        table.add(new Transition(90, "LE", 32, "REDUCE"));
        table.add(new Transition(90, "LT", 32, "REDUCE"));
        table.add(new Transition(90, "MINUS", 32, "REDUCE"));
        table.add(new Transition(90, "NE", 32, "REDUCE"));
        table.add(new Transition(90, "PCT", 32, "REDUCE"));
        table.add(new Transition(90, "PLUS", 32, "REDUCE"));
        table.add(new Transition(90, "RBRACK", 32, "REDUCE"));
        table.add(new Transition(90, "RPAREN", 32, "REDUCE"));
        table.add(new Transition(90, "SEMI", 32, "REDUCE"));
        table.add(new Transition(90, "SLASH", 32, "REDUCE"));
        table.add(new Transition(90, "STAR", 32, "REDUCE"));
        table.add(new Transition(91, "MINUS", 25, "SHIFT"));
        table.add(new Transition(91, "PLUS", 22, "SHIFT"));
        table.add(new Transition(91, "RPAREN", 20, "REDUCE"));
        table.add(new Transition(92, "MINUS", 25, "SHIFT"));
        table.add(new Transition(92, "PLUS", 22, "SHIFT"));
        table.add(new Transition(92, "RPAREN", 19, "REDUCE"));
        table.add(new Transition(93, "MINUS", 25, "SHIFT"));
        table.add(new Transition(93, "PLUS", 22, "SHIFT"));
        table.add(new Transition(93, "RPAREN", 18, "REDUCE"));
        table.add(new Transition(94, "MINUS", 25, "SHIFT"));
        table.add(new Transition(94, "PLUS", 22, "SHIFT"));
        table.add(new Transition(94, "RPAREN", 17, "REDUCE"));
        table.add(new Transition(95, "MINUS", 25, "SHIFT"));
        table.add(new Transition(95, "PLUS", 22, "SHIFT"));
        table.add(new Transition(95, "RPAREN", 16, "REDUCE"));
        table.add(new Transition(96, "MINUS", 25, "SHIFT"));
        table.add(new Transition(96, "PLUS", 22, "SHIFT"));
        table.add(new Transition(96, "RPAREN", 15, "REDUCE"));
        table.add(new Transition(97, "DELETE", 61, "SHIFT"));
        table.add(new Transition(97, "ID", 53, "SHIFT"));
        table.add(new Transition(97, "IF", 52, "SHIFT"));
        table.add(new Transition(97, "LPAREN", 30, "SHIFT"));
        table.add(new Transition(97, "lvalue", 68, "SHIFT"));
        table.add(new Transition(97, "PRINTLN", 82, "SHIFT"));
        table.add(new Transition(97, "RETURN", 84, "SHIFT"));
        table.add(new Transition(97, "STAR", 2, "SHIFT"));
        table.add(new Transition(97, "statement", 66, "SHIFT"));
        table.add(new Transition(97, "WHILE", 38, "SHIFT"));
        table.add(new Transition(98, "dcl", 60, "SHIFT"));
        table.add(new Transition(98, "INT", 39, "SHIFT"));
        table.add(new Transition(98, "type", 63, "SHIFT"));
        table.add(new Transition(99, "INT", 44, "SHIFT"));
        table.add(new Transition(99, "procedure", 50, "SHIFT"));
    }
}