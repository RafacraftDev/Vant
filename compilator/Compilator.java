package compilator;

import java.io.File;
import java.io.IOException;
import java.nio.file.Files;

public class Compilator {
    Token sigToken = Token.NONE;
  
    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Err: Use 'java compilator.Compilator <file.vant>'");
            // En Java, 'return' no devuelve excepciones, se usa 'throw'
            throw new Exception("No args provided");
        }
        
        String file_name = args[0];
        System.out.println("> reading " + file_name + "...");
        File fl = new File(file_name);
        
        // Corregido: 'exists()' es un método, no una variable
        if (!fl.exists()) {
            System.err.println("Err: file doesn't exist");
            throw new Exception("File not found: " + file_name);
        } 
        
        process(fl);
    }

    private static void process(File fl) {
        String code = readFile(fl);
        if (code == null || code.trim().isEmpty()) {
            System.out.println("> File is empty, skipping...");
            return;
        }
        
        System.out.println("> Processing Vant code...");
        String result = """
           import { vant_lang } from "./vant";
        """;
        List<Token> tokens = lines.tokenize();
        for (Token token : tokens) {
          if (token.tt == Token.CLASS) {
            sigType = Token.IDENTIFIER;
            result += " class";
          }
          if (token.tt == Token.IDENTIFIER) {
            sigType = Token.NONE;
            result += " " + token.value;
        }
    }

    private static String readFile(File fl) {
        try {
            // Forma moderna y rápida de leer todo el archivo en Java
            return Files.readString(fl.toPath());
        } catch (IOException e) {
            System.err.println("Err: Could not read file");
            return "";
        }
    }
}
