package code;

import java.util.HashMap;

import tables.varTable;

// Implementação de uma memória (hash) de values, com os métodos que facilitam acessar um valor
public class Memory {
    // A chave será o nome da variável presente na tabela de variáveis
    // O valor será um objeto Value que contém o tipo e os dados
    private HashMap<String, Value> memory;

    public Memory(varTable vt) {
        this.memory = new HashMap<>();
        // Inicializa a memória com as variáveis da tabela de variáveis
        for (String varName : vt.getAllVarNames()) {
            memory.put(varName, new Value(vt.getType(varName))); // Inicializa com valor padrão
        }
    }

    // Adiciona um valor à memória
    public void addValue(String name, Value value) {
        memory.put(name, value);
    }

    // Obtém um valor da memória
    public Value getValue(String name) {
        return memory.get(name);
    }

    // Verifica se um valor existe na memória
    public boolean containsValue(String name) {
        return memory.containsKey(name);
    }

    // Remove um valor da memória
    public void removeValue(String name) {
        memory.remove(name);
    }

    // Atualiza um valor na memória
    public void updateValue(String name, Value value) {
        if (memory.containsKey(name)) {
            memory.put(name, value);
        } else {
            throw new IllegalArgumentException("Value with name " + name + " does not exist in memory.");
        }
    }
    
}
