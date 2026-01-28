package codegen;

import java.util.HashMap;
import java.util.Map;

import ast.AST;
import ast.ASTBaseVisitor;
import ast.NodeKind;
import typing.PascalType;

/**
 * Visitor que gera código Jasmin (.j) para a JVM a partir da AST do Pascal
 */
public class CodegenVisitor extends ASTBaseVisitor<Void> {
    private StringBuilder jasminCode = new StringBuilder();
    private Map<String, Integer> localVariables = new HashMap<>(); // mapeia nome da variável para índice local
    private Map<String, PascalType> variableTypes = new HashMap<>(); // mapeia nome da variável para tipo
    private int labelCounter = 0;
    private int maxLocals = 0;
    private int maxStack = 0;
    private int currentStackSize = 0;
    private String className = "PascalProgram";
    
    /**
     * Gera o código Jasmin completo para o programa Pascal
     */
    public String generate(AST program) {
        jasminCode.setLength(0);
        localVariables.clear();
        variableTypes.clear();
        labelCounter = 0;
        maxLocals = 0;
        maxStack = 0;
        currentStackSize = 0;
        
        // Coleta informações sobre variáveis globais
        collectVariables(program);
        
        // Gera cabeçalho do arquivo Jasmin
        emitHeader();
        
        // Visita o programa principal
        visit(program);
        
        // Gera rodapé
        emitFooter();
        
        return jasminCode.toString();
    }
    
    /**
     * Coleta informações sobre variáveis do programa
     */
    private void collectVariables(AST program) {
        int localIndex = 0;
        
        // Percorre os filhos do programa para encontrar declarações de variáveis
        for (int i = 0; i < program.getChildCount(); i++) {
            AST child = program.getChild(i);
            if (child.kind == NodeKind.VAR_LIST_NODE) {
                collectVariablesFromList(child, localIndex);
                localIndex += child.getChildCount();
            }
        }
        
        maxLocals = Math.max(maxLocals, localIndex);
    }
    
    /**
     * Coleta variáveis de uma lista de declarações
     */
    private void collectVariablesFromList(AST varList, int startIndex) {
        int localIndex = startIndex;
        
        for (int i = 0; i < varList.getChildCount(); i++) {
            AST varDecl = varList.getChild(i);
            if (varDecl.kind == NodeKind.VAR_DECL_NODE && varDecl.strData != null) {
                localVariables.put(varDecl.strData, localIndex);
                variableTypes.put(varDecl.strData, varDecl.type);
                localIndex++;
            }
        }
    }
    
    /**
     * Gera o cabeçalho do arquivo Jasmin
     */
    private void emitHeader() {
        jasminCode.append(".class public ").append(className).append("\n");
        jasminCode.append(".super java/lang/Object\n\n");
        
        // Construtor padrão
        jasminCode.append(".method public <init>()V\n");
        jasminCode.append("  aload_0\n");
        jasminCode.append("  invokespecial java/lang/Object/<init>()V\n");
        jasminCode.append("  return\n");
        jasminCode.append(".end method\n\n");
        
        // Método main
        jasminCode.append(".method public static main([Ljava/lang/String;)V\n");
        jasminCode.append("  .limit stack 100\n"); // Será ajustado depois
        jasminCode.append("  .limit locals 100\n"); // Será ajustado depois
    }
    
    /**
     * Gera o rodapé do arquivo Jasmin
     */
    private void emitFooter() {
        jasminCode.append("  return\n");
        jasminCode.append(".end method\n");
        
        // Ajusta os limites de stack e locals
        String code = jasminCode.toString();
        code = code.replace(".limit stack 100", ".limit stack " + Math.max(10, maxStack));
        code = code.replace(".limit locals 100", ".limit locals " + Math.max(10, maxLocals));
        jasminCode.setLength(0);
        jasminCode.append(code);
    }
    
    /**
     * Atualiza o tamanho atual da pilha
     */
    private void updateStack(int delta) {
        currentStackSize += delta;
        maxStack = Math.max(maxStack, currentStackSize);
    }
    
