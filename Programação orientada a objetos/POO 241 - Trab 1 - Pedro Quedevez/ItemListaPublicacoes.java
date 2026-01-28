
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;

public class ItemListaPublicacoes {
    int ano;
    String siglaVeiculo;
    String nomeVeiculo;
    String qualis;
    double fatorImpacto;
    String tituloPublicacao;
    ArrayList<String> nomesDocentes;
    Enum<ordemQualis> qualisEnum;

    public enum ordemQualis {
        A1, A2, A3, A4, B1, B2, B3, B4, B5, C;
    }

    // recebe dois qualis e utiliza o enum definido aqui para comparar;
    public static boolean comparaQualis(String qualis1, String qualis2) {
        ordemQualis q1 = ordemQualis.valueOf(qualis1);
        ordemQualis q2 = ordemQualis.valueOf(qualis2);
        return q1.ordinal() > q2.ordinal();
    }

    public static ArrayList<ItemListaPublicacoes> criaListaPublicacoes(ArrayList<Publicacao> publicacoes,
            ArrayList<Docente> docentes,
            ArrayList<Veiculo> veiculos) {
        ArrayList<ItemListaPublicacoes> listaPublicacoes = new ArrayList<ItemListaPublicacoes>();
        for (Publicacao publicacao : publicacoes) {
            listaPublicacoes.add(new ItemListaPublicacoes(publicacao, docentes, veiculos));
        }

        Collections.sort(listaPublicacoes, new listaComparator());
        return listaPublicacoes;
    }

    public ItemListaPublicacoes(Publicacao publicacao, ArrayList<Docente> docentes,
            ArrayList<Veiculo> veiculos) {
        this.ano = publicacao.getAno();
        this.siglaVeiculo = publicacao.getSiglaVeiculo();
        this.tituloPublicacao = publicacao.getTitulo();
        for (Veiculo veiculo : veiculos) {
            if (veiculo.getSigla().equals(this.siglaVeiculo)) {
                this.nomeVeiculo = veiculo.getNome();
                this.fatorImpacto = veiculo.getFatorImpacto();
            }
        }
        this.qualis = publicacao.getQuali();

        try {
            this.qualisEnum = ordemQualis.valueOf(this.qualis);
        } catch (IllegalArgumentException e) {
            this.qualisEnum = null;
        }

        this.nomesDocentes = new ArrayList<String>();
        for (Long codigo : publicacao.getListaAutores()) {
            for (Docente docente : docentes) {
                if (docente.getCodigo().equals(codigo)) {
                    this.nomesDocentes.add(docente.getNome());
                }
            }
        }
    }

    @Override
    public String toString() {
        String todosNomes = "";
        for (String nome : nomesDocentes) {
            todosNomes += nome + ",";
        }
        todosNomes = todosNomes.substring(0, todosNomes.length() - 1);
        return ano + ";" + siglaVeiculo + ";" + nomeVeiculo + ";" + qualis + ";"
                + String.format("%.3f", fatorImpacto) + ";" + tituloPublicacao + ";" + todosNomes;
    }

    public int getAno() {
        return ano;
    }

    public void setAno(int ano) {
        this.ano = ano;
    }

    public String getSiglaVeiculo() {
        return siglaVeiculo;
    }

    public void setSiglaVeiculo(String siglaVeiculo) {
        this.siglaVeiculo = siglaVeiculo;
    }

    public String getNomeVeiculo() {
        return nomeVeiculo;
    }

    public void setNomeVeiculo(String nomeVeiculo) {
        this.nomeVeiculo = nomeVeiculo;
    }

    public String getQualis() {
        return qualis;
    }

    public void setQualis(String qualis) {
        this.qualis = qualis;
    }

    public double getFatorImpacto() {
        return fatorImpacto;
    }

    public void setFatorImpacto(double fatorImpacto) {
        this.fatorImpacto = fatorImpacto;
    }

    public String getTituloPublicacao() {
        return tituloPublicacao;
    }

    public void setTituloPublicacao(String tituloPublicacao) {
        this.tituloPublicacao = tituloPublicacao;
    }

    public ArrayList<String> getNomesDocentes() {
        return nomesDocentes;
    }

    public void setNomesDocentes(ArrayList<String> nomesDocentes) {
        this.nomesDocentes = nomesDocentes;
    }

    // comparador para ordenar os elementos;
    public static class listaComparator implements Comparator<ItemListaPublicacoes> {
        @Override
        public int compare(ItemListaPublicacoes p1, ItemListaPublicacoes p2) {
            int resultadoCompQualis = p1.qualisEnum.ordinal() - p2.qualisEnum.ordinal(); // usa os valores definidos em
                                                                                         // enum;
            if (resultadoCompQualis != 0) { // se qualis for igual, passa para a próxima comparação;
                return resultadoCompQualis; // se forem diferentes, já tem um resultado da comparação para retornar;
            }

            // seguindo a mesma ideia, verificar se diferente de zero.
            // se for zero, significa empate, passa para a próxima comparação;
            // se for diferente de zero, já tem um resultado da comparação para retornar;
            int resultadoCompAno = p2.ano - p1.ano;
            if (resultadoCompAno != 0) {
                return resultadoCompAno;
            }

            int resultadoCompSiglaVeiculo = p1.siglaVeiculo.compareTo(p2.siglaVeiculo);
            if (resultadoCompSiglaVeiculo != 0) {
                return resultadoCompSiglaVeiculo;
            }

            // caso nenhum dos outros returns tenha sido chamado, retorna a comparação dos
            // títulos;
            return p1.tituloPublicacao.compareTo(p2.tituloPublicacao);

        }
    }

}
