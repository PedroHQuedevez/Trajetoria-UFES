package ast;

import typing.PascalType;
import static typing.PascalType.NO_TYPE;

import java.util.ArrayList;
import java.util.List;

import tables.varTable;

// Implementação dos nós da AST (Abstract Syntax Tree) para a linguagem Pascal.
public class AST {

    //Todos os campos são finais para simplificar
    public final NodeKind kind;

    // Dados adicionais para alguns tipos de nós
    public final int intData; 
    public final String strData;
    public final float realData;
    public final boolean boolData;

    public final PascalType type;
    private final List<AST> children; // privado para evitar modificações externas

	// Construtor completo para poder tornar todos os campos finais.
    // Privado porque não queremos os dois campos 'data' preenchidos ao mesmo tempo.
    private AST(NodeKind kind, int intData, String strData, float realData, boolean boolData, PascalType type) {
        this.kind = kind;
        this.intData = intData;
        this.strData = strData;
        this.realData = realData;
        this.boolData = boolData;
        this.type = type != null ? type : NO_TYPE; // Garante que o tipo nunca seja nulo
        this.children = new ArrayList<>();
    }

    // Com dado inteiro
    public AST(NodeKind kind, int intData, PascalType type) {
        this(kind, intData, null, 0.0f, false, type);
    }

    // Com dado string
    public AST(NodeKind kind, String strData, PascalType type) {
        this(kind, 0, strData, 0.0f, false, type);
    }

    // Com dado real
    public AST(NodeKind kind, float realData, PascalType type) {
        this(kind, 0, null, realData, false, type);
    }

    // Com dado booleano
    public AST(NodeKind kind, boolean boolData, PascalType type) {
        this(kind, 0, null, 0.0f, boolData, type);
    }

    // Adiciona um filho ao nó
    public void addChild(AST child) {
        if (child != null) {
            this.children.add(child);
        }
    }

    // Retorna o número de filhos do nó
    public int getChildCount() {
        return this.children.size();
    }

    // Retorna o filho no índice passado
    public AST getChild(int index) {
        if (index < 0 || index >= children.size()) {
            throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + children.size());
        }
        return this.children.get(index);
    }

    // Cria um nó e pendura todos os filhos passados como argumento.
    public static AST newSubtree(NodeKind kind, PascalType type, AST... children) {
        AST node = new AST(kind, 0, null, 0.0f, false, type);
        for (AST child : children) {
            if (child != null) {
                node.addChild(child);
            }
        }
        return node;
    }

    // Variáveis internas usadas para geração da saída em DOT.
	// Estáticas porque só precisamos de uma instância.
	private static int nr;

    // Imprime recursivamente a codificação em DOT da subárvore começando no nó atual.
	// Usa stderr como saída para facilitar o redirecionamento
    private int printNodeDot() {
		int myNr = nr++;

	    System.err.printf("node%d[label=\"", myNr);
	    if (this.type != NO_TYPE) {
	    	System.err.printf("(%s) ", this.type.toString());
	    }
	    if (this.kind == NodeKind.VAR_DECL_NODE || this.kind == NodeKind.VAR_USE_NODE) {
	    	System.err.printf("%s@", this.strData);
	    } else {
	    	System.err.printf("%s", this.kind.toString());
	    }
	    if (NodeKind.hasData(this.kind)) {
	        if (this.kind == NodeKind.REAL_VAL_NODE) {
                System.err.printf(" %.2f", this.realData);
            } else if (this.kind == NodeKind.INT_VAL_NODE) {
                System.err.printf(" %d", this.intData);
            } else if (this.kind == NodeKind.BOOL_VAL_NODE) {
                System.err.printf(" %s", this.boolData ? "true" : "false");
            } else if (this.kind == NodeKind.STRING_VAL_NODE) {
                System.err.printf(" \\\"%s\\\"", this.strData.replace("\"", "\\\""));
            }
	    }
	    System.err.printf("\"];\n");

	    for (int i = 0; i < this.children.size(); i++) {
	        int childNr = this.children.get(i).printNodeDot();
	        System.err.printf("node%d -> node%d;\n", myNr, childNr);
	    }
	    return myNr;
	}

    // Imprime a árvore toda em stderr.
	public static void printDot(AST tree, varTable table) {
	    nr = 0;
	    System.err.printf("digraph {\ngraph [ordering=\"out\"];\n");
	    tree.printNodeDot();
	    System.err.printf("}\n");
	}
}
