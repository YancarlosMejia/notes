import java.util.*;
import java.math.*;

/** A sample main class demonstrating the use of the Lexer.
 * This main class just outputs each line in the input, followed by
 * the tokens returned by the lexer for that line.
 *
 * @version 071011.0
 */
public class Asm {
    public static final void main(String[] args) {
        new Asm().run();
    }

    private Lexer lexer = new Lexer();

    private void run() {
        Scanner in = new Scanner(System.in);
        while(in.hasNextLine()) {
            String line = in.nextLine();

            // Scan the line into an array of tokens.
            Token[] tokens;
            tokens = lexer.scan(line);

            // Print the tokens produced by the scanner
            for( int i = 0; i < tokens.length; i++ ) {
                System.err.println("  Token: "+tokens[i]);
            }
        }
        System.out.flush();
    }
}

/** The various kinds of tokens. */
enum Kind {
    ID,         // Opcode or identifier (use of a label)
    INT,        // Decimal integer
    HEXINT,     // Hexadecimal integer
    REGISTER,   // Register number
    COMMA,      // Comma
    LPAREN,     // (
    RPAREN,     // )
    LABEL,      // Declaration of a label (with a colon)
    DOTWORD,    // .word directive
    WHITESPACE; // Whitespace
}

/** Representation of a token. */
class Token {
    public Kind kind;     // The kind of token.
    public String lexeme; // String representation of the actual token in the
                          // source code.

    public Token(Kind kind, String lexeme) {
        this.kind = kind;
        this.lexeme = lexeme;
    }
    public String toString() {
        return kind+" {"+lexeme+"}";
    }
    /** Returns an integer representation of the token. For tokens of kind
     * INT (decimal integer constant) and HEXINT (hexadecimal integer
     * constant), returns the integer constant. For tokens of kind
     * REGISTER, returns the register number.
     */
    public int toInt() {
        if(kind == Kind.INT) return parseLiteral(lexeme, 10, 32);
        else if(kind == Kind.HEXINT) return parseLiteral(lexeme.substring(2), 16, 32);
        else if(kind == Kind.REGISTER) return parseLiteral(lexeme.substring(1), 10, 5);
        else {
            System.err.println("ERROR in to-int conversion.");
            System.exit(1);
            return 0;
        }
    }
    private int parseLiteral(String s, int base, int bits) {
        BigInteger x = new BigInteger(s, base);
        if(x.signum() > 0) {
            if(x.bitLength() > bits) {
                System.err.println("ERROR in parsing: constant out of range: "+s);
                System.exit(1);
            }
        } else if(x.signum() < 0) {
            if(x.negate().bitLength() > bits-1
            && x.negate().subtract(new BigInteger("1")).bitLength() > bits-1) {
                System.err.println("ERROR in parsing: constant out of range: "+s);
                System.exit(1);
            }
        }
        return (int) (x.longValue() & ((1L << bits) - 1));
    }
}

/** Lexer -- reads an input line, and partitions it into a list of tokens. */
class Lexer {
    public Lexer() {
        CharSet whitespace = new Chars("\t\n\r ");
        CharSet letters = new Chars(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
        CharSet lettersDigits = new Chars(
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
        CharSet digits = new Chars("0123456789");
        CharSet hexDigits = new Chars("0123456789ABCDEFabcdef");
        CharSet oneToNine = new Chars("123456789");
        CharSet all = new AllChars(); 

        table = new Transition[] {
                new Transition(State.START, whitespace, State.WHITESPACE),
                new Transition(State.START, letters, State.ID),
                new Transition(State.ID, lettersDigits, State.ID),
                new Transition(State.START, oneToNine, State.INT),
                new Transition(State.INT, digits, State.INT),
                new Transition(State.START, new Chars("-"), State.MINUS),
                new Transition(State.MINUS, digits, State.INT),
                new Transition(State.START, new Chars(","), State.COMMA),
                new Transition(State.START, new Chars("("), State.LPAREN),
                new Transition(State.START, new Chars(")"), State.RPAREN),
                new Transition(State.START, new Chars("$"), State.DOLLAR),
                new Transition(State.DOLLAR, digits, State.REGISTER),
                new Transition(State.REGISTER, digits, State.REGISTER),
                new Transition(State.START, new Chars("0"), State.ZERO),
                new Transition(State.ZERO, new Chars("x"), State.ZEROX),
                new Transition(State.ZERO, digits, State.INT),
                new Transition(State.ZEROX, hexDigits, State.HEXINT),
                new Transition(State.HEXINT, hexDigits, State.HEXINT),
                new Transition(State.ID, new Chars(":"), State.LABEL),
                new Transition(State.START, new Chars(";"), State.COMMENT),
                new Transition(State.START, new Chars("."), State.DOT),
                new Transition(State.DOT, new Chars("w"), State.DOTW),
                new Transition(State.DOTW, new Chars("o"), State.DOTWO),
                new Transition(State.DOTWO, new Chars("r"), State.DOTWOR),
                new Transition(State.DOTWOR, new Chars("d"), State.DOTWORD),
                new Transition(State.COMMENT, all, State.COMMENT)
        };
    }
    /** Partitions the line passed in as input into an array of tokens.
     * The array of tokens is returned.
     */
    public Token[] scan( String input ) {
        List<Token> ret = new ArrayList<Token>();
        if(input.length() == 0) return new Token[0];
        int i = 0;
        int startIndex = 0;
        State state = State.START;
        while(true) {
            Transition t = null;
            if(i < input.length()) t = findTransition(state, input.charAt(i));
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

    ///////////////////////////////////////////////////////////////
    // END OF PUBLIC METHODS
    ///////////////////////////////////////////////////////////////

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
        DOLLAR(null),
        MINUS(null),
        REGISTER(Kind.REGISTER),
        INT(Kind.INT),
        ID(Kind.ID),
        LABEL(Kind.LABEL),
        COMMA(Kind.COMMA),
        LPAREN(Kind.LPAREN),
        RPAREN(Kind.RPAREN),
        ZERO(Kind.INT),
        ZEROX(null),
        HEXINT(Kind.HEXINT),
        COMMENT(Kind.WHITESPACE),
        DOT(null),
        DOTW(null),
        DOTWO(null),
        DOTWOR(null),
        DOTWORD(Kind.DOTWORD),
        WHITESPACE(Kind.WHITESPACE);
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