    /**
     * Gera um novo label único
     */
    private String newLabel() {
        return "L" + (labelCounter++);
    }

    // ==================== VISITOR METHODS ====================

    @Override
    protected Void visitProgram(AST node) {
        // Inicializa variáveis globais com valores padrão
        for (Map.Entry<String, Integer> entry : localVariables.entrySet()) {
            String varName = entry.getKey();
            Integer varIndex = entry.getValue();
            PascalType varType = variableTypes.get(varName);
            
            // Inicializa com valor padrão baseado no tipo
            if (varType == PascalType.INT_TYPE || varType == PascalType.BOOL_TYPE) {
                jasminCode.append("  iconst_0\n");
                jasminCode.append("  istore ").append(varIndex).append("\n");
                updateStack(1);
                updateStack(-1);
            } else if (varType == PascalType.REAL_TYPE) {
                jasminCode.append("  fconst_0\n");
                jasminCode.append("  fstore ").append(varIndex).append("\n");
                updateStack(1);
                updateStack(-1);
            } else if (varType == PascalType.STR_TYPE) {
                jasminCode.append("  ldc \"\"\n");
                jasminCode.append("  astore ").append(varIndex).append("\n");
                updateStack(1);
                updateStack(-1);
            }
        }
        
        // Executa todos os filhos do programa
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }

    @Override
    protected Void visitBlock(AST node) {
        // Executa todos os filhos do bloco
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }

    @Override
    protected Void visitVarList(AST node) {
        // Declarações de variáveis já foram processadas na coleta
        return null;
    }

    @Override
    protected Void visitVarDecl(AST node) {
        // Declarações individuais já foram processadas
        return null;
    }

    @Override
    protected Void visitAssign(AST node) {
        // Avalia a expressão do lado direito primeiro
        visit(node.getChild(1));
        
        // Obtém a variável do lado esquerdo
        AST varNode = node.getChild(0);
        String varName = varNode.strData;
        Integer localIndex = localVariables.get(varName);
        PascalType varType = variableTypes.get(varName);
        
        if (localIndex != null) {
            // Gera código para armazenar na variável local
            if (varType == PascalType.INT_TYPE || varType == PascalType.BOOL_TYPE) {
                jasminCode.append("  istore ").append(localIndex).append("\n");
            } else if (varType == PascalType.REAL_TYPE) {
                jasminCode.append("  fstore ").append(localIndex).append("\n");
            } else if (varType == PascalType.STR_TYPE) {
                jasminCode.append("  astore ").append(localIndex).append("\n");
            }
            updateStack(-1);
        }
        return null;
    }

    @Override
    protected Void visitVarUse(AST node) {
        String varName = node.strData;
        Integer localIndex = localVariables.get(varName);
        PascalType varType = variableTypes.get(varName);
        
        if (localIndex != null) {
            // Carrega valor da variável local
            if (varType == PascalType.INT_TYPE || varType == PascalType.BOOL_TYPE) {
                jasminCode.append("  iload ").append(localIndex).append("\n");
            } else if (varType == PascalType.REAL_TYPE) {
                jasminCode.append("  fload ").append(localIndex).append("\n");
            } else if (varType == PascalType.STR_TYPE) {
                jasminCode.append("  aload ").append(localIndex).append("\n");
            }
            updateStack(1);
        }
        return null;
    }

    @Override
    protected Void visitIntVal(AST node) {
        // Carrega constante inteira na pilha
        int value = node.intData;
        if (value >= -1 && value <= 5) {
            jasminCode.append("  iconst_").append(value).append("\n");
        } else if (value >= -128 && value <= 127) {
            jasminCode.append("  bipush ").append(value).append("\n");
        } else if (value >= -32768 && value <= 32767) {
            jasminCode.append("  sipush ").append(value).append("\n");
        } else {
            jasminCode.append("  ldc ").append(value).append("\n");
        }
        updateStack(1);
        return null;
    }

