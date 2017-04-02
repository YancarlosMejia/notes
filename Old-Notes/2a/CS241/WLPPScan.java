import java.util.*;
import java.math.*;

public class WLPPScan {
    public static final void main(String[] args) {
        new WLPPScan().run();
    }

    private Lexer lexer = new Lexer();

    private void run() {
        Scanner in = new Scanner(System.in);
        while(in.hasNextLine()){
            String line = in.nextLine();
            Token[] tokens;
            tokens = lexer.scan(line);
            for( int i = 0; i < tokens.length; i++ ) {
                System.out.println(tokens[i].kind + " " + tokens[i].lexeme);
            }
        }
        System.out.flush();
    }
}

enum Kind {
        START, 
        ID,
        NUM,
        LPAREN,
        RPAREN,
        LBRACE,
        RBRACE,
        RETURN,
        IF,
        ELSE,
        WHILE,
        PRINTLN,
        WAIN,
        BECOMES,
        INT,
        EQ,
        NE,
        LT,
        GT,
        LE,
        GE,
        PLUS,
        MINUS,
        STAR,
        SLASH,
        PCT,
        COMMA,
        SEMI,
        NEW,
        DELETE,
        LBRACK,
        RBRACK,
        AMP,
        NULL,
        WHITESPACE,
}
    class Token {
        public Kind kind;     // The kind of token.
        public String lexeme; // String representation of the actual token in the
                              // source code.

        public Token(Kind kind, String lexeme) {
            this.kind = kind;
            this.lexeme = lexeme;
        }
    }
