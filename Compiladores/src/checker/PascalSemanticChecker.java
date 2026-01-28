package checker;

import static ast.NodeKind.ARRAY_ACCESS_NODE;
import static ast.NodeKind.ASSIGN_NODE;
import static ast.NodeKind.B2S_NODE;
import static ast.NodeKind.BLOCK_NODE;
import static ast.NodeKind.BOOL_VAL_NODE;
import static ast.NodeKind.DIV_NODE;
import static ast.NodeKind.EQ_NODE;
import static ast.NodeKind.EXPR_LIST_NODE;
import static ast.NodeKind.FOR_BLOCK_NODE;
import static ast.NodeKind.FOR_HEADING_NODE;
import static ast.NodeKind.FOR_NODE;
import static ast.NodeKind.FUNCTION_BLOCK_NODE;
import static ast.NodeKind.FUNCTION_CALL_NODE;
import static ast.NodeKind.FUNCTION_DECL_NODE;
import static ast.NodeKind.FUNCTION_HEADING_NODE;
import static ast.NodeKind.FUNCTION_SECT_NODE;
import static ast.NodeKind.GE_NODE;
import static ast.NodeKind.GT_NODE;
import static ast.NodeKind.I2R_NODE;
import static ast.NodeKind.I2S_NODE;
import static ast.NodeKind.IF_NODE;
import static ast.NodeKind.INT_VAL_NODE;
import static ast.NodeKind.LE_NODE;
import static ast.NodeKind.LT_NODE;
import static ast.NodeKind.MINUS_NODE;
import static ast.NodeKind.MULT_NODE;
import static ast.NodeKind.NE_NODE;
import static ast.NodeKind.NOT_NODE;
import static ast.NodeKind.PARAM_LIST_NODE;
import static ast.NodeKind.PLUS_NODE;
import static ast.NodeKind.PROCEDURE_BLOCK_NODE;
import static ast.NodeKind.PROCEDURE_DECL_NODE;
import static ast.NodeKind.PROCEDURE_HEADING_NODE;
import static ast.NodeKind.PROCEDURE_SECT_NODE;
import static ast.NodeKind.PROGRAM_NODE;
import static ast.NodeKind.R2S_NODE;
import static ast.NodeKind.READ_NODE;
import static ast.NodeKind.REAL_VAL_NODE;
import static ast.NodeKind.STRING_VAL_NODE;
import static ast.NodeKind.STRUCTURE_STMT_NODE;
import static ast.NodeKind.VAR_DECL_NODE;
import static ast.NodeKind.VAR_LIST_NODE;
import static ast.NodeKind.VAR_USE_NODE;
import static ast.NodeKind.WRITE_NODE;
import static typing.PascalType.NO_TYPE;

import java.util.LinkedHashMap;
import java.util.List;

import org.antlr.v4.runtime.Token;

import ast.AST;
import parser.PascalLexer;
import parser.PascalParser;
import parser.PascalParserBaseVisitor;
import tables.strTable;
import tables.varTable;
import typing.PascalType;

public class PascalSemanticChecker extends PascalParserBaseVisitor<AST> {

    // Tabela de símbolos (variáveis, funções, procedimentos)
    private varTable symbolTable = new varTable();

    // Tabela de strings literais
    private strTable stringTable = new strTable();

    // Busca símbolo: primeiro local, depois global
    private varTable.Entry lookup(String id) {
        return symbolTable.lookup(id);
    }

    AST root; // Raiz da árvore AST

    // Verifica se variável existe
    AST checkVar(Token t) {
        String id = t.getText();
        varTable.Entry e = lookup(id);
        if (e == null || (e.kind != varTable.SymbolKind.VARIABLE && e.kind != varTable.SymbolKind.ARRAY)) {
            System.err.printf("SEMANTIC ERROR (%d): variable '%s' was not declared.\n", t.getLine(), id);
            System.exit(1);
        }
        return new AST(VAR_USE_NODE, id, e.type); // Retorna AST com tipo da variável
    }

    private void typeError(int lineNo, String op, PascalType t1, PascalType t2) {
        System.err.printf("SEMANTIC ERROR (%d): incompatible types for operator '%s', LHS is '%s' and RHS is '%s'.\n",
                lineNo, op, t1.toString(), t2.toString());
        System.exit(1);
    }

    private void checkAssign(int lineNo, PascalType lhsType, PascalType rhsType) {
        if (lhsType == PascalType.BOOL_TYPE && rhsType != PascalType.BOOL_TYPE) {
            typeError(lineNo, ":=", lhsType, rhsType);
        }
        if (lhsType == PascalType.STR_TYPE && rhsType != PascalType.STR_TYPE) {
            typeError(lineNo, ":=", lhsType, rhsType);
        }
        if (lhsType == PascalType.INT_TYPE && rhsType != PascalType.INT_TYPE) {
            typeError(lineNo, ":=", lhsType, rhsType);
        }
        if (lhsType == PascalType.REAL_TYPE && !(rhsType == PascalType.INT_TYPE || rhsType == PascalType.REAL_TYPE)) {
            typeError(lineNo, ":=", lhsType, rhsType);
        }
    }

