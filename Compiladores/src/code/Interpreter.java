package code;

import java.util.Map;
import java.util.Scanner;

import ast.AST;
import ast.ASTBaseVisitor;
import ast.NodeKind;
import tables.strTable;
import tables.varTable;
import typing.PascalType;

public class Interpreter extends ASTBaseVisitor<Void> {
    private final DataStack stack;
    private Memory memory;  // Removed final to allow reassignment
    private final varTable vt;
    private final Scanner in; // Para leitura de stdin
    
    // Para suporte a funções e procedimentos
    private boolean returnCalled = false;
    
    // Mapa para armazenar os corpos das funções da AST
    private final Map<String, AST> functionBodies = new java.util.HashMap<>();

    public Interpreter(strTable st, varTable vt) {
        this.stack = new DataStack();
        this.memory = new Memory(vt);
        this.in = new Scanner(System.in);
        this.vt = vt;
    }

    // Métodos auxiliares para conversão de tipos
    private Value convertValue(Value value, PascalType targetType) {
        Object data = value.getData();
        PascalType sourceType = value.getType();
        
        if (sourceType == targetType) {
            return value;
        }
        
        switch (targetType) {
            case INT_TYPE:
                if (sourceType == PascalType.REAL_TYPE) {
                    return new Value(PascalType.INT_TYPE, Math.round((Float) data));
                } else if (sourceType == PascalType.BOOL_TYPE) {
                    return new Value(PascalType.INT_TYPE, (Boolean) data ? 1 : 0);
                }
                break;
            case REAL_TYPE:
                if (sourceType == PascalType.INT_TYPE) {
                    return new Value(PascalType.REAL_TYPE, ((Integer) data).floatValue());
                } else if (sourceType == PascalType.BOOL_TYPE) {
                    return new Value(PascalType.REAL_TYPE, (Boolean) data ? 1.0f : 0.0f);
                }
                break;
            case STR_TYPE:
                return new Value(PascalType.STR_TYPE, data.toString());
            case BOOL_TYPE:
                if (sourceType == PascalType.INT_TYPE) {
                    return new Value(PascalType.BOOL_TYPE, (Integer) data != 0);
                } else if (sourceType == PascalType.REAL_TYPE) {
                    return new Value(PascalType.BOOL_TYPE, (Float) data != 0.0f);
                }
                break;
            case FUNCTION_TYPE:
            case PROCEDURE_TYPE:
            case NO_TYPE:
            default:
                break;
        }
        
        throw new RuntimeException("Cannot convert from " + sourceType + " to " + targetType);
    }

