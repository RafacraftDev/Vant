package vant.lexer;

import java.util.*;

public class Lexer {

    private String input;
    private int pos = 0;

    public Lexer(String input) {
        this.input = input;
    }

    public List<Token> tokenize() {
        List<Token> tokens = new ArrayList<>();

        while (pos < input.length()) {
            char current = input.charAt(pos);

            if (Character.isWhitespace(current)) {
                pos++;
                continue;
            }

            if (Character.isLetter(current)) {
                String word = readWord();
                tokens.add(keyword(word));
                continue;
            }

            if (Character.isDigit(current)) {
                tokens.add(new Token(Token.Type.NUMBER, readNumber()));
                continue;
            }

            if (current == '"') {
                tokens.add(new Token(Token.Type.STRING, readString()));
                continue;
            }

            switch (current) {
                case '=':
                    tokens.add(new Token(Token.Type.EQUAL, "="));
                    break;
                case '+':
                    tokens.add(new Token(Token.Type.PLUS, "+"));
                    break;
                case ';':
                    tokens.add(new Token(Token.Type.SEMICOLON, ";"));
                    break;
                case '(':
                    tokens.add(new Token(Token.Type.LPAREN, "("));
                    break;
                case ')':
                    tokens.add(new Token(Token.Type.RPAREN, ")"));
                    break;
                case '{':
                    tokens.add(new Token(Token.Type.LBRACE, "{"));
                    break;
                case '}':
                    tokens.add(new Token(Token.Type.RBRACE, "}"));
                    break;
            }

            pos++;
        }

        tokens.add(new Token(Token.Type.EOF, ""));
        return tokens;
    }

    private String readWord() {
        int start = pos;
        while (pos < input.length() && Character.isLetterOrDigit(input.charAt(pos))) {
            pos++;
        }
        return input.substring(start, pos);
    }

    private String readNumber() {
        int start = pos;
        while (pos < input.length() && Character.isDigit(input.charAt(pos))) {
            pos++;
        }
        return input.substring(start, pos);
    }

    private String readString() {
        pos++;
        int start = pos;
        while (input.charAt(pos) != '"') {
            pos++;
        }
        String str = input.substring(start, pos);
        pos++;
        return str;
    }

    private Token keyword(String word) {
        switch (word) {
			case "let": return new Token(Token.Type.LET, word);
            case "const": return new Token(Token.Type.CONST, word);
            case "func": return new Token(Token.Type.FUN, word);
            case "if": return new Token(Token.Type.IF, word);
            case "else": return new Token(Token.Type.ELSE, word);
			case "return": return new Token(Token.Type.RETURN, word);
            default: return new Token(Token.Type.IDENTIFIER, word);
        }
    }
}