    // Visita a regra program
    @Override
    public AST visitProgram(PascalParser.ProgramContext ctx) {
        // Visita recursivamente os filhos para construir a AST.
        AST varsSect = visit(ctx.varsSect());

        // Cria lista de filhos dinamicamente baseada no que existe no programa
        java.util.List<AST> children = new java.util.ArrayList<>();
        children.add(varsSect);

        // Só adiciona nó de funções se existirem funções no programa
        if (ctx.functionDecl() != null && !ctx.functionDecl().isEmpty()) {
            AST nodefunc = AST.newSubtree(FUNCTION_SECT_NODE, NO_TYPE);
            for (int i = 0; i < ctx.functionDecl().size(); i++) {
                AST funcdecl = visit(ctx.functionDecl(i));
                nodefunc.addChild(funcdecl);
            }
            children.add(nodefunc);
        }

        // Só adiciona nó de procedimentos se existirem procedimentos no programa
        if (ctx.procedureDecl() != null && !ctx.procedureDecl().isEmpty()) {
            AST nodeproc = AST.newSubtree(PROCEDURE_SECT_NODE, NO_TYPE);
            for (int i = 0; i < ctx.procedureDecl().size(); i++) {
                AST procdecl = visit(ctx.procedureDecl(i));
                nodeproc.addChild(procdecl);
            }
            children.add(nodeproc);
        }

        AST stmtSect = visit(ctx.stmtSect());
        children.add(stmtSect);
        
        // Como esta é a regra inicial, chegamos na raiz da AST.
        this.root = AST.newSubtree(PROGRAM_NODE, NO_TYPE);
        for (AST child : children) {
            this.root.addChild(child);
        }
        
        return this.root;
    }

    // Visita a regra varsSect
    @Override
    public AST visitVarsSect(PascalParser.VarsSectContext ctx) {
        // Cria um nó com a lista das variáveis
        AST node = AST.newSubtree(VAR_LIST_NODE, NO_TYPE);
        if (ctx.varDecl() != null && !ctx.varDecl().isEmpty()) {
            for (int i = 0; i < ctx.varDecl().size(); i++) {
                AST child = visit(ctx.varDecl(i));
                if (child != null) {
                    // Se o child for um VAR_LIST_NODE (múltiplas variáveis), adiciona seus filhos
                    if (child.kind == VAR_LIST_NODE) {
                        for (int j = 0; j < child.getChildCount(); j++) {
                            node.addChild(child.getChild(j));
                        }
                    } else {
                        // Se for um nó simples (única variável), adiciona diretamente
                        node.addChild(child);
                    }
                }
            }
        }
        // Se não há filhos, o nó fica vazio, o que é o comportamento correto
        return node;
    }

    // Visita a regra stmtSect
    @Override
    public AST visitStmtSect(PascalParser.StmtSectContext ctx) {
        AST node = AST.newSubtree(BLOCK_NODE, NO_TYPE);
        if (ctx.stmtList() != null) {
            AST stmtListNode = visit(ctx.stmtList());
            if (stmtListNode != null) {
                // Adiciona todos os filhos do stmtList ao bloco
                for (int i = 0; i < stmtListNode.getChildCount(); i++) {
                    node.addChild(stmtListNode.getChild(i));
                }
            }
        }
        return node;
    }

    // Visita a regra stmtList
    @Override
    public AST visitStmtList(PascalParser.StmtListContext ctx) {
        AST node = AST.newSubtree(BLOCK_NODE, NO_TYPE);
        if (ctx.stmt() != null) {
            for (int i = 0; i < ctx.stmt().size(); i++) {
                AST child = visit(ctx.stmt(i));
                if (child != null) {
                    node.addChild(child);
                }
            }
        }
        return node;
    }

    @Override
    public AST visitWriteStmt(PascalParser.WriteStmtContext ctx) {
        AST writeNode = AST.newSubtree(WRITE_NODE, NO_TYPE);
        for (PascalParser.ExprContext expr : ctx.expr()) {
            AST exprNode = visit(expr);
            if (exprNode != null) {
                // Adiciona nó de conversão conforme o tipo da expressão
                AST convertedNode = createWriteConversionNode(exprNode);
                writeNode.addChild(convertedNode);
            }
        }
        return writeNode;
    }

    // Método auxiliar para criar nós de conversão para string
    private AST createWriteConversionNode(AST exprNode) {
        PascalType exprType = exprNode.type;
        
        switch (exprType) {
            case INT_TYPE:
                // Cria nó I2S (Integer to String)
                AST i2sNode = AST.newSubtree(I2S_NODE, PascalType.STR_TYPE);
                i2sNode.addChild(exprNode);
                return i2sNode;
                
            case REAL_TYPE:
                // Cria nó R2S (Real to String)
                AST r2sNode = AST.newSubtree(R2S_NODE, PascalType.STR_TYPE);
                r2sNode.addChild(exprNode);
                return r2sNode;
                
            case BOOL_TYPE:
                // Cria nó B2S (Boolean to String)
                AST b2sNode = AST.newSubtree(B2S_NODE, PascalType.STR_TYPE);
                b2sNode.addChild(exprNode);
                return b2sNode;
                
            case STR_TYPE:
                // Se já é string, não precisa de conversão - retorna o nó original
                return exprNode;
                
            default:
                // Para outros tipos (NO_TYPE, etc.), retorna o nó original sem conversão
                return exprNode;
        }
    }

    // Declaração de variável (global ou local)
    @Override
    public AST visitVarDecl(PascalParser.VarDeclContext ctx) {
        var idList = ctx.identifierList();
        int typeToken = ctx.typeSpec().start.getType();
        varTable.SymbolKind typeKind = null;
        // Verifica se é um tipo de variável ou array
        if (typeToken == PascalLexer.ARRAY) {
            typeKind = varTable.SymbolKind.ARRAY;
            // Se for array, pega o tipo do elemento
            typeToken = ctx.typeSpec().arrayType().typeSpec().start.getType();
        } else {
            typeKind = varTable.SymbolKind.VARIABLE;
        }
        PascalType type = PascalType.getVarType(typeToken);
        int line = idList.start.getLine();

        // Verifica se já existe variável com o mesmo nome e adiciona na tabela
        for (var idToken : idList.IDENTIFIER()) {
            String id = idToken.getText();
            varTable.Entry entry = new varTable.Entry(id, type, line, typeKind);
            if (!symbolTable.add(id, entry)) {
                varTable.Entry existing = symbolTable.lookup(id);
                System.err.printf("SEMANTIC ERROR (%d): variable '%s' already declared at line %d.\n",
                        line, id, existing.lineDeclared);
                System.exit(1);
            }
        }
        visitChildren(ctx);
        
        // Se há apenas uma variável, retorna um nó simples
        if (idList.IDENTIFIER().size() == 1) {
            String varName = idList.IDENTIFIER().get(0).getText();
            return new AST(VAR_DECL_NODE, varName, type);
        }
        
        // Se há múltiplas variáveis, cria um nó container que será "desempacotado" pelo visitVarsSect
        AST containerNode = AST.newSubtree(VAR_LIST_NODE, NO_TYPE);
        for (var idToken : idList.IDENTIFIER()) {
            String varName = idToken.getText();
            containerNode.addChild(new AST(VAR_DECL_NODE, varName, type));
        }
        return containerNode;
    }