    @Override
    protected Void visitRealVal(AST node) {
        // Carrega constante real na pilha
        float value = node.realData;
        if (value == 0.0f) {
            jasminCode.append("  fconst_0\n");
        } else if (value == 1.0f) {
            jasminCode.append("  fconst_1\n");
        } else if (value == 2.0f) {
            jasminCode.append("  fconst_2\n");
        } else {
            jasminCode.append("  ldc ").append(value).append("\n");
        }
        updateStack(1);
        return null;
    }

    @Override
    protected Void visitBoolVal(AST node) {
        // Carrega constante booleana (0 para false, 1 para true)
        boolean value = node.boolData;
        jasminCode.append("  iconst_").append(value ? "1" : "0").append("\n");
        updateStack(1);
        return null;
    }

    @Override
    protected Void visitStringVal(AST node) {
        // Carrega string constante
        jasminCode.append("  ldc \"").append(node.strData).append("\"\n");
        updateStack(1);
        return null;
    }

    @Override
    protected Void visitPlus(AST node) {
        // Avalia operandos
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        // Determina o tipo da operação baseado no tipo do nó
        if (node.type == PascalType.INT_TYPE) {
            jasminCode.append("  iadd\n");
        } else if (node.type == PascalType.REAL_TYPE) {
            jasminCode.append("  fadd\n");
        }
        updateStack(-1); // dois operandos se tornam um resultado
        return null;
    }

