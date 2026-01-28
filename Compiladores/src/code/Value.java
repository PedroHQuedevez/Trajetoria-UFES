package code;

import typing.PascalType;
import java.util.HashMap;
import java.util.Map;

public class Value {
    private PascalType type;
    private Object data;
    private boolean isArray;
    private Map<Integer, Value> arrayData; // Para arrays - mapeamento índice -> valor

    public Value(PascalType type, Object data) {
        this.type = type;
        this.isArray = false;
        this.arrayData = null;
        
        // Se data for null, inicializar data de acordo com o tipo
        if (data == null) {
            switch (type) {
                case INT_TYPE:
                    this.data = 0;
                    break;
                case REAL_TYPE:
                    this.data = 0.0f;
                    break;
                case STR_TYPE:
                    this.data = "";
                    break;
                case BOOL_TYPE:
                    this.data = false;
                    break;
                default:
                    this.data = null;
            }
        } else {
            this.data = data; // Se data não for null, usar o valor fornecido
        }
    }
    
    // Construtor adicional para facilitar criação de valores com valor padrão
    public Value(PascalType type) {
        this(type, null);
    }
    
    // Construtor para arrays
    public Value(PascalType elementType, boolean isArray) {
        this.type = elementType;
        this.isArray = isArray;
        if (isArray) {
            this.arrayData = new HashMap<>();
            this.data = null;
        } else {
            this.arrayData = null;
            // Inicializa valor padrão
            switch (elementType) {
                case INT_TYPE:
                    this.data = 0;
                    break;
                case REAL_TYPE:
                    this.data = 0.0f;
                    break;
                case STR_TYPE:
                    this.data = "";
                    break;
                case BOOL_TYPE:
                    this.data = false;
                    break;
                default:
                    this.data = null;
            }
        }
    }

    public PascalType getType() {
        return type;
    }

    public Object getData() {
        return data;
    }

    public void setData(Object data) {
        this.data = data;
    }
    
    public boolean isArray() {
        return isArray;
    }
    
    // Métodos para manipulação de arrays
    public void setArrayElement(int index, Value value) {
        if (!isArray) {
            throw new RuntimeException("Trying to set array element on non-array value");
        }
        arrayData.put(index, value);
    }
    
    public Value getArrayElement(int index) {
        if (!isArray) {
            throw new RuntimeException("Trying to get array element from non-array value");
        }
        Value element = arrayData.get(index);
        if (element == null) {
            // Retorna valor padrão se o elemento não foi inicializado
            element = new Value(type);
        }
        return element;
    }

    @Override
    public String toString() {
        return "Value{" +
                "type=" + type +
                ", data=" + data +
                '}';
    }
}