class Lexer {
    public Lexer() {
        CharSet whitespace = new Chars("\t\n\r ");
        CharSet letters = new Chars(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        CharSet lettersDigits = new Chars(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
        CharSet digits = new Chars("0123456789");
        CharSet numbers = new Chars("123456789");

        CharSet all = new AllChars(); 

        table = new Transition[] {

                new Transition(State.START, new Chars("i"), State.I),
                new Transition(State.I, new Chars("f"), State.IF),
                new Transition(State.START, new Chars("e"), State.E),
                new Transition(State.E, new Chars("l"), State.EL),
                new Transition(State.EL, new Chars("s"), State.ELS),
                new Transition(State.ELS, new Chars("e"), State.ELSE),
                new Transition(State.START, new Chars("i"), State.I),
                new Transition(State.I, new Chars("n"), State.IN),
                new Transition(State.IN, new Chars("t"), State.INT),
                new Transition(State.START, new Chars("w"), State.W),
                new Transition(State.W, new Chars("h"), State.WH),
                new Transition(State.WH, new Chars("i"), State.WHI),
                new Transition(State.WHI, new Chars("l"), State.WHIL),
                new Transition(State.WHIL, new Chars("e"), State.WHILE),
                new Transition(State.START, new Chars("r"), State.R),
                new Transition(State.R, new Chars("e"), State.RE),
                new Transition(State.RE, new Chars("t"), State.RET),
                new Transition(State.RET, new Chars("u"), State.RETU),
                new Transition(State.RETU, new Chars("r"), State.RETUR),
                new Transition(State.RETUR, new Chars("n"), State.RETURN),
                new Transition(State.START, new Chars("p"), State.P),
                new Transition(State.P, new Chars("r"), State.PR),
                new Transition(State.PR, new Chars("i"), State.PRI),
                new Transition(State.PRI, new Chars("n"), State.PRIN),
                new Transition(State.PRIN, new Chars("t"), State.PRINT),
                new Transition(State.PRINT, new Chars("l"), State.PRINTL),
                new Transition(State.PRINTL, new Chars("n"), State.PRINTLN),
                new Transition(State.START, new Chars("w"), State.W),
                new Transition(State.W, new Chars("a"), State.WA),
                new Transition(State.WA, new Chars("i"), State.WAI),
                new Transition(State.WAI, new Chars("n"), State.WAIN),
                new Transition(State.START, new Chars("n"), State.N),
                new Transition(State.N, new Chars("e"), State.NE),
                new Transition(State.NE, new Chars("w"), State.NEW),
                new Transition(State.START, new Chars("d"), State.D),
                new Transition(State.D, new Chars("e"), State.DE),
                new Transition(State.DE, new Chars("l"), State.DEL),
                new Transition(State.DEL, new Chars("e"), State.DELE),
                new Transition(State.DELE, new Chars("t"), State.DELET),
                new Transition(State.DELET, new Chars("e"), State.DELETE),
                new Transition(State.START, new Chars("N"), State.N),
                new Transition(State.N, new Chars("U"), State.NU),
                new Transition(State.NU, new Chars("L"), State.NUL),
                new Transition(State.NUL, new Chars("L"), State.NULL),

                new Transition(State.START, whitespace, State.WHITESPACE),
                new Transition(State.START, new Chars("/"), State.SLASH),
                new Transition(State.SLASH, new Chars("/"), State.COMMENT),                
                new Transition(State.COMMENT, all, State.COMMENT),

                new Transition(State.START, new Chars(","), State.COMMA),
                new Transition(State.START, new Chars(";"), State.SEMI),

                new Transition(State.START, new Chars("("), State.LPAREN),
                new Transition(State.START, new Chars(")"), State.RPAREN),
                new Transition(State.START, new Chars("{"), State.LBRACE),
                new Transition(State.START, new Chars("}"), State.RBRACE),
                new Transition(State.START, new Chars("["), State.LBRACK),
                new Transition(State.START, new Chars("]"), State.RBRACK),

                new Transition(State.START, new Chars("+"), State.PLUS),
                new Transition(State.START, new Chars("-"), State.MINUS),
                new Transition(State.START, new Chars("*"), State.STAR),
                new Transition(State.START, new Chars("%"), State.PCT),
                new Transition(State.START, new Chars("&"), State.AMP),

                new Transition(State.START, new Chars("="), State.BECOMES),
                new Transition(State.START, new Chars("<"), State.LT),
                new Transition(State.START, new Chars(">"), State.GT),
                new Transition(State.START, new Chars("!"), State.BANG),
                new Transition(State.LT, new Chars("="), State.LE),
                new Transition(State.GT, new Chars("="), State.GE),
                new Transition(State.BECOMES, new Chars("="), State.EQ),
                new Transition(State.BANG, new Chars("="), State.NEQ),

                new Transition(State.I, lettersDigits, State.ID),
                new Transition(State.IF, lettersDigits, State.ID),
                new Transition(State.E, lettersDigits, State.ID),
                new Transition(State.EL, lettersDigits, State.ID),
                new Transition(State.ELS, lettersDigits, State.ID),
                new Transition(State.ELSE, lettersDigits, State.ID),
                new Transition(State.I, lettersDigits, State.ID),
                new Transition(State.IN, lettersDigits, State.ID),
                new Transition(State.INT, lettersDigits, State.ID),
                new Transition(State.E, lettersDigits, State.ID),
                new Transition(State.EL, lettersDigits, State.ID),
                new Transition(State.ELS, lettersDigits, State.ID),
                new Transition(State.ELSE, lettersDigits, State.ID),
                new Transition(State.W, lettersDigits, State.ID),
                new Transition(State.WH, lettersDigits, State.ID),
                new Transition(State.WHI, lettersDigits, State.ID),
                new Transition(State.WHIL, lettersDigits, State.ID),
                new Transition(State.WHILE, lettersDigits, State.ID),
                new Transition(State.R, lettersDigits, State.ID),
                new Transition(State.RE, lettersDigits, State.ID),
                new Transition(State.RET, lettersDigits, State.ID),
                new Transition(State.RETU, lettersDigits, State.ID),
                new Transition(State.RETUR, lettersDigits, State.ID),
                new Transition(State.RETURN, lettersDigits, State.ID),
                new Transition(State.P, lettersDigits, State.ID),
                new Transition(State.PR, lettersDigits, State.ID),
                new Transition(State.PRI, lettersDigits, State.ID),
                new Transition(State.PRIN, lettersDigits, State.ID),
                new Transition(State.PRINT, lettersDigits, State.ID),
                new Transition(State.PRINTL, lettersDigits, State.ID),
                new Transition(State.PRINTLN, lettersDigits, State.ID),
                new Transition(State.W, lettersDigits, State.ID),
                new Transition(State.WA, lettersDigits, State.ID),
                new Transition(State.WAI, lettersDigits, State.ID),
                new Transition(State.WAIN, lettersDigits, State.ID),
                new Transition(State.N, lettersDigits, State.ID),
                new Transition(State.NE, lettersDigits, State.ID),
                new Transition(State.NEW, lettersDigits, State.ID),
                new Transition(State.D, lettersDigits, State.ID),
                new Transition(State.DE, lettersDigits, State.ID),
                new Transition(State.DEL, lettersDigits, State.ID),
                new Transition(State.DELE, lettersDigits, State.ID),
                new Transition(State.DELET, lettersDigits, State.ID),
                new Transition(State.DELETE, lettersDigits, State.ID),
                new Transition(State.N, lettersDigits, State.ID),
                new Transition(State.NU, lettersDigits, State.ID),
                new Transition(State.NUL, lettersDigits, State.ID),
                new Transition(State.NULL, lettersDigits, State.ID),

                new Transition(State.START, letters, State.ID),
                new Transition(State.ID, lettersDigits, State.ID),

                new Transition(State.START, numbers, State.NUM),
                new Transition(State.NUM, digits, State.NUM),
                new Transition(State.START, new Chars("0"), State.ZERO),
                new Transition(State.ZERO, new Chars("0"), State.ZERO),                


        };
    }

    public Token[] scan( String input ) {
        List<Token> ret = new ArrayList<Token>();
        if(input.length() == 0) return new Token[0];
        int i = 0;
        int startIndex = 0;
        State state = State.START;
        while(true) {
            Transition t = null;
            if(i < input.length()) {
                t = findTransition(state, input.charAt(i));
                //if(t!=null) System.err.println(t.fromState + " to " + t.toState);
            }   
            if(t == null) {
                // no more transitions possible

                if(!state.isFinal()) {
                    System.err.println("ERROR in lexing after reading "+input.substring(0, i));
                    System.exit(1);
                }
                if( state.kind != Kind.WHITESPACE ) {
                    ret.add(new Token(state.kind,
                    input.substring(startIndex, i)));
                }
                startIndex = i;
                state = State.START;
                if(i >= input.length()) break;
            } else {
                state = t.toState;
                i++;
             }
         }
         return ret.toArray(new Token[ret.size()]);
     }
     private Transition findTransition(State state, char c) {
         for( int j = 0; j < table.length; j++ ) {
             Transition t = table[j];
             if(t.fromState == state && t.chars.contains(c)) {
                 return t;
             }
         }
         return null;
     }
 
     private static enum State {
        START(null), 
        ID(Kind.ID),
        NUM(Kind.NUM),
        LPAREN(Kind.LPAREN),
        RPAREN(Kind.RPAREN),
        LBRACE(Kind.LBRACE),
        RBRACE(Kind.RBRACE),
        BECOMES(Kind.BECOMES),
        ZERO(Kind.NUM),
        EQ(Kind.EQ),
        NEQ(Kind.NE),
        LT(Kind.LT),
        GT(Kind.GT),
        LE(Kind.LE),
        GE(Kind.GE),
        PLUS(Kind.PLUS),
        MINUS(Kind.MINUS),
        STAR(Kind.STAR),
        SLASH(Kind.SLASH),
        PCT(Kind.PCT),
        COMMA(Kind.COMMA),
        SEMI(Kind.SEMI),
        LBRACK(Kind.LBRACK),
        RBRACK(Kind.RBRACK),
        AMP(Kind.AMP),
        N(Kind.ID),
        NU(Kind.ID),
        NUL(Kind.ID),
        NULL(Kind.NULL),
        R(Kind.ID),
        RE(Kind.ID),
        RET(Kind.ID),
        RETU(Kind.ID),
        RETUR(Kind.ID),
        RETURN(Kind.RETURN),
        I(Kind.ID),
        IF(Kind.IF),
        E(Kind.ID),
        EL(Kind.ID),
        ELS(Kind.ID),
        ELSE(Kind.ELSE),
        W(Kind.ID),
        WH(Kind.ID),
        WHI(Kind.ID),
        WHIL(Kind.ID),
        WHILE(Kind.WHILE),
        P(Kind.ID),
        PR(Kind.ID),
        PRI(Kind.ID),
        PRIN(Kind.ID),
        PRINT(Kind.ID),
        PRINTL(Kind.ID),
        PRINTLN(Kind.PRINTLN),
        WA(Kind.ID),
        WAI(Kind.ID),
        WAIN(Kind.WAIN),
        NE(Kind.ID),
        NEW(Kind.NEW),
        D(Kind.ID),
        DE(Kind.ID),
        DEL(Kind.ID),
        DELE(Kind.ID),
        DELET(Kind.ID),
        DELETE(Kind.DELETE),
        IN(Kind.ID),
        INT(Kind.INT),
        WHITESPACE(Kind.WHITESPACE),
        COMMENT(Kind.WHITESPACE),
        BANG(null);
        State(Kind kind) {
            this.kind = kind;
        }
        Kind kind;
        boolean isFinal() {
            return kind != null;
        }
    }
    private interface CharSet {
        public boolean contains(char newC);
    }
    private class Chars implements CharSet {
        private String chars;
        public Chars(String chars) { this.chars = chars; }
        public boolean contains(char newC) {
            return chars.indexOf(newC) >= 0;
        }
    }
    private class AllChars implements CharSet {
        public boolean contains(char newC) {
            return true;
        }
    }

    private class Transition {
        State fromState;
        CharSet chars;
        State toState;
        Transition(State fromState, CharSet chars, State toState) {
            this.fromState = fromState;
            this.chars = chars;
            this.toState = toState;
        }
    }
    private Transition[] table;
}