    // Função
    @Override
    public AST visitFunctionDecl(PascalParser.FunctionDeclContext ctx) {
        // Obtém informações da função
        PascalParser.FunctionHeadingContext heading = ctx.functionHeading();
        String funcName = heading.IDENTIFIER().getText();
        int line = heading.start.getLine();
        int typeToken = heading.typeSpec().start.getType();
        PascalType returnType = PascalType.getVarType(typeToken);
        
        // Verifica se a função já foi declarada
        varTable.Entry funcEntry = new varTable.Entry(funcName, returnType, line, varTable.SymbolKind.FUNCTION);
        if (!symbolTable.addGlobal(funcName, funcEntry)) {
            varTable.Entry existing = symbolTable.getGlobal(funcName);
            System.err.printf("SEMANTIC ERROR (%d): function '%s' already declared at line %d.\n",
                    line, funcName, existing.lineDeclared);
            System.exit(1);
        }

        funcEntry.localTable = new LinkedHashMap<>();
        // Nome da função como variável local (valor de retorno)
        funcEntry.localTable.put(funcName, new varTable.Entry(funcName, returnType, line, varTable.SymbolKind.VARIABLE));

        // Cria nó do cabeçalho da função
        AST headingNode = AST.newSubtree(FUNCTION_HEADING_NODE, returnType);
        headingNode.addChild(new AST(VAR_USE_NODE, funcName, returnType));

        // Parâmetros
        if (heading.formalParameterList() != null) {
            var paramList = heading.formalParameterList();
            AST paramListNode = AST.newSubtree(PARAM_LIST_NODE, NO_TYPE);

            // Pode ter vários parâmetros
            List<PascalParser.IdentifierListContext> idLists = paramList.identifierList();
            List<PascalParser.TypeSpecContext> typeSpecs = paramList.typeSpec();

            // Verifica se o número de listas de identificadores e especificações de tipo é igual
            for (int i = 0; i < idLists.size(); i++) {
                PascalParser.IdentifierListContext idList = idLists.get(i);
                PascalParser.TypeSpecContext typeSpec = typeSpecs.get(i);
                int paramTypeToken = typeSpec.start.getType();
                PascalType paramType = PascalType.getVarType(paramTypeToken);
                for (var idToken : idList.IDENTIFIER()) {
                    // Para cada identificador, cria uma entrada na tabela local
                    String pname = idToken.getText();
                    funcEntry.params.add(new varTable.Param(pname, paramType));
                    if (funcEntry.localTable.containsKey(pname)) {
                        System.err.printf("SEMANTIC ERROR (%d): parameter '%s' already declared in function '%s'.\n",
                                idToken.getSymbol().getLine(), pname, funcName);
                        System.exit(1);
                    }
                    funcEntry.localTable.put(pname, new varTable.Entry(pname, paramType, idToken.getSymbol().getLine(), varTable.SymbolKind.VARIABLE));
                    
                    // Adiciona parâmetro à AST
                    paramListNode.addChild(new AST(VAR_DECL_NODE, pname, paramType));
                }
            }
            headingNode.addChild(paramListNode);
        }

        // Executa corpo da função com escopo local
        varTable.Entry prevRoutine = symbolTable.getCurrentRoutine();
        symbolTable.setCurrentRoutine(funcEntry);
        
        // Cria nó da declaração de função completa
        AST funcDeclNode = AST.newSubtree(FUNCTION_DECL_NODE, returnType);
        funcDeclNode.addChild(headingNode);
        
        // Adiciona var_list como filho direto, se existir
        if (ctx.functionBlock().varsSect() != null) {
            AST varsNode = visit(ctx.functionBlock().varsSect());
            funcDeclNode.addChild(varsNode);
        }
        
        // Adiciona function_block como filho direto (só com instruções)
        AST stmtNode = visit(ctx.functionBlock().stmtSect());
        AST funcBlockNode = AST.newSubtree(FUNCTION_BLOCK_NODE, NO_TYPE);
        // Adiciona todos os filhos do stmtSect ao function_block
        if (stmtNode != null) {
            for (int i = 0; i < stmtNode.getChildCount(); i++) {
                funcBlockNode.addChild(stmtNode.getChild(i));
            }
        }
        funcDeclNode.addChild(funcBlockNode);
        
        symbolTable.setCurrentRoutine(prevRoutine);

        return funcDeclNode;
    }

