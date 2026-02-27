package vant;

import vant.executors.*;
import vant.lexer.*;
import java.util.List;

public class Vant {

    private Environment env = new Environment();
    public String outputBuffer = ""; // Para capturar los cout

    public void eval(String code) {
        Lexer lexer = new Lexer(code);
        List<Token> tokens = lexer.tokenize();
        interpret(tokens, env);
    }

    // El corazón del lenguaje: el Loop de Ejecución
    public Object interpret(List<Token> tokens, Environment localEnv) {

        for (int i = 0; i < tokens.size(); i++) {
            Token token = tokens.get(i);

            // 1. Declaración de Clases/Funciones (def)
            if (token.type == Token.Type.DEF) {
                // El Executor maneja la lógica y nos devuelve la nueva posición del índice
                i = MethodExecutor.declare(token, i, tokens, localEnv);
                continue;
            }

            // 2. Control de Flujo (if)
            if (token.type == Token.Type.IF) {
                i = IfExecutor.execute(tokens, i, localEnv, this);
                continue;
            }

            // 3. Llamadas a funciones y Print (cout)
            if (token.type == Token.Type.IDENTIFIER && i + 1 < tokens.size()
                    && tokens.get(i + 1).type == Token.Type.LPAREN) {

                if (token.value.equals("cout")) {
                    List<Token> args = TokenParser.parseArgs(tokens, i + 2);
                    for (Token arg : args) {
                        // Resolvemos el valor (si es variable, string, etc.)
                        Object val = ValueResolver.resolve(arg, localEnv);
                        outputBuffer += val + "\n";
                        System.out.println(val); // Imprimir en consola real
                    }
                    i = TokenParser.findClosingParen(tokens, i + 2);
                } else {
                    VFunction fn = env.getFunction(token.value);
                    if (fn != null) {
                        List<Token> args = TokenParser.parseArgs(tokens, i + 2);
                        Object res = MethodExecutor.call(fn, args, env, localEnv);
                        if (res != null) return res;
                        i = TokenParser.findClosingParen(tokens, i + 2);
                    }
                }
            }

            // 4. Variables (var para dinámicas, val para constantes)
            if (token.type == Token.Type.VAR) {
                i = VarExecutor.handle(tokens, i, localEnv);
            } 
            else if (token.type == Token.Type.VAL) {
                i = ValExecutor.handle(tokens, i, localEnv);
            }

            // 5. Retorno de valores
            if (token.type == Token.Type.RETURN) {
                if (i + 1 < tokens.size()) {
                    return ValueResolver.resolve(tokens.get(i + 1), localEnv);
                }
                return null;
            }
        }
        return null;
    }
}
