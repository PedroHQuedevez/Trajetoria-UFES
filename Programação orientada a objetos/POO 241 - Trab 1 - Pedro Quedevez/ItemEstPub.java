
import java.util.ArrayList;

public class ItemEstPub {
    String qualis;
    Float numArtigos;
    Float numArtigosPorDocente;

    public ItemEstPub(String qualis, Float numArtigos, Float numArtigosPorDocente) {
        this.qualis = qualis;
        this.numArtigos = numArtigos;
        this.numArtigosPorDocente = numArtigosPorDocente;
    }

    public static ArrayList<ItemEstPub> criaListEstats(ArrayList<Publicacao> publicacoes) {
        // criar um elemento para cada qualis;

        ArrayList<ItemEstPub> estats = new ArrayList<>();
        // cria vetores com tamnhos iguais para armazenar os valores calculados;
        // coloca cada tripla de valores em um objeto ItemEstPub e adiciona na lista
        // estats para gerar o arquivo de saída;
        String qualis[] = { "A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "B5", "C" };
        Float numArtigos[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        Float numAutores[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

        for (int i = 0; i < qualis.length; i++) {
            for (Publicacao publicacao : publicacoes) {
                if (publicacao.getQuali().equals(qualis[i])) {
                    numArtigos[i]++;
                    Float numAutoresTemp = Float.valueOf(publicacao.getListaAutores().size());
                    if (numAutoresTemp != 0) {
                        numAutores[i] += (1f / numAutoresTemp);
                    }
                }
            }
        }

        for (int i = 0; i < qualis.length; i++) {

            estats.add(new ItemEstPub(qualis[i], numArtigos[i], numAutores[i]));

        }

        return estats;

    }

    @Override
    public String toString() {
        return qualis + ";" + (String.format("%.0f", numArtigos)) + ";" + (String.format("%.2f", numArtigosPorDocente));
    }

    public String getQualis() {
        return qualis;
    }

    public void setQualis(String qualis) {
        this.qualis = qualis;
    }

    public Float getNumArtigos() {
        return numArtigos;
    }

    public void setNumArtigos(Float numArtigos) {
        this.numArtigos = numArtigos;
    }

    public Float getNumArtigosPorDocente() {
        return numArtigosPorDocente;
    }

    public void setNumArtigosPorDocente(Float numArtigosPorDocente) {
        this.numArtigosPorDocente = numArtigosPorDocente;
    }
}
