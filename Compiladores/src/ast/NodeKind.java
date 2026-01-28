package ast;

// Enumeração dos tipos de nós de uma AST para Pascal.
public enum NodeKind {
    ASSIGN_NODE,
    EQ_NODE,
    LT_NODE,
    LE_NODE,
    GT_NODE,
    GE_NODE,
    NE_NODE,
    BLOCK_NODE,
    BOOL_VAL_NODE,
    IF_NODE,
    INT_VAL_NODE,
    REAL_VAL_NODE,
    STRING_VAL_NODE,
    MINUS_NODE,
    PLUS_NODE,
    MULT_NODE,
    DIV_NODE,
    PROGRAM_NODE,
    READ_NODE,
    WRITE_NODE,
    FOR_NODE,
    FOR_HEADING_NODE, // Usado para o cabeçalho do loop 'for'
    FOR_BLOCK_NODE, // Usado para o corpo do loop 'for'
    VAR_DECL_NODE,
    VAR_LIST_NODE,
    VAR_USE_NODE,
    IDENTIFIER_NODE,
    ARRAY_TYPE_NODE,
    ARRAY_ACCESS_NODE,
    FUNCTION_CALL_NODE,
    FUNCTION_DECL_NODE,
    FUNCTION_SECT_NODE,    // Seção de funções
    PROCEDURE_DECL_NODE,
    PROCEDURE_SECT_NODE,   // Seção de procedimentos
    PARAM_LIST_NODE,
    EXPR_LIST_NODE,
    NOT_NODE,
    AND_NODE,
    OR_NODE,
    // Nós adicionais necessários para AST completa
    FUNCTION_HEADING_NODE,
    PROCEDURE_HEADING_NODE,
    FUNCTION_BLOCK_NODE,
    PROCEDURE_BLOCK_NODE,
    STMT_LIST_NODE,
    STRUCTURE_STMT_NODE,
    // Type conversion nodes
    B2I_NODE,
    B2R_NODE,
    B2S_NODE,
    I2R_NODE,
    I2S_NODE,
    R2S_NODE;

    public String toString() {
        switch(this) {
            case ASSIGN_NODE:       return ":=";
            case EQ_NODE:           return "=";
            case LT_NODE:           return "<";
            case LE_NODE:           return "<=";
            case GT_NODE:           return ">";
            case GE_NODE:           return ">=";
            case NE_NODE:           return "<>";
            case BLOCK_NODE:        return "block";
            case BOOL_VAL_NODE:     return "";
            case IF_NODE:           return "if";
            case INT_VAL_NODE:      return "";
            case REAL_VAL_NODE:     return "";
            case STRING_VAL_NODE:   return "";
            case MINUS_NODE:        return "-";
            case PLUS_NODE:         return "+";
            case MULT_NODE:        return "*";
            case DIV_NODE:          return "/";
            case PROGRAM_NODE:      return "program";
            case READ_NODE:         return "read";
            case WRITE_NODE:        return "write";
            case FOR_NODE:          return "for";
            case FOR_HEADING_NODE:   return "for_heading"; // Cabeçalho do loop 'for'
            case FOR_BLOCK_NODE:     return "for_block"; // Corpo do loop 'for'
            case VAR_DECL_NODE:     return "var_decl";
            case VAR_LIST_NODE:     return "var_list";
            case VAR_USE_NODE:      return "var_use";
            case IDENTIFIER_NODE:   return "identifier";
            case ARRAY_TYPE_NODE:   return "array_type";
            case ARRAY_ACCESS_NODE: return "array_access";
            case FUNCTION_CALL_NODE: return "function_call";
            case FUNCTION_DECL_NODE: return "function_decl";
            case FUNCTION_SECT_NODE: return "function_sect";
            case PROCEDURE_DECL_NODE: return "procedure_decl";
            case PROCEDURE_SECT_NODE: return "procedure_sect";
            case PARAM_LIST_NODE:   return "param_list";
            case EXPR_LIST_NODE:    return "expr_list";
            case NOT_NODE:          return "not";
            case AND_NODE:          return "and";
            case OR_NODE:           return "or";
            case FUNCTION_HEADING_NODE: return "function_heading";
            case PROCEDURE_HEADING_NODE: return "procedure_heading";
            case FUNCTION_BLOCK_NODE: return "function_block";
            case PROCEDURE_BLOCK_NODE: return "procedure_block";
            case STMT_LIST_NODE:    return "stmt_list";
            case STRUCTURE_STMT_NODE: return "structure_stmt";
            case B2I_NODE:          return "B2I";
            case B2R_NODE:          return "B2R";
            case B2S_NODE:          return "B2S";
            case I2R_NODE:          return "I2R";
            case I2S_NODE:          return "I2S";
            case R2S_NODE:          return "R2S";
            default:
                System.err.println("ERROR: Fall through in NodeKind enumeration!");
                System.exit(1);
                return "";
        }
    }

    public static boolean hasData(NodeKind kind) {
        switch(kind) {
            case BOOL_VAL_NODE:
            case INT_VAL_NODE:
            case REAL_VAL_NODE:
            case STRING_VAL_NODE:
            case VAR_DECL_NODE:
            case VAR_USE_NODE:
            case IDENTIFIER_NODE:
                return true;
            default:
                return false;
        }
    }
}