    // Procedimento
    @Override
    public AST visitProcedureDecl(PascalParser.ProcedureDeclContext ctx) {
        PascalParser.ProcedureHeadingContext heading = ctx.procedureHeading();
        String procName = heading.IDENTIFIER().getText();
        int line = heading.start.getLine();

        // Cria entrada para o procedimento
        varTable.Entry procEntry = new varTable.Entry(procName, null, line, varTable.SymbolKind.PROCEDURE);
        if (!symbolTable.addGlobal(procName, procEntry)) {
            varTable.Entry existing = symbolTable.getGlobal(procName);
            System.err.printf("SEMANTIC ERROR (%d): procedure '%s' already declared at line %d.\n",
                    line, procName, existing.lineDeclared);
            System.exit(1);
        }
        
        procEntry.localTable = new LinkedHashMap<>();

        // Cria nó do cabeçalho do procedimento
        AST headingNode = AST.newSubtree(PROCEDURE_HEADING_NODE, PascalType.NO_TYPE);
        headingNode.addChild(new AST(VAR_USE_NODE, procName, PascalType.NO_TYPE));

        // Parâmetros
        if (heading.formalParameterList() != null) {
            var paramList = heading.formalParameterList();
            AST paramListNode = AST.newSubtree(PARAM_LIST_NODE, NO_TYPE);
            
            List<PascalParser.IdentifierListContext> idLists = paramList.identifierList();
            List<PascalParser.TypeSpecContext> typeSpecs = paramList.typeSpec();
            for (int i = 0; i < idLists.size(); i++) {
                // Assim como em função, cria entradas na tabela local
                PascalParser.IdentifierListContext idList = idLists.get(i);
                PascalParser.TypeSpecContext typeSpec = typeSpecs.get(i);
                int paramTypeToken = typeSpec.start.getType();
                PascalType paramType = PascalType.getVarType(paramTypeToken);
                for (var idToken : idList.IDENTIFIER()) {
                    String pname = idToken.getText();
                    procEntry.params.add(new varTable.Param(pname, paramType));
                    if (procEntry.localTable.containsKey(pname)) {
                        System.err.printf("SEMANTIC ERROR (%d): parameter '%s' already declared in procedure '%s'.\n",
                                idToken.getSymbol().getLine(), pname, procName);
                        System.exit(1);
                    }
                    procEntry.localTable.put(pname, new varTable.Entry(pname, paramType, idToken.getSymbol().getLine(), varTable.SymbolKind.VARIABLE));
                    
                    // Adiciona parâmetro à AST
                    paramListNode.addChild(new AST(VAR_DECL_NODE, pname, paramType));
                }
            }
            headingNode.addChild(paramListNode);
        }

        // Executa corpo do procedimento com escopo local
        varTable.Entry prevRoutine = symbolTable.getCurrentRoutine();
        symbolTable.setCurrentRoutine(procEntry);
        
        // Cria nó da declaração de procedimento completa
        AST procDeclNode = AST.newSubtree(PROCEDURE_DECL_NODE, PascalType.NO_TYPE);
        procDeclNode.addChild(headingNode);
        
        // Adiciona var_list como filho direto, se existir
        if (ctx.procedureBlock().varsSect() != null) {
            AST varsNode = visit(ctx.procedureBlock().varsSect());
            procDeclNode.addChild(varsNode);
        }
        
        // Adiciona procedure_block como filho direto (só com instruções)
        AST stmtNode = visit(ctx.procedureBlock().stmtSect());
        AST procBlockNode = AST.newSubtree(PROCEDURE_BLOCK_NODE, NO_TYPE);
        // Adiciona todos os filhos do stmtSect ao procedure_block
        if (stmtNode != null) {
            for (int i = 0; i < stmtNode.getChildCount(); i++) {
                procBlockNode.addChild(stmtNode.getChild(i));
            }
        }
        procDeclNode.addChild(procBlockNode);
        
        symbolTable.setCurrentRoutine(prevRoutine);

        return procDeclNode;
    }

    @Override
    public AST visitFunctionCall(PascalParser.FunctionCallContext ctx) {
        String funcName = ctx.IDENTIFIER().getText();
        // Verifica se a função foi declarada
        varTable.Entry e = symbolTable.getGlobal(funcName);
        if (e == null || (e.kind != varTable.SymbolKind.FUNCTION && e.kind != varTable.SymbolKind.PROCEDURE)) {
            System.err.printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n", ctx.start.getLine(), funcName);
            System.exit(1);
        }
        int expected = e.params.size();
        int given = 0;
        
        AST funcCallNode = AST.newSubtree(FUNCTION_CALL_NODE, e.type);
        funcCallNode.addChild(new AST(VAR_USE_NODE, funcName, e.type));
        
        // Se a função tem parâmetros, verifica o número de argumentos passados
        if (ctx.exprList() != null) {
            AST argsNode = visit(ctx.exprList());
            given = argsNode.getChildCount();
            funcCallNode.addChild(argsNode);
        }
        
        if (expected != given) {
            System.err.printf("SEMANTIC ERROR (%d): function '%s' expects %d arguments, got %d.\n",
                    ctx.start.getLine(), funcName, expected, given);
            System.exit(1);
        }
        
        // Verifica os tipos dos argumentos
        if (ctx.exprList() != null) {
            List<PascalParser.ExprContext> args = ctx.exprList().expr();
            for (int i = 0; i < args.size(); i++) {
                PascalParser.ExprContext arg = args.get(i);
                AST argAst = visit(arg);
                PascalType argType = argAst.type;
                varTable.Param param = e.params.get(i);
                if (argType == PascalType.NO_TYPE || param.type == PascalType.NO_TYPE)
                    continue; // Se algum tipo for NO_TYPE, ignora a verificação
                if (argType != param.type) {
                    System.err.printf("SEMANTIC ERROR (%d): argument %d of function '%s' expected type '%s', got '%s'.\n",
                            ctx.start.getLine(), i + 1, funcName, param.type.toString(), argType.toString());
                    System.exit(1);
                }
            }
        }

        return funcCallNode;
    }

