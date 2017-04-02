import java.util.*;

public class WLPPGen {

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
    public boolean checkTree(Tree t) {
        if(t.rule.get(0).equals("ID")) {
            if(!symbols.containsKey(t.rule.get(1))) {
                System.err.println("ERROR " + t.rule.get(1) + " isnt declared");
            }
        }
        else {
            for(Tree s : t.children) {
                checkTree(s);
            }
        }
        return true;
    }

    // Compute symbols defined in t
    List<String> genSymbols(Tree t) {
        return null;
    }
 

    // Print an error message and exit the program.
    void bail(String msg) {
        System.err.println("ERROR: " + msg);
        System.exit(0);
    }

    // Generate the code for the parse tree t.
    String genCode(Tree t) {
        return null;
    }

    // Main program
    public static final void main(String args[]) {
        new WLPPGen().go();
    }

    public void go() {
        Tree parseTree = readParse("S");
        for (Map.Entry<String, String> entry : symbols.entrySet()) {
            System.err.println(entry.getKey() + " " + entry.getValue());
        }
        checkTree(parseTree);
    }
}