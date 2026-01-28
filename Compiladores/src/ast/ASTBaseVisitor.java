package ast;

public abstract class ASTBaseVisitor<T> {
    public void execute(AST root) {
        visit(root);
    }


    protected T visit(AST node) {
        switch (node.kind) {
            case ASSIGN_NODE:               return visitAssign(node);
            case EQ_NODE:                   return visitEq(node);
            case LT_NODE:                   return visitLt(node);
            case LE_NODE:                   return visitLe(node);
            case GT_NODE:                   return visitGt(node);
            case GE_NODE:                   return visitGe(node);
            case NE_NODE:                   return visitNe(node);
            case BLOCK_NODE:                return visitBlock(node);
            case BOOL_VAL_NODE:             return visitBoolVal(node);
            case IF_NODE:                   return visitIf(node);
            case INT_VAL_NODE:              return visitIntVal(node);
            case REAL_VAL_NODE:             return visitRealVal(node);
            case STRING_VAL_NODE:           return visitStringVal(node);
            case MINUS_NODE:                return visitMinus(node);
            case PLUS_NODE:                 return visitPlus(node);
            case MULT_NODE:                 return visitMult(node);
            case DIV_NODE:                  return visitDiv(node);
            case PROGRAM_NODE:              return visitProgram(node);
            case READ_NODE:                 return visitRead(node);
            case WRITE_NODE:                return visitWrite(node);
            case FOR_NODE:                  return visitFor(node);
            case FOR_HEADING_NODE:          return visitForHeading(node);
            case FOR_BLOCK_NODE:            return visitForBlock(node);
            case VAR_DECL_NODE:             return visitVarDecl(node);
            case VAR_LIST_NODE:             return visitVarList(node);
            case VAR_USE_NODE:              return visitVarUse(node);
            case IDENTIFIER_NODE:           return visitIdentifier(node);
            case ARRAY_TYPE_NODE:           return visitArrayType(node);
            case ARRAY_ACCESS_NODE:         return visitArrayAccess(node);
            case FUNCTION_CALL_NODE:        return visitFunctionCall(node);
            case FUNCTION_DECL_NODE:        return visitFunctionDecl(node);
            case FUNCTION_SECT_NODE:        return visitFunctionSect(node);
            case PROCEDURE_DECL_NODE:       return visitProcedureDecl(node);
            case PROCEDURE_SECT_NODE:       return visitProcedureSect(node);
            case PARAM_LIST_NODE:           return visitParamList(node);
            case EXPR_LIST_NODE:            return visitExprList(node);
            case NOT_NODE:                  return visitNot(node);
            case AND_NODE:                  return visitAnd(node);
            case OR_NODE:                   return visitOr(node);
            case FUNCTION_HEADING_NODE:     return visitFunctionHeading(node);
            case PROCEDURE_HEADING_NODE:    return visitProcedureHeading(node);
            case FUNCTION_BLOCK_NODE:       return visitFunctionBlock(node);
            case PROCEDURE_BLOCK_NODE:      return visitProcedureBlock(node);
            case STMT_LIST_NODE:            return visitStmtList(node);
            case STRUCTURE_STMT_NODE:       return visitStructureStmt(node);
            case B2I_NODE:                  return visitB2I(node);
            case B2R_NODE:                  return visitB2R(node);
            case B2S_NODE:                  return visitB2S(node);
            case I2R_NODE:                  return visitI2R(node);
            case I2S_NODE:                  return visitI2S(node);
            case R2S_NODE:                  return visitR2S(node);
            default:
                System.err.printf("Invalid kind: %s!\n", node.kind.toString());
                System.exit(1);
                return null;
        }
    }

    // Métodos especializados para visitar um nó com um certo 'kind'.
    protected abstract T visitAssign(AST node);
    protected abstract T visitEq(AST node);
    protected abstract T visitLt(AST node);
    protected abstract T visitLe(AST node);
    protected abstract T visitGt(AST node);
    protected abstract T visitGe(AST node);
    protected abstract T visitNe(AST node);
    protected abstract T visitBlock(AST node);
    protected abstract T visitBoolVal(AST node);
    protected abstract T visitIf(AST node);
    protected abstract T visitIntVal(AST node);
    protected abstract T visitRealVal(AST node);
    protected abstract T visitStringVal(AST node);
    protected abstract T visitMinus(AST node);
    protected abstract T visitPlus(AST node);
    protected abstract T visitMult(AST node);
    protected abstract T visitDiv(AST node);
    protected abstract T visitProgram(AST node);
    protected abstract T visitRead(AST node);
    protected abstract T visitWrite(AST node);
    protected abstract T visitFor(AST node);
    protected abstract T visitForHeading(AST node);
    protected abstract T visitForBlock(AST node);
    protected abstract T visitVarDecl(AST node);
    protected abstract T visitVarList(AST node);
    protected abstract T visitVarUse(AST node);
    protected abstract T visitIdentifier(AST node);
    protected abstract T visitArrayType(AST node);
    protected abstract T visitArrayAccess(AST node);
    protected abstract T visitFunctionCall(AST node);
    protected abstract T visitFunctionDecl(AST node);
    protected abstract T visitFunctionSect(AST node);
    protected abstract T visitProcedureDecl(AST node);
    protected abstract T visitProcedureSect(AST node);
    protected abstract T visitParamList(AST node);
    protected abstract T visitExprList(AST node);
    protected abstract T visitNot(AST node);
    protected abstract T visitAnd(AST node);
    protected abstract T visitOr(AST node);
    protected abstract T visitFunctionHeading(AST node);
    protected abstract T visitProcedureHeading(AST node);
    protected abstract T visitFunctionBlock(AST node);
    protected abstract T visitProcedureBlock(AST node);
    protected abstract T visitStmtList(AST node);
    protected abstract T visitStructureStmt(AST node);
    protected abstract T visitB2I(AST node);
    protected abstract T visitB2R(AST node);
    protected abstract T visitB2S(AST node);
    protected abstract T visitI2R(AST node);
    protected abstract T visitI2S(AST node);
    protected abstract T visitR2S(AST node);

}