    // Atribuição
    @Override
    public AST visitAssignStmt(PascalParser.AssignStmtContext ctx) {
        AST exprAst = visit(ctx.expr());
        if (exprAst == null) {
            System.err.printf("SEMANTIC ERROR (%d): expression in assignment is invalid.\n", ctx.start.getLine());
            System.exit(1);
        }

        AST lhsNode = null;
        Token idToken = null;

        if (ctx.IDENTIFIER() != null) {
            // Atribuição simples
            idToken = ctx.IDENTIFIER().getSymbol();
            lhsNode = checkVar(idToken);
        }
        else if (ctx.indexedVariable() != null) {
            // Atribuição em array - criar nó ARRAY_ACCESS_NODE com índices
            idToken = ctx.indexedVariable().IDENTIFIER().getSymbol();
            varTable.Entry e = lookup(idToken.getText());
            if (e == null || e.kind != varTable.SymbolKind.ARRAY) {
                System.err.printf("SEMANTIC ERROR (%d): array variable '%s' is not declared.\n", 
                        idToken.getLine(), idToken.getText());
                System.exit(1);
            }
            
            // Cria nó de acesso ao array
            lhsNode = AST.newSubtree(ARRAY_ACCESS_NODE, (PascalType) e.type);
            lhsNode.addChild(new AST(VAR_USE_NODE, idToken.getText(), (PascalType) e.type));
            
            // Verifica e adiciona os índices
            List<PascalParser.ExprContext> indices = ctx.indexedVariable().expr();
            for (PascalParser.ExprContext indexExpr : indices) {
                AST indexAst = visit(indexExpr);
                PascalType indexType = indexAst.type;
                if (indexType != PascalType.INT_TYPE) {
                    System.err.printf("SEMANTIC ERROR (%d): array index must be of type integer, got '%s'.\n",
                            ctx.start.getLine(), indexType.toString());
                    System.exit(1);
                }
                lhsNode.addChild(indexAst);
            }
        }
        
        if (lhsNode != null && idToken != null) {
            // Aplica conversão I2R APENAS se necessário (int -> real) ANTES da verificação de tipos
            AST finalExprAst = exprAst;
            if (lhsNode.type == PascalType.REAL_TYPE && exprAst.type == PascalType.INT_TYPE) {
                // Cria nó I2R para conversão de inteiro para real
                AST i2rNode = AST.newSubtree(I2R_NODE, PascalType.REAL_TYPE);
                i2rNode.addChild(exprAst);
                finalExprAst = i2rNode;
            }
            
            // Faz as verificações de tipos usando a expressão (possivelmente convertida)
            checkAssign(ctx.start.getLine(), lhsNode.type, finalExprAst.type);
            
            return AST.newSubtree(ASSIGN_NODE, lhsNode.type, lhsNode, finalExprAst); // Retorna AST de atribuição
        }

        return null;
    }

    @Override
    public AST visitMulExpr(PascalParser.MulExprContext ctx) {
        AST lhsAst = visit(ctx.expr(0));
        AST rhsAst = visit(ctx.expr(1));
        PascalType lhsType = lhsAst.type;
        PascalType rhsType = rhsAst.type;
        PascalType resultType = PascalType.NO_TYPE;
        ast.NodeKind nodeKind = MULT_NODE; // Default

        if (ctx.mulop().STAR() != null) {
            resultType = lhsType.unifyMult(rhsType);
            nodeKind = MULT_NODE;
        } else if (ctx.mulop().SLASH() != null) {
            resultType = lhsType.unifyslash(rhsType);
            nodeKind = DIV_NODE;
        } else if (ctx.mulop().DIV() != null) {
            resultType = lhsType.unifyDiv(rhsType);
            nodeKind = DIV_NODE; // Usar DIV_NODE para ambos / e DIV
        } else if (ctx.mulop().MOD() != null) {
            resultType = lhsType.unifyMod(rhsType);
            nodeKind = MULT_NODE;
        }

        if (resultType == PascalType.NO_TYPE) {
            typeError(ctx.start.getLine(), ctx.mulop().getText(), lhsType, rhsType);
        }
        
        AST mulNode = AST.newSubtree(nodeKind, resultType);
        mulNode.addChild(lhsAst);
        mulNode.addChild(rhsAst);
        
        return mulNode;
    }

    @Override
    public AST visitAddExpr(PascalParser.AddExprContext ctx) {
        AST lhsAst = visit(ctx.expr(0));
        AST rhsAst = visit(ctx.expr(1));
        PascalType lhsType = lhsAst.type;
        PascalType rhsType = rhsAst.type;

        if (lhsType == null) {
            System.err.printf("SEMANTIC ERROR (%d): left-hand side of " + ctx.addop().getText() + " is not a valid type.\n", ctx.start.getLine());
            System.exit(1);
        }
        if (lhsType == PascalType.NO_TYPE || rhsType == PascalType.NO_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): right-hand side of " +  ctx.addop().getText() + " is not a valid type.\n", ctx.start.getLine());
            System.exit(1);
        }

        // Unifica os tipos para o operador adição/subtração
        PascalType resultType = lhsType.unifyPlusMinus(rhsType);

        if (resultType == PascalType.NO_TYPE) {
            typeError(ctx.start.getLine(), ctx.addop().getText(), lhsType, rhsType);
        }

        // Escolhe o nó correto baseado no operador
        ast.NodeKind nodeKind;
        if (ctx.addop().PLUS() != null) {
            nodeKind = PLUS_NODE;
        } else if (ctx.addop().MINUS() != null) {
            nodeKind = MINUS_NODE;
        } else {
            nodeKind = PLUS_NODE; // Default fallback
        }

        AST addNode = AST.newSubtree(nodeKind, resultType);
        addNode.addChild(lhsAst);
        addNode.addChild(rhsAst);
        