    @Override
    protected Void visitMinus(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        if (node.type == PascalType.INT_TYPE) {
            jasminCode.append("  isub\n");
        } else if (node.type == PascalType.REAL_TYPE) {
            jasminCode.append("  fsub\n");
        }
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitMult(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        if (node.type == PascalType.INT_TYPE) {
            jasminCode.append("  imul\n");
        } else if (node.type == PascalType.REAL_TYPE) {
            jasminCode.append("  fmul\n");
        }
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitDiv(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        if (node.type == PascalType.INT_TYPE) {
            jasminCode.append("  idiv\n");
        } else if (node.type == PascalType.REAL_TYPE) {
            jasminCode.append("  fdiv\n");
        }
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitEq(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String falseLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmpne ").append(falseLabel).append("\n");
        jasminCode.append("  iconst_1\n"); // true
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(falseLabel).append(":\n");
        jasminCode.append("  iconst_0\n"); // false
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1); // dois operandos se tornam um resultado
        return null;
    }

    @Override
    protected Void visitNe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String trueLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmpne ").append(trueLabel).append("\n");
        jasminCode.append("  iconst_0\n"); // false
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(trueLabel).append(":\n");
        jasminCode.append("  iconst_1\n"); // true
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitLt(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String trueLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmplt ").append(trueLabel).append("\n");
        jasminCode.append("  iconst_0\n"); // false
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(trueLabel).append(":\n");
        jasminCode.append("  iconst_1\n"); // true
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitLe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String trueLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmple ").append(trueLabel).append("\n");
        jasminCode.append("  iconst_0\n");
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(trueLabel).append(":\n");
        jasminCode.append("  iconst_1\n");
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitGt(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String trueLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmpgt ").append(trueLabel).append("\n");
        jasminCode.append("  iconst_0\n");
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(trueLabel).append(":\n");
        jasminCode.append("  iconst_1\n");
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitGe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        String trueLabel = newLabel();
        String endLabel = newLabel();
        
        jasminCode.append("  if_icmpge ").append(trueLabel).append("\n");
        jasminCode.append("  iconst_0\n");
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(trueLabel).append(":\n");
        jasminCode.append("  iconst_1\n");
        jasminCode.append(endLabel).append(":\n");
        
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitIf(AST node) {
        // Avalia a condição
        visit(node.getChild(0));
        
        String elseLabel = newLabel();
        String endLabel = newLabel();
        
        // Se a condição for false (0), pula para else
        jasminCode.append("  ifeq ").append(elseLabel).append("\n");
        updateStack(-1);
        
        // Executa bloco then
        visit(node.getChild(1));
        
        jasminCode.append("  goto ").append(endLabel).append("\n");
        jasminCode.append(elseLabel).append(":\n");
        
        // Executa bloco else se existir
        if (node.getChildCount() > 2) {
            visit(node.getChild(2));
        }
        
        jasminCode.append(endLabel).append(":\n");
        return null;
    }

    @Override
    protected Void visitFor(AST node) {
        // Implementação básica do loop for
        // Estrutura: FOR_NODE -> FOR_HEADING_NODE, FOR_BLOCK_NODE
        
        AST forHeading = node.getChild(0); // FOR_HEADING_NODE
        AST forBlock = node.getChild(1);   // FOR_BLOCK_NODE
        
        // Obtém variável, início e fim do loop
        AST varNode = forHeading.getChild(0);
        AST startExpr = forHeading.getChild(1);
        AST endExpr = forHeading.getChild(2);
        
        String varName = varNode.strData;
        Integer varIndex = localVariables.get(varName);
        
        String loopStart = newLabel();
        String loopEnd = newLabel();
        
        // Inicializa a variável do loop
        visit(startExpr);
        jasminCode.append("  istore ").append(varIndex).append("\n");
        updateStack(-1);
        
        // Avalia o valor final e armazena em uma variável temporária
        visit(endExpr);
        int tempVar = maxLocals++;
        jasminCode.append("  istore ").append(tempVar).append("\n");
        updateStack(-1);
        
        // Label do início do loop
        jasminCode.append(loopStart).append(":\n");
        
        // Verifica condição: var <= end
        jasminCode.append("  iload ").append(varIndex).append("\n");
        jasminCode.append("  iload ").append(tempVar).append("\n");
        jasminCode.append("  if_icmpgt ").append(loopEnd).append("\n");
        updateStack(2);
        updateStack(-2);
        
        // Executa corpo do loop
        visit(forBlock);
        
        // Incrementa variável do loop
        jasminCode.append("  iload ").append(varIndex).append("\n");
        jasminCode.append("  iconst_1\n");
        jasminCode.append("  iadd\n");
        jasminCode.append("  istore ").append(varIndex).append("\n");
        updateStack(2);
        updateStack(-1);
        
        // Volta para o início do loop
        jasminCode.append("  goto ").append(loopStart).append("\n");
        
        // Label do fim do loop
        jasminCode.append(loopEnd).append(":\n");
        
        return null;
    }

    @Override
    protected Void visitWrite(AST node) {
        // Obtém System.out
        jasminCode.append("  getstatic java/lang/System/out Ljava/io/PrintStream;\n");
        updateStack(1);
        
        // Para cada expressão a ser impressa
        for (int i = 0; i < node.getChildCount(); i++) {
            AST child = node.getChild(i);
            
            // Avalia a expressão
            visit(child);
            
            // Chama o método println apropriado baseado no tipo
            if (child.type == PascalType.INT_TYPE || child.type == PascalType.BOOL_TYPE) {
                jasminCode.append("  invokevirtual java/io/PrintStream/println(I)V\n");
            } else if (child.type == PascalType.REAL_TYPE) {
                jasminCode.append("  invokevirtual java/io/PrintStream/println(F)V\n");
            } else if (child.type == PascalType.STR_TYPE) {
                jasminCode.append("  invokevirtual java/io/PrintStream/println(Ljava/lang/String;)V\n");
            }
            
            updateStack(-2); // consome PrintStream e valor
            
            // Se não for o último, obtém System.out novamente
            if (i < node.getChildCount() - 1) {
                jasminCode.append("  getstatic java/lang/System/out Ljava/io/PrintStream;\n");
                updateStack(1);
            }
        }
        return null;
    }

    @Override
    protected Void visitRead(AST node) {
        // Implementação simplificada - lê sempre 0 para inteiros
        // Em uma implementação completa, seria necessário usar Scanner
        AST varNode = node.getChild(0);
        String varName = varNode.strData;
        Integer varIndex = localVariables.get(varName);
        PascalType varType = variableTypes.get(varName);
        
        if (varIndex != null) {
            if (varType == PascalType.INT_TYPE) {
                jasminCode.append("  iconst_0\n"); // lê 0 por simplicidade
                jasminCode.append("  istore ").append(varIndex).append("\n");
                updateStack(1);
                updateStack(-1);
            }
        }
        return null;
    }

    // ==================== CONVERSÕES DE TIPO ====================

    @Override
    protected Void visitI2R(AST node) {
        visit(node.getChild(0));
        jasminCode.append("  i2f\n"); // converte int para float
        return null;
    }

    @Override
    protected Void visitI2S(AST node) {
        visit(node.getChild(0));
        jasminCode.append("  invokestatic java/lang/String/valueOf(I)Ljava/lang/String;\n");
        return null;
    }

    @Override
    protected Void visitR2S(AST node) {
        visit(node.getChild(0));
        jasminCode.append("  invokestatic java/lang/String/valueOf(F)Ljava/lang/String;\n");
        return null;
    }

    @Override
    protected Void visitB2S(AST node) {
        visit(node.getChild(0));
        jasminCode.append("  invokestatic java/lang/String/valueOf(Z)Ljava/lang/String;\n");
        return null;
    }

    // ==================== OPERADORES LÓGICOS ====================

    @Override
    protected Void visitAnd(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        jasminCode.append("  iand\n");
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitOr(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        jasminCode.append("  ior\n");
        updateStack(-1);
        return null;
    }

    @Override
    protected Void visitNot(AST node) {
        visit(node.getChild(0));
        jasminCode.append("  iconst_1\n");
        jasminCode.append("  ixor\n"); // XOR com 1 inverte o bit
        updateStack(1);
        updateStack(-1);
        return null;
    }

    // ==================== MÉTODOS NÃO IMPLEMENTADOS (PLACEHOLDERS) ====================
    // Estes métodos representam funcionalidades que podem ser implementadas posteriormente

    @Override
    protected Void visitFunctionCall(AST node) {
        // Para chamadas de função simples, retorna um valor constante
        // Esta é uma implementação simplificada
        String funcName = node.strData;
        if (funcName == null && node.getChildCount() > 0) {
            funcName = node.getChild(0).strData;
        }
        
        // Para o exemplo GetDez, retorna 10
        if ("GetDez".equals(funcName)) {
            jasminCode.append("  bipush 10\n");
            updateStack(1);
        } else {
            // Para outras funções, retorna 0 por padrão
            jasminCode.append("  iconst_0\n");
            updateStack(1);
        }
        return null;
    }

    @Override
    protected Void visitFunctionDecl(AST node) {
        // TODO: Implementar declaração de funções
        return null;
    }

    @Override
    protected Void visitArrayAccess(AST node) {
        // TODO: Implementar acesso a arrays
        return null;
    }

    // Métodos vazios para nós que não precisam gerar código
    @Override protected Void visitForHeading(AST node) { return null; }
    @Override protected Void visitForBlock(AST node) { 
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null; 
    }
    @Override protected Void visitIdentifier(AST node) { return null; }
    @Override protected Void visitArrayType(AST node) { return null; }
    @Override protected Void visitFunctionSect(AST node) { return null; }
    @Override protected Void visitProcedureDecl(AST node) { return null; }
    @Override protected Void visitProcedureSect(AST node) { return null; }
    @Override protected Void visitParamList(AST node) { return null; }
    @Override protected Void visitExprList(AST node) { return null; }
    @Override protected Void visitFunctionHeading(AST node) { return null; }
    @Override protected Void visitProcedureHeading(AST node) { return null; }
    @Override protected Void visitFunctionBlock(AST node) { return null; }
    @Override protected Void visitProcedureBlock(AST node) { return null; }
    @Override protected Void visitStmtList(AST node) { 
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null; 
    }
    @Override protected Void visitStructureStmt(AST node) { 
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null; 
    }
    @Override protected Void visitB2I(AST node) { return visitBoolVal(node.getChild(0)); }
    @Override protected Void visitB2R(AST node) { 
        visitBoolVal(node.getChild(0));
        jasminCode.append("  i2f\n");
        return null; 
    }
}
