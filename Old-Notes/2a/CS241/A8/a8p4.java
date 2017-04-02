import java.util.*;

public class CFGrl {
    Scanner in = new Scanner(System.in);
    public class Tree {
        String rule;
        LinkedList<Tree> children = new LinkedList<Tree>();
    }
    Set<String> terms = new HashSet<String>(); // terminals
    Set<String> nonterms = new HashSet<String>(); // nonterminals
    Set<String> prods = new HashSet<String>(); // production rules
    String start; // start symbol

    // read n symbols into set t
    public void readsyms(int n, Set<String> t) {
        for(int i = 0; i < n; i++) {
            t.add(in.nextLine());
        }
    }

    // read single line containing integer
    public int readln() {
        return Integer.parseInt(in.nextLine());
    }

    // output leftmost derivation of tree t with indentation d
    public void traverse(Tree t, int d) {
        for(int i = 0; i < d; i++) System.out.print(" ");
        System.out.println(t.rule); // print root
        for(Tree c : t.children) {  // print all subtrees
            traverse(c, d+1);
        }
    }

    // print elements of set h in .cfg file format
    public void dump(Set<String> h) {
        System.out.println(h.size());
        for(String s : h) {
            System.out.println(s);
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
        do {
            String f = in.nextLine();
            List<String> r = new ArrayList<String>(); // rhs symbols

            Scanner sc = new Scanner(f);
            l = sc.next(); // lhs symbol
            while(sc.hasNext()) {
                String s = sc.next();
                if(nonterms.contains(s)) r.add(s); // only non-terminals
            }
            popper(stack, r, f); // reduce rule
        } while(!start.equals(l));
        return stack.peek();
    }

    public void go() {
        readsyms(readln(), terms); // read terminals
        readsyms(readln(), nonterms); // read nonterminals
        start = in.nextLine(); // read start symbol
        readsyms(readln(), prods); // read production rules
        Tree parsetree = lrdo(); // read reverse rightmost derivation
        dump(terms); // write terminals in .cfg format
        dump(nonterms); // write nonterminals
        System.out.println(start); // write start symbol
        dump(prods); // write production rules
        traverse(parsetree, 0); // write forward leftmost derivation
    }

    public static final void main(String[] args) {
        new CFGrl().go();
    }
}