    // Implementação dos métodos visit para cada tipo de nó da AST
    @Override
    protected Void visitProgram(AST node) {
        // Inicializa variáveis globais na memória
        for (String varName : vt.getAllVarNames()) {
            varTable.Entry entry = vt.lookup(varName);
            if (entry != null) {
                if (entry.kind == varTable.SymbolKind.ARRAY) {
                    Value arrayValue = new Value(entry.type, true);
                    memory.addValue(varName, arrayValue);
                } else if (entry.kind == varTable.SymbolKind.VARIABLE) {
                    memory.addValue(varName, new Value(entry.type));
                }
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
    protected Void visitStmtList(AST node) {
        // Executa todos os statements
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }

    @Override
    protected Void visitAssign(AST node) {
        // O primeiro filho é a variável (ou array access), o segundo é a expressão
        AST varNode = node.getChild(0);
        AST exprNode = node.getChild(1);
        
        // Primeiro, avaliamos a expressão do lado direito e obtemos seu valor
        visit(exprNode);
        Value value = stack.popValue();
        
        // Agora verificamos se estamos atribuindo a um array ou variável simples
        if (varNode.kind == NodeKind.ARRAY_ACCESS_NODE) {
            // Primeiro filho do array_access é o nome do array, segundo é o índice
            AST arrayVar = varNode.getChild(0);
            AST indexExpr = varNode.getChild(1);
            
            String arrayName = arrayVar.strData;
            Value arrayValue = memory.getValue(arrayName);
            if (arrayValue == null) {
                throw new RuntimeException("Array variable '" + arrayName + "' not found");
            }
            
            // Verifica se realmente é um array
            if (!arrayValue.isArray()) {
                throw new RuntimeException("Variable '" + arrayName + "' is not an array");
            }
            
            // Avalia a expressão do índice para saber qual posição modificar
            visit(indexExpr);
            Value indexValue = stack.popValue();
            
            // Garante que o índice é um inteiro
            if (indexValue.getType() != PascalType.INT_TYPE) {
                throw new RuntimeException("Array index must be an integer");
            }
            
            int index = (Integer) indexValue.getData();
            
            // Atribui o valor ao elemento específico do array
            arrayValue.setArrayElement(index, value);
        } else {
            String varName = varNode.strData;
            
            // Verifica se a variável já existe na memória e atualiza/cria conforme necessário
            if (memory.getValue(varName) != null) {
                memory.updateValue(varName, value);
            } else {
                memory.addValue(varName, value);
            }
        }
        
        return null;
    }

    @Override
    protected Void visitVarUse(AST node) {
        String varName = node.strData;
        Value value = memory.getValue(varName);
        if (value == null) {
            throw new RuntimeException("Variable '" + varName + "' not found");
        }
        stack.pushValue(value);
        return null;
    }

    // Visitors para valores literais - empilham o valor na pilha de avaliação
    @Override
    protected Void visitIntVal(AST node) {
        stack.pushValue(new Value(PascalType.INT_TYPE, node.intData));
        return null;
    }

    @Override
    protected Void visitRealVal(AST node) {
        stack.pushValue(new Value(PascalType.REAL_TYPE, node.realData));
        return null;
    }

    @Override
    protected Void visitBoolVal(AST node) {
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(node.boolData)));
        return null;
    }

    @Override
    protected Void visitStringVal(AST node) {
        stack.pushValue(new Value(PascalType.STR_TYPE, node.strData));
        return null;
    }

    // Visitors para operações aritméticas - avaliam operandos e calculam resultado
    @Override
    protected Void visitPlus(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        // Conversão de tipos se necessário
        if (left.getType() == PascalType.REAL_TYPE || right.getType() == PascalType.REAL_TYPE) {
            left = convertValue(left, PascalType.REAL_TYPE);
            right = convertValue(right, PascalType.REAL_TYPE);
            float result = (Float) left.getData() + (Float) right.getData();
            stack.pushValue(new Value(PascalType.REAL_TYPE, result));
        } else {
            int result = (Integer) left.getData() + (Integer) right.getData();
            stack.pushValue(new Value(PascalType.INT_TYPE, result));
        }
        
        return null;
    }

    @Override
    protected Void visitMinus(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        // Conversão de tipos se necessário
        if (left.getType() == PascalType.REAL_TYPE || right.getType() == PascalType.REAL_TYPE) {
            left = convertValue(left, PascalType.REAL_TYPE);
            right = convertValue(right, PascalType.REAL_TYPE);
            float result = (Float) left.getData() - (Float) right.getData();
            stack.pushValue(new Value(PascalType.REAL_TYPE, result));
        } else {
            int result = (Integer) left.getData() - (Integer) right.getData();
            stack.pushValue(new Value(PascalType.INT_TYPE, result));
        }
        
        return null;
    }

    @Override
    protected Void visitMult(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        // Conversão de tipos se necessário
        if (left.getType() == PascalType.REAL_TYPE || right.getType() == PascalType.REAL_TYPE) {
            left = convertValue(left, PascalType.REAL_TYPE);
            right = convertValue(right, PascalType.REAL_TYPE);
            float result = (Float) left.getData() * (Float) right.getData();
            stack.pushValue(new Value(PascalType.REAL_TYPE, result));
        } else {
            int result = (Integer) left.getData() * (Integer) right.getData();
            stack.pushValue(new Value(PascalType.INT_TYPE, result));
        }
        
        return null;
    }

    @Override
    protected Void visitDiv(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        // Divisão sempre retorna real
        left = convertValue(left, PascalType.REAL_TYPE);
        right = convertValue(right, PascalType.REAL_TYPE);
        
        float rightVal = (Float) right.getData();
        if (rightVal == 0.0f) {
            throw new RuntimeException("Division by zero");
        }
        
        float result = (Float) left.getData() / rightVal;
        stack.pushValue(new Value(PascalType.REAL_TYPE, result));
        
        return null;
    }

    // Visitors para operações relacionais - comparam valores e retornam boolean
    @Override
    protected Void visitEq(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) == 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitNe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) != 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitLt(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) < 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitLe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) <= 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitGt(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) > 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitGe(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = compareValues(left, right) >= 0;
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    private int compareValues(Value left, Value right) {
        // Converte para o mesmo tipo para comparação
        if (left.getType() == PascalType.REAL_TYPE || right.getType() == PascalType.REAL_TYPE) {
            left = convertValue(left, PascalType.REAL_TYPE);
            right = convertValue(right, PascalType.REAL_TYPE);
            return Float.compare((Float) left.getData(), (Float) right.getData());
        } else if (left.getType() == PascalType.INT_TYPE && right.getType() == PascalType.INT_TYPE) {
            return Integer.compare((Integer) left.getData(), (Integer) right.getData());
        } else if (left.getType() == PascalType.STR_TYPE && right.getType() == PascalType.STR_TYPE) {
            return ((String) left.getData()).compareTo((String) right.getData());
        } else if (left.getType() == PascalType.BOOL_TYPE && right.getType() == PascalType.BOOL_TYPE) {
            return Boolean.compare((Boolean) left.getData(), (Boolean) right.getData());
        }
        
        throw new RuntimeException("Cannot compare " + left.getType() + " with " + right.getType());
    }

    // Visitors para operações lógicas - operam com valores booleanos
    @Override
    protected Void visitAnd(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = (Boolean) left.getData() && (Boolean) right.getData();
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitOr(AST node) {
        visit(node.getChild(0));
        visit(node.getChild(1));
        
        Value right = stack.popValue();
        Value left = stack.popValue();
        
        boolean result = (Boolean) left.getData() || (Boolean) right.getData();
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    @Override
    protected Void visitNot(AST node) {
        visit(node.getChild(0));
        
        Value value = stack.popValue();
        boolean result = !(Boolean) value.getData();
        stack.pushValue(new Value(PascalType.BOOL_TYPE, Boolean.valueOf(result)));
        
        return null;
    }

    // Visitors para estruturas de controle
    @Override
    protected Void visitIf(AST node) {
        // Primeiro filho é a condição
        visit(node.getChild(0));
        Value condition = stack.popValue();
        
        if ((Boolean) condition.getData()) {
            // Executa o bloco then
            visit(node.getChild(1));
        } else if (node.getChildCount() > 2) {
            // Executa o bloco else se existir
            visit(node.getChild(2));
        }
        
        return null;
    }

    @Override
    protected Void visitFor(AST node) {
        // Primeiro filho é o heading (contém var, start, end)
        // Segundo filho é o bloco a ser executado
        AST heading = node.getChild(0);
        AST block = node.getChild(1);
        
        // Extrai os componentes do heading: variável de controle, início e fim
        AST varNode = heading.getChild(0);
        AST startExpr = heading.getChild(1);
        AST endExpr = heading.getChild(2);
        
        String varName = varNode.strData;
        
        // Avalia as expressões de início e fim do loop
        visit(startExpr);
        Value startValue = stack.popValue();
        
        visit(endExpr);
        Value endValue = stack.popValue();
        
        // Converte para inteiros
        int start = (Integer) startValue.getData();
        int end = (Integer) endValue.getData();
        
        // Executa o loop: para cada valor de start até end (inclusive)
        for (int i = start; i <= end; i++) {
            // Atualiza a variável de controle com o valor atual
            memory.updateValue(varName, new Value(PascalType.INT_TYPE, i));
            // Executa o corpo do loop
            visit(block);
        }
        
        return null;
    }

    @Override
    protected Void visitWrite(AST node) {
        // Avalia todas as expressões e imprime
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
            Value value = stack.popValue();
            System.out.print(value.getData());
            if (i < node.getChildCount() - 1) {
                System.out.print(" ");
            }
        }
        System.out.println();
        return null;
    }

    @Override
    protected Void visitRead(AST node) {
        // Lê valores do usuário para as variáveis especificadas
        // Cada filho representa uma variável a ser lida
        for (int i = 0; i < node.getChildCount(); i++) {
            AST varNode = node.getChild(i);
            String varName = varNode.strData;
            
            // Consulta o tipo da variável na tabela de símbolos
            PascalType varType = vt.getType(varName);
            
            // Solicita entrada do usuário
            System.out.print("Enter value for " + varName + ": ");
            String input = in.nextLine();
            
            Value value;
            try {
                // Converte a entrada string para o tipo apropriado
                switch (varType) {
                    case INT_TYPE:
                        value = new Value(PascalType.INT_TYPE, Integer.parseInt(input));
                        break;
                    case REAL_TYPE:
                        value = new Value(PascalType.REAL_TYPE, Float.parseFloat(input));
                        break;
                    case BOOL_TYPE:
                        value = new Value(PascalType.BOOL_TYPE, Boolean.parseBoolean(input));
                        break;
                    case STR_TYPE:
                        value = new Value(PascalType.STR_TYPE, input);
                        break;
                    default:
                        throw new RuntimeException("Unsupported type for read: " + varType);
                }
                
                // Armazena o valor lido na variável
                memory.updateValue(varName, value);
            } catch (NumberFormatException e) {
                throw new RuntimeException("Invalid input for " + varType + ": " + input);
            }
        }
        return null;
    }

    // Métodos para conversões de tipo
    @Override
    protected Void visitB2I(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.INT_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitB2R(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.REAL_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitB2S(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.STR_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitI2R(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.REAL_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitI2S(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.STR_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitR2S(AST node) {
        visit(node.getChild(0));
        Value value = stack.popValue();
        Value converted = convertValue(value, PascalType.STR_TYPE);
        stack.pushValue(converted);
        return null;
    }

    @Override
    protected Void visitVarDecl(AST node) {
        // Declarações de variáveis já foram processadas durante a análise semântica
        return null;
    }

    @Override
    protected Void visitVarList(AST node) {
        // Lista de variáveis - não precisa fazer nada na execução
        return null;
    }

    @Override
    protected Void visitIdentifier(AST node) {
        // Similar ao VarUse
        return visitVarUse(node);
    }

    @Override
    protected Void visitForHeading(AST node) {
        // O heading do for é processado pelo visitFor
        return null;
    }

    @Override
    protected Void visitForBlock(AST node) {
        // O bloco do for é processado pelo visitFor
        return visitBlock(node);
    }

    @Override
    protected Void visitArrayType(AST node) {
        return null;
    }

    @Override
    protected Void visitArrayAccess(AST node) {
        // Primeiro filho é a variável array, segundo é a expressão do índice
        AST arrayVar = node.getChild(0);
        AST indexExpr = node.getChild(1);
        
        // Obtém o nome do array e busca na memória
        String arrayName = arrayVar.strData;
        Value arrayValue = memory.getValue(arrayName);
        if (arrayValue == null) {
            throw new RuntimeException("Array variable '" + arrayName + "' not found");
        }
        
        // Verifica se a variável é realmente um array
        if (!arrayValue.isArray()) {
            throw new RuntimeException("Variable '" + arrayName + "' is not an array");
        }
        
        // Avalia a expressão do índice
        visit(indexExpr);
        Value indexValue = stack.popValue();
        
        // Garante que o índice é um inteiro
        if (indexValue.getType() != PascalType.INT_TYPE) {
            throw new RuntimeException("Array index must be an integer");
        }
        
        int index = (Integer) indexValue.getData();
        
        Value element = arrayValue.getArrayElement(index);
        // Empilha o valor do elemento para uso em expressões
        stack.pushValue(element);
        
        return null;
    }

    @Override
    protected Void visitFunctionCall(AST node) {
        String funcName = node.strData;
        if (funcName == null && node.getChildCount() > 0) {
            funcName = node.getChild(0).strData;
        }
        
        if (funcName == null) {
            throw new RuntimeException("Function name not found in AST node");
        }
        
        // Busca a função/procedimento na tabela de símbolos
        varTable.Entry funcEntry = vt.lookup(funcName);
        if (funcEntry == null || 
            (funcEntry.kind != varTable.SymbolKind.FUNCTION && 
             funcEntry.kind != varTable.SymbolKind.PROCEDURE)) {
            throw new RuntimeException("Function/Procedure '" + funcName + "' not found");
        }
        
        // Se for um procedimento, executa mas não retorna valor
        if (funcEntry.kind == varTable.SymbolKind.PROCEDURE) {
            executeFunction(funcName, funcEntry, node);
            return null;
        }
        
        // Se for uma função, executa e retorna o valor
        Value result = executeFunction(funcName, funcEntry, node);
        if (result != null) {
            stack.pushValue(result);
        } 
        
        return null;
    }
    
    // Método para executar uma função ou procedimento
    private Value executeFunction(String funcName, varTable.Entry funcEntry, AST callNode) {
        AST funcBody = functionBodies.get(funcName);
        
        // Cria uma nova instância de memória
        Memory localMemory = new Memory(vt);
        
        // Copia apenas as variáveis globais para o contexto local
        for (String varName : vt.getAllVarNames()) {
            varTable.Entry globalEntry = vt.lookup(varName);
            if (globalEntry != null && globalEntry.kind == varTable.SymbolKind.VARIABLE) {
                Value globalValue = memory.getValue(varName);
                if (globalValue != null) {
                    localMemory.addValue(varName, globalValue);
                }
            }
        }
        
        // Salva a memória atual para restaurar depois
        Memory savedMemory = memory;
        
        try {
            // Usa a memória local para execução da função
            memory = localMemory;
            
            // Se for função, cria variável de retorno com nome da função
            if (funcEntry.kind == varTable.SymbolKind.FUNCTION) {
                memory.addValue(funcName, new Value(funcEntry.type));
            }
            
            // Inicializa todas as variáveis locais da função com valores padrão
            if (funcEntry.localTable != null) {
                for (varTable.Entry localVar : funcEntry.localTable.values()) {
                    if (localVar.kind == varTable.SymbolKind.VARIABLE) {
                        memory.addValue(localVar.name, new Value(localVar.type));
                    }
                }
            }
            
            // Processa argumentos passados na chamada e associa aos parâmetros
            if (callNode.getChildCount() > 1) {
                int paramIndex = 0;
                // Itera pelos argumentos passados na chamada
                for (int i = 1; i < callNode.getChildCount(); i++) {
                    AST argNode = callNode.getChild(i);
                    
                    // Verifica se é uma lista de expressões
                    if (argNode.kind == NodeKind.EXPR_LIST_NODE) {
                        // Processa cada expressão da lista
                        for (int j = 0; j < argNode.getChildCount(); j++) {
                            if (paramIndex < funcEntry.params.size()) {
                                // Temporariamente volta para a memória original para avaliar argumentos
                                Memory tempMemory = memory;
                                memory = savedMemory;
                                
                                // Avalia a expressão do argumento
                                visit(argNode.getChild(j));
                                Value argValue = stack.popValue();
                                
                                // Volta para a memória local e associa ao parâmetro
                                memory = tempMemory;
                                String paramName = funcEntry.params.get(paramIndex).name;
                                memory.addValue(paramName, argValue);
                                paramIndex++;
                            }
                        }
                    } else {
                        // Argumento simples
                        if (paramIndex < funcEntry.params.size()) {
                            Memory tempMemory = memory;
                            memory = savedMemory;
                            
                            visit(argNode);
                            Value argValue = stack.popValue();

                            memory = tempMemory;
                            String paramName = funcEntry.params.get(paramIndex).name;
                            memory.addValue(paramName, argValue);
                            paramIndex++;
                        }
                    }
                }
            }

            visit(funcBody);  // Executa as instruções da função

            // Para funções, retorna o valor da variável
            if (funcEntry.kind == varTable.SymbolKind.FUNCTION) {
                Value result = memory.getValue(funcName);
                return result;
            }
            
            return null;  // Procedimentos não retornam valor  
        } finally {
            // Copia de volta as variáveis globais que podem ter sido modificadas
            for (String varName : vt.getAllVarNames()) {
                varTable.Entry globalEntry = vt.lookup(varName);
                if (globalEntry != null && globalEntry.kind == varTable.SymbolKind.VARIABLE) {
                    Value localValue = memory.getValue(varName);
                    if (localValue != null) {
                        savedMemory.updateValue(varName, localValue);
                    }
                }
            }
            
            // Restaura a memória original
            memory = savedMemory;
        }
    }

    @Override
    protected Void visitFunctionDecl(AST node) {
        AST headingNode = node.getChild(0); // function_heading
        AST funcNameNode = headingNode.getChild(0); // nome da função
        String funcName = funcNameNode.strData;
        
        // Encontra o bloco da função
        AST funcBlockNode = null;
        for (int i = 0; i < node.getChildCount(); i++) {
            if (node.getChild(i).kind == NodeKind.FUNCTION_BLOCK_NODE) {
                funcBlockNode = node.getChild(i);
                break;
            }
        }
        
        if (funcBlockNode != null) {
            functionBodies.put(funcName, funcBlockNode);
        }
        
        return null;
    }

    @Override
    protected Void visitFunctionSect(AST node) {
        // Seção de funções - coleta todas as declarações de função
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i)); // Isso vai chamar visitFunctionDecl
        }
        return null;
    }

    @Override
    protected Void visitProcedureDecl(AST node) {
        AST headingNode = node.getChild(0); // procedure_heading
        AST procNameNode = headingNode.getChild(0); // nome do procedimento
        String procName = procNameNode.strData;
        
        // Encontra o bloco do procedimento
        AST procBlockNode = null;
        for (int i = 0; i < node.getChildCount(); i++) {
            if (node.getChild(i).kind == NodeKind.PROCEDURE_BLOCK_NODE) {
                procBlockNode = node.getChild(i);
                break;
            }
        }
        
        if (procBlockNode != null) {
            functionBodies.put(procName, procBlockNode);
        }
        
        return null;
    }

    @Override
    protected Void visitProcedureSect(AST node) {
        // Processa declarações de procedimentos para coletar seus corpos
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }

    @Override
    protected Void visitParamList(AST node) {
        // Lista de parâmetros - processada durante chamada de função
        return null;
    }

    @Override
    protected Void visitExprList(AST node) {
        // Lista de expressões - executa todas
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }

    @Override
    protected Void visitFunctionHeading(AST node) {
        // Cabeçalho de função - não faz nada durante execução
        return null;
    }

    @Override
    protected Void visitProcedureHeading(AST node) {
        // Cabeçalho de procedimento - não faz nada durante execução
        return null;
    }

    @Override
    protected Void visitFunctionBlock(AST node) {
        // Bloco de função - executa como um bloco normal
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
            if (returnCalled) {
                returnCalled = false;
                break;
            }
        }
        return null;
    }

    @Override
    protected Void visitProcedureBlock(AST node) {
        // Bloco de procedimento - executa como um bloco normal
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
            if (returnCalled) {
                returnCalled = false;
                break;
            }
        }
        return null;
    }

    @Override
    protected Void visitStructureStmt(AST node) {
        // Statement estruturado - executa todos os filhos
        for (int i = 0; i < node.getChildCount(); i++) {
            visit(node.getChild(i));
        }
        return null;
    }
}
