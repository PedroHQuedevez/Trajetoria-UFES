package tables;

import java.util.*;

public class strTable {
    // Conjunto de strings literais (para evitar duplicatas e manter a ordem de inserção)
    private Set<String> strings = new LinkedHashSet<>();

    /**
     * Adiciona uma string à tabela, se ainda não estiver lá
     * @param str A string a ser adicionada (sem aspas)
     * @return true se a string foi adicionada, false se já existia
     */
    public boolean addString(String str) {
        if (strings.contains(str)) {
            return false;
        }
        strings.add(str);
        return true;
    }

    /**
     * Verifica se uma string existe na tabela
     * @param str A string a ser verificada
     * @return true se a string existe, false caso contrário
     */
    public boolean contains(String str) {
        return strings.contains(str);
    }

    /**
     * Retorna o conjunto de strings (imutável)
     * @return Set contendo todas as strings
     */
    public Set<String> getStrings() {
        return Collections.unmodifiableSet(strings);
    }

    /**
     * Retorna o número de strings na tabela
     * @return Número de strings
     */
    public int size() {
        return strings.size();
    }

    /**
     * Limpa todas as strings da tabela
     */
    public void clear() {
        strings.clear();
    }

    /**
     * Imprime a tabela de strings
     */
    public void printStrings() {
        System.out.println("Strings table:");
        int i = 0;
        for (String s : strings) {
            System.out.printf("Entry %d -- \"%s\"\n", i++, s);
        }
    }
}
