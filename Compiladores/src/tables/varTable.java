package tables;

import java.util.ArrayList;
import java.util.Collections;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

import typing.PascalType;

public class varTable {
    // Tipos de símbolos: variável, função ou procedimento
    public enum SymbolKind { VARIABLE, FUNCTION, PROCEDURE, ARRAY }

    // Entrada genérica para variável, função ou procedimento
    public static class Entry {
        public String name;
        public PascalType type; // Tipo da variável ou tipo de retorno da função (PascalType)
        public int lineDeclared;
        public SymbolKind kind;
        public List<Param> params; // Parâmetros se for função/procedimento
        public Map<String, Entry> localTable; // Tabela local para funções/procedimentos

        public Entry(String name, PascalType type, int line, SymbolKind kind) {
            this.name = name;
            this.type = type;
            this.lineDeclared = line;
            this.kind = kind;
            this.params = new ArrayList<>();
            this.localTable = null;
        }
    }

    // Parâmetro de função/procedimento
    public static class Param {
        public String name;
        public PascalType type; // PascalType

        public Param(String name, PascalType type) {
            this.name = name;
            this.type = type;
        }
    }

    // Tabela global: variáveis globais, funções e procedimentos
    private Map<String, Entry> globalTable = new LinkedHashMap<>();

    // Função/procedimento atual (se estiver dentro de um). Ou seja, a tabela local atual
    private Entry currentRoutine = null;

    /**
     * Busca símbolo: primeiro local, depois global
     * @param id Identificador a ser buscado
     * @return Entry correspondente ou null se não encontrado
     */
    public Entry lookup(String id) {
        // Se estiver dentro de uma função ou procedimento, procura na tabela local
        if (currentRoutine != null && currentRoutine.localTable != null && currentRoutine.localTable.containsKey(id))
            return currentRoutine.localTable.get(id);
        return globalTable.get(id);
    }

    /**
     * Adiciona uma entrada na tabela global
     * @param id Identificador
     * @param entry Entrada a ser adicionada
     * @return true se adicionado com sucesso, false se já existe
     */
    public boolean addGlobal(String id, Entry entry) {
        if (globalTable.containsKey(id)) {
            return false;
        }
        globalTable.put(id, entry);
        return true;
    }

    /**
     * Adiciona uma entrada na tabela local (se houver rotina atual)
     * @param id Identificador
     * @param entry Entrada a ser adicionada
     * @return true se adicionado com sucesso, false se já existe ou não há rotina atual
     */
    public boolean addLocal(String id, Entry entry) {
        if (currentRoutine == null || currentRoutine.localTable == null) {
            return false;
        }
        if (currentRoutine.localTable.containsKey(id)) {
            return false;
        }
        currentRoutine.localTable.put(id, entry);
        return true;
    }

    /**
     * Adiciona entrada na tabela apropriada (local se houver, senão global)
     * @param id Identificador
     * @param entry Entrada a ser adicionada
     * @return true se adicionado com sucesso, false se já existe
     */
    public boolean add(String id, Entry entry) {
        Map<String, Entry> table = (currentRoutine == null) ? globalTable : currentRoutine.localTable;
        if (table.containsKey(id)) {
            return false;
        }
        table.put(id, entry);
        return true;
    }

    /**
     * Verifica se um identificador existe na tabela apropriada
     * @param id Identificador
     * @return true se existe, false caso contrário
     */
    public boolean contains(String id) {
        return lookup(id) != null;
    }

    public String getName(String id) {
        Entry entry = lookup(id);
        return (entry != null) ? entry.name : null;
    }

    /**
     * Obtém a entrada da tabela global
     * @param id Identificador
     * @return Entry ou null se não encontrado
     */
    public Entry getGlobal(String id) {
        return globalTable.get(id);
    }

    /**
     * Define a rotina atual (para escopo local)
     * @param routine Entry da função/procedimento atual
     */
    public void setCurrentRoutine(Entry routine) {
        this.currentRoutine = routine;
    }

    /**
     * Obtém a rotina atual
     * @return Entry da rotina atual ou null
     */
    public Entry getCurrentRoutine() {
        return currentRoutine;
    }

    /**
     * Obtém todos os nomes de variáveis na tabela global
     * @return Lista de nomes de variáveis
     */
    public List<String> getAllVarNames() {
        List<String> varNames = new ArrayList<>();
        for (Entry entry : globalTable.values()) {
            if (entry.kind == SymbolKind.VARIABLE || entry.kind == SymbolKind.ARRAY) {
                varNames.add(entry.name);
            }
        }
        return varNames;
    }

    /**
     * Obtém o tipo de uma variável na tabela global
     * @param id Identificador da variável
     * @return PascalType do identificador ou null se não encontrado
     */
    public PascalType getType(String id) {
        Entry entry = lookup(id);
        return (entry != null) ? entry.type : null;
    }
    
    /**
     * Retorna a tabela global (imutável)
     * @return Map contendo a tabela global
     */
    public Map<String, Entry> getGlobalTable() {
        return Collections.unmodifiableMap(globalTable);
    }

    /**
     * Limpa todas as tabelas
     */
    public void clear() {
        globalTable.clear();
        currentRoutine = null;
    }

    /**
     * Imprime a tabela global de símbolos
     */
    public void printSymbols() {
        System.out.println("Global symbol table:");
        int i = 0;
        for (Entry e : globalTable.values()) {                System.out.printf("Entry %d -- name: %s, kind: %s, line: %d, type: %s\n",
                i++, e.name, e.kind, e.lineDeclared, e.type);

            // Se for função ou procedimento, imprime parâmetros e variáveis locais
            if (e.kind == SymbolKind.FUNCTION || e.kind == SymbolKind.PROCEDURE) {
                System.out.print("  Params: ");
                for (Param p : e.params) {
                    System.out.printf("%s:%s ", p.name, p.type);
                }

                System.out.println();

                System.out.println("  Local variables:");
                if (e.localTable != null) {
                    for (Entry local : e.localTable.values()) {
                        System.out.printf("    %s : %s\n", local.name, local.type);
                    }
                }
            }
        }
    }
}
