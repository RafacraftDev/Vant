package vant;

import iej.node.*;
import java.util.*;
import java.util.regex.*;

/**
 * IRJ – Interactive REPL Java (Interpreter)
 * Author: RafacraftCoder
 * GitHub: https://github.com/RafacraftDev/IEJ
 *
 * Description: Interpreter for IEJ mini-language
 * License: MIT
 */
public class Interpreter {

    static Node printlNode = Sequence.of(
        Literal.of("printl"),
        Whitespace.optional(),
        Parse.of('('),
        Whitespace.optional(),
        Group.of(StringLiteral.of().or(Literal.of("[a-zA-Z_][a-zA-Z0-9_]*"))),
        Whitespace.optional(),
        Parse.of(')'),
        Literal.of(";")
    );

    static Node printNode = Sequence.of(
        Literal.of("print"),
        Whitespace.optional(),
        Parse.of('('),
        Whitespace.optional(),
        Group.of(StringLiteral.of().or(Literal.of("[a-zA-Z_][a-zA-Z0-9_]*"))),
        Whitespace.optional(),
        Parse.of(')'),
        Literal.of(";")
    );

    static Node varNode = Sequence.of(
        Literal.of("var"),
        Whitespace.required(),
        Group.of(Literal.of("[a-zA-Z_][a-zA-Z0-9_]*")),
        Whitespace.optional(),
        Literal.of("="),
        Whitespace.optional(),
        Group.of(StringLiteral.of()
                 .or(Literal.of("[0-9]+"))
                 .or(Literal.of("[a-zA-Z_][a-zA-Z0-9_]*"))
                 .or(Literal.of("Sys.nextl\\(\\)"))),
        Literal.of(";")
    );

    static Scanner sc = new Scanner(System.in);
    static Map<String, Object> variables = new HashMap<>();

    public static void main(String[] args) {
        System.out.println("=== IRJ Interpreter ===");
        System.out.println("Enter your code line by line. Type '-start' to execute:");

        String code = "";
        while (true) {
            String line = sc.nextLine();
            if(line.equals("-start")) break;
            code += line + "\n";
        }

        interpret(code);
    }

    static void interpret(String code) {
        String[] lines = code.split("\n");
        for (String line : lines) {
            line = line.trim();
            if (line.isEmpty()) continue;

            if (line.matches(printlNode.get())) {
                NodeMatcher matcher = NodeMatcher.of(line, printlNode);
                String value = matcher.group(1);
                System.out.println(resolveValue(value));
            } 
            else if (line.matches(printNode.get())) {
                NodeMatcher matcher = NodeMatcher.of(line, printNode);
                String value = matcher.group(1);
                System.out.print(resolveValue(value));
            } 
            else if (line.matches(varNode.get())) {
                NodeMatcher matcher = NodeMatcher.of(line, varNode);
                String name = matcher.group(1);
                String value = matcher.group(2);
                variables.put(name, resolveValue(value));
            } 
            else {
                System.out.println("Unknown command: " + line);
            }
        }
    }

    static Object resolveValue(String value) {
        value = value.trim();
        if (value.equals("Sys.nextl()")) {
            System.out.print("> ");
            return sc.nextLine();
        }
        if (value.startsWith("\"") && value.endsWith("\"")) {
            return value.substring(1, value.length() - 1);
        }
        if (variables.containsKey(value)) {
            return variables.get(value);
        }
        try {
            return Integer.parseInt(value);
        } catch (NumberFormatException e) { }

        // Handle simple addition of numbers or strings
        if (value.contains("+")) {
            String[] parts = value.split("\\+");
            Object left = resolveValue(parts[0].trim());
            Object right = resolveValue(parts[1].trim());
            if (left instanceof Integer && right instanceof Integer) {
                return (Integer) left + (Integer) right;
            } else {
                return String.valueOf(left) + String.valueOf(right);
            }
        }

        return value;
    }
}