        return addNode;
    }

    @Override
    public AST visitRelExpr(PascalParser.RelExprContext ctx) {
        AST lhsAst = visit(ctx.expr(0));
        AST rhsAst = visit(ctx.expr(1));
        PascalType lhsType = lhsAst.type;
        PascalType rhsType = rhsAst.type;

        if (lhsType == PascalType.NO_TYPE || rhsType == PascalType.NO_TYPE) {
            AST defaultNode = AST.newSubtree(EQ_NODE, PascalType.NO_TYPE);
            defaultNode.addChild(lhsAst);
            defaultNode.addChild(rhsAst);
            return defaultNode;
        }

        PascalType resultType = lhsType.unifyRel(rhsType);
        if (resultType == PascalType.NO_TYPE) {
            typeError(ctx.start.getLine(), ctx.relop().getText(), lhsType, rhsType);
        }

        AST relNode;
        switch (ctx.relop().getText()) {
            case "<":
                relNode = AST.newSubtree(LT_NODE, PascalType.BOOL_TYPE);
                break;
            case "<=":
                relNode = AST.newSubtree(LE_NODE, PascalType.BOOL_TYPE);
                break;
            case "=":
                relNode = AST.newSubtree(EQ_NODE, PascalType.BOOL_TYPE);
                break;
            case ">":
                relNode = AST.newSubtree(GT_NODE, PascalType.BOOL_TYPE);
                break;
            case ">=":
                relNode = AST.newSubtree(GE_NODE, PascalType.BOOL_TYPE);
                break;
            case "<>":
                relNode = AST.newSubtree(NE_NODE, PascalType.BOOL_TYPE);
                break;
            default:
                System.err.printf("SEMANTIC ERROR (%d): unknown relational operator '%s'.\n", ctx.start.getLine(), ctx.relop().getText());
                System.exit(1);
                return null; // Should not be reached
        }
        
        relNode.addChild(lhsAst);
        relNode.addChild(rhsAst);
        
        return relNode;
    }

    @Override
    public AST visitAndExpr(PascalParser.AndExprContext ctx) {
        AST lhsAst = visit(ctx.expr(0));
        AST rhsAst = visit(ctx.expr(1));
        PascalType lhsType = lhsAst.type;
        PascalType rhsType = rhsAst.type;

        // Ambos os operandos devem ser booleanos
        if (lhsType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): left operand of 'and' must be boolean, got '%s'.\n",
                    ctx.start.getLine(), lhsType.toString());
            System.exit(1);
        }
        if (rhsType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): right operand of 'and' must be boolean, got '%s'.\n",
                    ctx.start.getLine(), rhsType.toString());
            System.exit(1);
        }

        AST andNode = AST.newSubtree(ast.NodeKind.AND_NODE, PascalType.BOOL_TYPE);
        andNode.addChild(lhsAst);
        andNode.addChild(rhsAst);
        
        return andNode;
    }

    @Override
    public AST visitOrExpr(PascalParser.OrExprContext ctx) {
        AST lhsAst = visit(ctx.expr(0));
        AST rhsAst = visit(ctx.expr(1));
        PascalType lhsType = lhsAst.type;
        PascalType rhsType = rhsAst.type;

        // Ambos os operandos devem ser booleanos
        if (lhsType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): left operand of 'or' must be boolean, got '%s'.\n",
                    ctx.start.getLine(), lhsType.toString());
            System.exit(1);
        }
        if (rhsType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): right operand of 'or' must be boolean, got '%s'.\n",
                    ctx.start.getLine(), rhsType.toString());
            System.exit(1);
        }

        AST orNode = AST.newSubtree(ast.NodeKind.OR_NODE, PascalType.BOOL_TYPE);
        orNode.addChild(lhsAst);
        orNode.addChild(rhsAst);
        
        return orNode;
    }

    @Override
    public AST visitNotExpr(PascalParser.NotExprContext ctx) {
        AST exprAst = visit(ctx.expr());
        PascalType exprType = exprAst.type;
        if (exprType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): 'not' operator expects a boolean expression, got '%s'.\n",
                    ctx.start.getLine(), exprType.toString());
            System.exit(1);
        }
        
        AST notNode = AST.newSubtree(NOT_NODE, PascalType.BOOL_TYPE);
        notNode.addChild(exprAst);
        
        return notNode;
    }

    @Override
    public AST visitParenExpr(PascalParser.ParenExprContext ctx) {
        // Visita a expressão dentro dos parênteses
        return visit(ctx.expr());
    }

    @Override
    public AST visitBooleanExpr(PascalParser.BooleanExprContext ctx) {
        String boolStr = ctx.BOOLEAN_VALUE().getText();
        boolean boolValue = boolStr.equalsIgnoreCase("true");
        return new AST(BOOL_VAL_NODE, boolValue, PascalType.BOOL_TYPE); // Retorna AST com tipo booleano
    }

    @Override
    public AST visitIntegerExpr(PascalParser.IntegerExprContext ctx) {
        String intStr = ctx.INTEGER_VALUE().getText();
        int intValue = Integer.parseInt(intStr);
        return new AST(INT_VAL_NODE, intValue, PascalType.INT_TYPE); // Retorna o tipo inteiro
    }

    @Override
    public AST visitRealExpr(PascalParser.RealExprContext ctx) {
        String realStr = ctx.REAL_VALUE().getText();
        float realValue = Float.parseFloat(realStr);
        return new AST(REAL_VAL_NODE, realValue, PascalType.REAL_TYPE); // Retorna o tipo real
    }

    @Override
    public AST visitStringExpr(PascalParser.StringExprContext ctx) {
        // Adiciona a string à tabela de strings, se ainda não estiver lá
        String strVal = ctx.STRING_VALUE().getText();

        // Remove aspas da string
        strVal = strVal.substring(1, strVal.length() - 1);

        stringTable.addString(strVal);

        return new AST(STRING_VAL_NODE, strVal, PascalType.STR_TYPE); // Retorna AST com tipo string
    }

    @Override
    public AST visitIdentifierExpr(PascalParser.IdentifierExprContext ctx) {
        // Verifica se a variável foi declarada
        Token idToken = ctx.IDENTIFIER().getSymbol();
        return checkVar(idToken);
    }

    @Override
    public AST visitFunctionCallExpr(PascalParser.FunctionCallExprContext ctx) {
        String funcName = ctx.functionCall().IDENTIFIER().getText();
        // Verifica se a função foi declarada
        varTable.Entry e = symbolTable.getGlobal(funcName);
        if (e == null || e.kind != varTable.SymbolKind.FUNCTION) {
            System.err.printf("SEMANTIC ERROR (%d): function '%s' was not declared.\n", ctx.start.getLine(), funcName);
            System.exit(1);
        }
        
        AST funcCallNode = AST.newSubtree(FUNCTION_CALL_NODE, e.type);
        funcCallNode.addChild(new AST(VAR_USE_NODE, funcName, e.type));
        
        int expected = e.params.size();
        int given = 0;
        // Se a função tem parâmetros, verifica o número de argumentos passados
        if (ctx.functionCall().exprList() != null) {
            AST argsNode = visit(ctx.functionCall().exprList());
            given = argsNode.getChildCount();
            funcCallNode.addChild(argsNode);
        }
        if (expected != given) {
            System.err.printf("SEMANTIC ERROR (%d): function '%s' expects %d arguments, got %d.\n",
                    ctx.start.getLine(), funcName, expected, given);
            System.exit(1);
        }
        
        // Verifica os tipos dos argumentos
        if (ctx.functionCall().exprList() != null) {
            List<PascalParser.ExprContext> args = ctx.functionCall().exprList().expr();
            for (int i = 0; i < args.size(); i++) {
                PascalParser.ExprContext arg = args.get(i);
                AST argAst = visit(arg);
                PascalType argType = argAst.type;
                varTable.Param param = e.params.get(i);
                if (argType == PascalType.NO_TYPE || param.type == PascalType.NO_TYPE)
                    continue; // Se algum tipo for NO_TYPE, ignora a verificação
                if (argType != param.type) {
                    System.err.printf("SEMANTIC ERROR (%d): argument %d of function '%s' expected type '%s', got '%s'.\n",
                            ctx.start.getLine(), i + 1, funcName, param.type.toString(), argType.toString());
                    System.exit(1);
                }
            }
        }

        return funcCallNode;
    }

    @Override
    public AST visitIndexedVariableExpr(PascalParser.IndexedVariableExprContext ctx) {
        // Verifica se a variável array foi declarada
        Token idToken = ctx.indexedVariable().IDENTIFIER().getSymbol();
        varTable.Entry e = lookup(idToken.getText());
        if (e == null || e.kind != varTable.SymbolKind.ARRAY) {
            System.err.printf("SEMANTIC ERROR (%d): array variable '%s' is not declared.\n", 
                    idToken.getLine(), idToken.getText());
            System.exit(1);
        }
        
        AST arrayAccessNode = AST.newSubtree(ARRAY_ACCESS_NODE, (PascalType) e.type);
        arrayAccessNode.addChild(new AST(VAR_USE_NODE, idToken.getText(), (PascalType) e.type));
        
        // Verifica se os índices são do tipo correto (inteiro)
        List<PascalParser.ExprContext> indices = ctx.indexedVariable().expr();
        for (PascalParser.ExprContext indexExpr : indices) {
            AST indexAst = visit(indexExpr);
            PascalType indexType = indexAst.type;
            if (indexType != PascalType.INT_TYPE) {
                System.err.printf("SEMANTIC ERROR (%d): array index must be of type integer, got '%s'.\n",
                        ctx.start.getLine(), indexType.toString());
                System.exit(1);
            }
            arrayAccessNode.addChild(indexAst);
        }
        
        return arrayAccessNode;
    }

    @Override
    public AST visitAssignIndexedExpr(PascalParser.AssignIndexedExprContext ctx) {
        // Verifica se a variável array foi declarada
        Token idToken = ctx.assignIndexed().IDENTIFIER().getSymbol();
        varTable.Entry e = lookup(idToken.getText());
        if (e == null || e.kind != varTable.SymbolKind.ARRAY) {
            System.err.printf("SEMANTIC ERROR (%d): array variable '%s' is not declared.\n", 
                    idToken.getLine(), idToken.getText());
            System.exit(1);
        }
        
        // Verifica se os índices são do tipo correto (inteiro)
        List<PascalParser.ExprContext> indices = ctx.assignIndexed().expr();
        // O último expr é o valor sendo atribuído, os anteriores são índices
        for (int i = 0; i < indices.size() - 1; i++) {
            AST indexAst = visit(indices.get(i));
            PascalType indexType = indexAst.type;
            if (indexType != PascalType.INT_TYPE) {
                System.err.printf("SEMANTIC ERROR (%d): array index must be of type integer, got '%s'.\n",
                        ctx.start.getLine(), indexType.toString());
                System.exit(1);
            }
        }
        
        // Verifica o tipo da expressão sendo atribuída
        AST exprAst = visit(indices.get(indices.size() - 1));
        PascalType exprType = exprAst.type;
        
        // Verifica se os tipos são compatíveis
        checkAssign(ctx.start.getLine(), (PascalType) e.type, exprType);
        
        return new AST(ARRAY_ACCESS_NODE, idToken.getText(), PascalType.NO_TYPE); // Retorna AST com tipo NO_TYPE
    }

    // Leitura
    @Override
    public AST visitReadStmt(PascalParser.ReadStmtContext ctx) {
        AST readNode = AST.newSubtree(READ_NODE, PascalType.NO_TYPE);
        
        if (ctx.IDENTIFIER() != null) {
            AST varNode = checkVar(ctx.IDENTIFIER().getSymbol());
            readNode.addChild(varNode);
        }
        
        return readNode;
    }
    
    @Override
    public AST visitIfStmt(PascalParser.IfStmtContext ctx) {
        // Verifica o tipo da expressão condicional
        AST conditionAst = visit(ctx.expr());
        PascalType conditionType = conditionAst.type;
        if (conditionType != PascalType.BOOL_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): 'if' condition must be of type boolean, got '%s'.\n",
                    ctx.start.getLine(), conditionType.toString());
            System.exit(1);
        }
    
        AST ifNode = AST.newSubtree(IF_NODE, PascalType.NO_TYPE);
        ifNode.addChild(conditionAst);
        
        // Visita o bloco 'then'
        if (ctx.stmt(0) != null) {
            AST thenNode = visit(ctx.stmt(0));
            ifNode.addChild(thenNode);
        } else if (ctx.structureStmt(0) != null) {
            AST thenNode = visit(ctx.structureStmt(0));
            ifNode.addChild(thenNode);
        }
    
        // Visita o bloco 'else', se existir
        if (ctx.ELSE() != null) {
            if (ctx.stmt(1) != null) {
                AST elseNode = visit(ctx.stmt(1));
                ifNode.addChild(elseNode);
            } else if (ctx.structureStmt(1) != null) {
                AST elseNode = visit(ctx.structureStmt(1));
                ifNode.addChild(elseNode);
            }
        }
    
        return ifNode;
    }

    @Override
    public AST visitForStmt(PascalParser.ForStmtContext ctx) {
        // Verifica se a variável de controle foi declarada
        Token idToken = ctx.IDENTIFIER().getSymbol();
        AST varAst = checkVar(idToken);
        PascalType varType = varAst.type;
        
        // A variável de controle deve ser do tipo inteiro
        if (varType != PascalType.INT_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): for loop control variable '%s' must be of type integer, got '%s'.\n",
                    idToken.getLine(), idToken.getText(), varType.toString());
            System.exit(1);
        }
        
        // Verifica os tipos das expressões inicial e final
        List<PascalParser.ExprForContext> exprFors = ctx.exprFor();
        if (exprFors.size() != 2) {
            System.err.printf("SEMANTIC ERROR (%d): for loop must have exactly two expressions (start and end).\n",
                    ctx.start.getLine());
            System.exit(1);
        }
        
        // Visita as expressões para verificar se são válidas
        AST startAst = visit(exprFors.get(0));
        PascalType startType = startAst.type;
        AST endAst = visit(exprFors.get(1));
        PascalType endType = endAst.type;
        
        // As expressões devem ser do tipo inteiro
        if (startType != PascalType.INT_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): for loop start expression must be of type integer, got '%s'.\n",
                    ctx.start.getLine(), startType.toString());
            System.exit(1);
        }
        
        if (endType != PascalType.INT_TYPE) {
            System.err.printf("SEMANTIC ERROR (%d): for loop end expression must be of type integer, got '%s'.\n",
                    ctx.start.getLine(), endType.toString());
            System.exit(1);
        }
        
        // Cria o nó principal do for
        AST forNode = AST.newSubtree(FOR_NODE, PascalType.INT_TYPE);
        
        // Cria um nó específico para o cabeçalho do for (variável e limites)
        AST forHeadingNode = AST.newSubtree(FOR_HEADING_NODE, PascalType.INT_TYPE);
        forHeadingNode.addChild(varAst);
        forHeadingNode.addChild(startAst);
        forHeadingNode.addChild(endAst);
        forNode.addChild(forHeadingNode);
        
        // Cria um bloco específico para o corpo do loop
        AST forBlockNode = AST.newSubtree(FOR_BLOCK_NODE, PascalType.NO_TYPE);
        
        // Visita o corpo do loop e adiciona ao bloco
        if (ctx.stmt() != null) {
            AST bodyNode = visit(ctx.stmt());
            if (bodyNode != null) {
                forBlockNode.addChild(bodyNode);
            }
        } else if (ctx.structureStmt() != null) {
            AST bodyNode = visit(ctx.structureStmt());
            if (bodyNode != null) {
                forBlockNode.addChild(bodyNode);
            }
        }
        
        forNode.addChild(forBlockNode);
        
        return forNode;
    }

    @Override
    public AST visitExprFor(PascalParser.ExprForContext ctx) {
        // ExprFor pode ser um INTEGER_VALUE ou um IDENTIFIER
        if (ctx.INTEGER_VALUE() != null) {
            return new AST(INT_VAL_NODE, Integer.parseInt(ctx.INTEGER_VALUE().getText()), PascalType.INT_TYPE);
        } else if (ctx.IDENTIFIER() != null) {
            // Verifica se a variável foi declarada e retorna seu tipo
            Token idToken = ctx.IDENTIFIER().getSymbol();
            return checkVar(idToken);
        }
        
        return null; // Should not happen
    }

    @Override
    public AST visitStructureStmt(PascalParser.StructureStmtContext ctx) {
        AST structNode = AST.newSubtree(STRUCTURE_STMT_NODE, NO_TYPE);
        
        if (ctx.stmtList() != null) {
            AST stmtListNode = visit(ctx.stmtList());
            // Adiciona todos os filhos do stmtList ao bloco estruturado
            for (int i = 0; i < stmtListNode.getChildCount(); i++) {
                structNode.addChild(stmtListNode.getChild(i));
            }
        }
        
        return structNode;
    }

    @Override
    public AST visitExprList(PascalParser.ExprListContext ctx) {
        AST exprListNode = AST.newSubtree(EXPR_LIST_NODE, NO_TYPE);
        
        for (PascalParser.ExprContext expr : ctx.expr()) {
            AST exprAst = visit(expr);
            if (exprAst != null) {
                exprListNode.addChild(exprAst);
            }
        }
        
        return exprListNode;
    }

    // Impressão da tabela global de símbolos
    public void printSymbols() {
        symbolTable.printSymbols();
    }

    public void printStrings() {
        stringTable.printStrings();
    }

    public void printAST() {
        AST.printDot(root, symbolTable);
    }
    
    // Métodos getter para acesso às tabelas e AST
    public varTable getVarTable() {
        return symbolTable;
    }
    
    public strTable getStrTable() {
        return stringTable;
    }
    
    public AST getAST() {
        return root;
    }
}