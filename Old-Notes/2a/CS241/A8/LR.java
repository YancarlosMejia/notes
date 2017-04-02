import java.util.*;

public class LR {
    public static void main(String[] args){
        new LR().run();
    }
    private void run(){
        Scanner in  = new Scanner(System.in);
        skipGrammar(in);
        ArrayList<String> rules = new ArrayList<String>();
        ArrayList<Transition> table = new ArrayList<Transition>();
        ArrayList<String> input = new ArrayList<String>();
        ArrayList<String> print = new ArrayList<String>();
        String start = in.nextLine();
        int num = in.nextInt();
        in.nextLine();
        for(int i = 0; i < num; i++) {
            rules.add(in.nextLine());
        }
        in.nextLine();
        int num1 = in.nextInt();
        in.nextLine();
        for(int i = 0; i < num1; i++){
            String[] line = in.nextLine().split(" ");
            Transition current = new Transition(0, "0", "0", 0);
            current.fromState = Integer.parseInt(line[0]);
            current.stuff = line[1];
            current.type = line[2];
            current.toState = Integer.parseInt(line[3]);
            table.add(current);
        }
        while(in.hasNext()){
            String [] temp = in.nextLine().split(" ");
            for(String a : temp){
                input.add(a);
            }
        }
        /*for(String a : input){
            System.err.print(a + " ");
        }
        System.err.println();*/



        Stack<Integer> state = new Stack<Integer>();
        Stack<String> symbol = new Stack<String>();
        state.push(0);
        symbol.push("BOF");
        for(int i = 0; i<input.size(); i++) {
            //System.out.println();
            //System.out.println("ID = " + input.get(i));
            try {
                Transition next = findTransition(state.peek(), input.get(i), table);
                if(next.type.equals("shift")) {
                   //System.out.println(state.peek() + " to" + next.toState +  " by shift on " + symbol.peek()); 
                    symbol.push(next.stuff);
                    state.push(next.toState);

                }
                else{
                    String [] change = rules.get(next.toState).split(" ");
                    for(int j = 0; j < change.length-1; j++){
                        symbol.pop();
                        state.pop();
                        //System.out.print("Pop" + symbol.pop());
                        //System.out.println(" Pop" + state.pop());
                    }
                    //System.out.println(state.peek() + " to " + next.toState + " by " + rules.get(next.toState));
                    print.add(rules.get(next.toState));
                    symbol.push(change[0]);
                    state.push(findTransition(state.peek(), change[0], table).toState);


                    while(findTransition(state.peek(), input.get(i), table).type.equals("reduce")){
                        next = findTransition(state.peek(), input.get(i), table);
                        change = rules.get(next.toState).split(" ");
                        for(int j = 0; j < change.length-1; j++){
                            symbol.pop();
                            state.pop();
                        }
                        //System.out.println("findTransition " + state.peek() +" "+ change[0]);
                        //System.out.println(state.peek() + " to " + findTransition(state.peek(), change[0], table).toState + " by " + rules.get(next.toState));
                        print.add(rules.get(next.toState));
                        symbol.push(change[0]);
                        state.push(findTransition(state.peek(), change[0], table).toState);

                    }
                    next = findTransition(state.peek(), input.get(i), table);
                    //System.out.println(state.peek() + " to " + next.toState +  " by shift on " + input.get(i)); 
                    symbol.push(next.stuff);
                    state.push(next.toState);
                }

            }
            catch (Exception e) {
                int line = i + 1;
                System.err.println("ERROR at " + line);
               /*while(!symbol.peek().equals("BOF")) {
                    System.err.print(state.pop() + " ");
                    System.err.println(symbol.pop());
                }*/
                System.exit(0);
            }
        }   
        for(String r : rules){
            if(r.startsWith(start + " ")){
                print.add(r);
                break;
            }
        }
        for(String s : print) {
            System.out.println(s);
        }

  }

  private static void skipGrammar(Scanner in) {
    assert(in.hasNextInt());
    int numTerm = in.nextInt();
    in.nextLine();
    for (int i = 0; i < numTerm; i++) {
      in.nextLine();
    }
    int numNonTerm = in.nextInt();
    in.nextLine();
    for (int i = 0; i < numNonTerm; i++) {
      in.nextLine();
    }
  }
    private class Transition {
        int fromState;
        String stuff;
        String type;
        int toState;
        Transition(int fromState, String stuff, String type, int toState) {
            this.fromState = fromState;
            this.stuff = stuff;
            this.type = type;
            this.toState = toState;
        }
    }
    private Transition findTransition(int state, String blah, ArrayList<Transition> table) {
        for( int j = 0; j < table.size(); j++) {
            Transition t = table.get(j);
            if(t.fromState == state && t.stuff.equals(blah)) {
                return t;
            }
        }
        return null;
    }
}

    
