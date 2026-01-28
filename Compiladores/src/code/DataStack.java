package code;

import java.util.Stack;

/*
 * Implementação de uma pilha de dados para armazenar valores do tipo Value, com os valores intermediários de execução.

 */
@SuppressWarnings("serial")
public final class DataStack extends Stack<Value> {
	
	public void pushValue(Value value) {
        push(value);
    }

    public Value popValue() {
        if (isEmpty()) {
            throw new IllegalStateException("DataStack is empty");
        }
        return pop();
    }
}
