package typing;

// Enumeração dos tipos que podem existir em Pascal.

import parser.PascalLexer;

public enum PascalType {
    INT_TYPE,
    REAL_TYPE,
    BOOL_TYPE,
    STR_TYPE,
    FUNCTION_TYPE,
    PROCEDURE_TYPE,
    NO_TYPE; // Usado para indicar que não há tipo definido

    public static PascalType getVarType(int lexerTokenType) {
        switch (lexerTokenType) {
            case PascalLexer.INTEGER: return INT_TYPE;
            case PascalLexer.REAL: return REAL_TYPE;
            case PascalLexer.BOOLEAN: return BOOL_TYPE;
            case PascalLexer.STRING: return STR_TYPE;
            case PascalLexer.FUNCTION: return FUNCTION_TYPE;
            case PascalLexer.PROCEDURE: return PROCEDURE_TYPE;
        }
        return null;
    }

    public String toString() {
        switch (this) {
            case INT_TYPE: return "integer";
            case REAL_TYPE: return "real";
            case BOOL_TYPE: return "boolean";
            case STR_TYPE: return "string";
            case FUNCTION_TYPE: return "function";
            case PROCEDURE_TYPE: return "procedure";
            case NO_TYPE: return "no_type";
        }
        return null;
    }

    // Tabela de unificação de tipos primitivos para o
	// operador '+'. 
    private static PascalType plusMinus[][] = {
        // Só é possível com os tipos INT_TYPE e REAL_TYPE.
        { INT_TYPE,  REAL_TYPE, NO_TYPE, NO_TYPE },
        { REAL_TYPE, REAL_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE }
    };

    public PascalType unifyPlusMinus(PascalType that) {
        return plusMinus[this.ordinal()][that.ordinal()];
    }


    // Tabela de unificação de tipos primitivos para os
    // Operador '*'.
    private static PascalType mult[][] = {
        // Só é possível com os tipos INT_TYPE e REAL_TYPE.
        { INT_TYPE,  REAL_TYPE, NO_TYPE, NO_TYPE },
        { REAL_TYPE, REAL_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE }
    };

    public PascalType unifyMult(PascalType that) {
        return mult[this.ordinal()][that.ordinal()];
    }

    // Tabela de unificação de tipos primitivos para os
    // Operador '/'.
    private static PascalType slash[][] = {
        // Só é possível com os tipos INT_TYPE e REAL_TYPE.
        { REAL_TYPE,  REAL_TYPE, NO_TYPE, NO_TYPE },
        { REAL_TYPE, REAL_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE, NO_TYPE }
    };

    public PascalType unifyslash(PascalType that) {
        return slash[this.ordinal()][that.ordinal()];
    }

    // Tabela de unificação de tipos primitivos para os
    // Operador 'div'
    private static PascalType div[][] = {
        // Só é possível com os tipos INT_TYPE.
        { INT_TYPE,  NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE }
    };

    public PascalType unifyDiv(PascalType that) {
        return div[this.ordinal()][that.ordinal()];
    }

    // Tabela de unificação de tipos primitivos para os
    // Operador 'mod'
    private static PascalType mod[][] = {
        // Só é possível com os tipos INT_TYPE.
        { INT_TYPE,  NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE, NO_TYPE, NO_TYPE }
    };

    public PascalType unifyMod(PascalType that) {
        return mod[this.ordinal()][that.ordinal()];
    }

    // Tabela de unificação de tipos primitivos para os
    // Operadores relacionais.
    private static PascalType rel[][] = {
        // Só é possível com os tipos INT_TYPE, REAL_TYPE e BOOL_TYPE.
        { BOOL_TYPE, BOOL_TYPE, NO_TYPE, NO_TYPE },
        { BOOL_TYPE, BOOL_TYPE, NO_TYPE, NO_TYPE },
        { NO_TYPE, NO_TYPE, BOOL_TYPE, NO_TYPE },
        { NO_TYPE,   NO_TYPE,   NO_TYPE,   BOOL_TYPE }
    };

    public PascalType unifyRel(PascalType that) {
        return rel[this.ordinal()][that.ordinal()];
    }
}
