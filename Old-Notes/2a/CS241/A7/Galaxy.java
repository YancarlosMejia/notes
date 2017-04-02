import java.util.*;

public class Galaxy {
  public static void main(String[] args) {
    Scanner in = new Scanner(System.in);
    skipGrammar(in);
    //printDerivation(in);
    String line;
    String stuff[];
    String equation = in.nextLine().trim();
    while (in.hasNextLine()){
      line = in.nextLine().trim();
      stuff = line.split(" ", 2);
      equation = equation.replaceFirst(stuff[0], stuff[1]);
    }
    String temp[] = equation.split(" ");
    
    ArrayList<String> pieces = new ArrayList<String>(Arrays.asList(temp));
    System.out.println(interpret(pieces));
  }
  public static int interpret(ArrayList <String> pieces){
    int total = 0;
    int brackets = 1;
    int multiplier = 1;
    ArrayList<String> sub = new ArrayList<String>();
    for(int i = 0; i<pieces.size(); i++){
      if(pieces.get(i).equals("-")){
        multiplier *=-1;
      }
      else if(pieces.get(i).equals("id")){
        total += multiplier * 42;
        multiplier =1;
      }
      else if(pieces.get(i).equals("(")){
        while(brackets>1 || !pieces.get(i).equals(")")){
          i += 1;
          sub.add(pieces.get(i));
          if(pieces.get(i).equals("(")){
            brackets +=1;
          }
          else if(pieces.get(i).equals(")")){
            brackets -=1;
          }
        }
        total += multiplier * interpret(sub);
        multiplier = 1;
        brackets = 0;
      }
    }
    return total;
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
    in.nextLine();
    int numRules = in.nextInt();
    in.nextLine();
    for (int i = 0; i < numRules; i++) {
      in.nextLine();
    }
  }

  private static void printDerivation(Scanner in) {
    while (in.hasNextLine()) {
      System.out.println(in.nextLine().trim());
    }
  }
}