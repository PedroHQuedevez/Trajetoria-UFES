import java.io.PrintWriter;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.antlr.v4.runtime.CharStreams;
import org.antlr.v4.runtime.CommonTokenStream;
import org.antlr.v4.runtime.tree.ParseTree;

import checker.PascalSemanticChecker;
import code.Interpreter;
import codegen.CodegenVisitor;
import parser.PascalLexer;
import parser.PascalParser;

public class Main {

    public static void main(String[] args) throws Exception {
        if (args.length < 1) {
            System.err.println("Uso: java Main <arquivo.pas>");
            System.exit(1);
        }
        String inputFile = args[0];
        String code = new String(Files.readAllBytes(Paths.get(inputFile)));

        // Cria o lexer e parser
        PascalLexer lexer = new PascalLexer(CharStreams.fromString(code));
        CommonTokenStream tokens = new CommonTokenStream(lexer);
        PascalParser parser = new PascalParser(tokens);

        // Gera a árvore sintática
        ParseTree tree = parser.program();

        // Visita a árvore
        PascalSemanticChecker visitor = new PascalSemanticChecker();
        visitor.visit(tree);

        visitor.printStrings();
        System.out.println("\n");
        visitor.printSymbols();
        System.out.println("\n");
        visitor.printAST();
        
        // Executa o interpretador
        System.out.println("\n=== EXECUTANDO O PROGRAMA ===\n");
        Interpreter interpreter = new Interpreter(visitor.getStrTable(), visitor.getVarTable());
        interpreter.execute(visitor.getAST());
        
        // Gera código Jasmin
        System.out.println("\n=== GERANDO CÓDIGO JASMIN ===\n");
        CodegenVisitor codegen = new CodegenVisitor();
        String jasminCode = codegen.generate(visitor.getAST());
        
        // Determina o nome do arquivo .j baseado no arquivo de entrada
        String baseName = inputFile.substring(0, inputFile.lastIndexOf('.'));
        String outputFile = baseName + ".j";
        
        // Salva o código Jasmin no arquivo .j
        try (PrintWriter writer = new PrintWriter(outputFile)) {
            writer.print(jasminCode);
            System.out.println("Código Jasmin gerado com sucesso em: " + outputFile);
        } catch (Exception e) {
            System.err.println("Erro ao salvar o arquivo .j: " + e.getMessage());
        }
        
        // Exibe o código gerado na tela
        System.out.println("\n=== CÓDIGO JASMIN GERADO ===\n");
        System.out.println(jasminCode);
    }
}
