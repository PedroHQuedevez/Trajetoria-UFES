
import java.util.ArrayList;
import java.util.Comparator;

public class Recredenciamento {
    String nomeDocente;
    double pontuacao;
    String recredenciado;

    public enum ordemQualis {
        A1, A2, A3, A4, B1, B2, B3, B4, B5, C;
    }

    public static ArrayList<Recredenciamento> listaRecredenciamento(ArrayList<Docente> docentes,
            ArrayList<Regras> regras, ArrayList<Veiculo> veiculos, int anoAtual) {

        // obtem as informações da regra necessárias para o recredenciamento;
        Regras regraAtual = Regras.getRegraAtual(regras, anoAtual);
        int quantAnosPontos = regraAtual.getQtdeAnosPontos();
        Float vetorPontos[] = regraAtual.constroiVetorPontos();

        ArrayList<Recredenciamento> listaRecredenciamento = new ArrayList<>();

        for (Docente docente : docentes) {
            // obtem informações de recadastramento do docente para comparação;
            String recredenciado = Ocorrencia.EventoRecadastramento(docente.getOcorrencias(), anoAtual);
            Float pontuacao = Recredenciamento.calculaPontuacao(vetorPontos, docente, quantAnosPontos, anoAtual);

            int regraAtualQuantMin = regraAtual.getQuantidadesMinimas().get(0);
            String regraAtualQualisMin = regraAtual.getQualis1().get(regraAtual.getQualis1().size() - 1);

            // cria e adiciona o resultado para o docente;
            if (recredenciado.equals("Nao")) {
                if (docente.idadeDocente(anoAtual) >= 60) {
                    recredenciado = "PPS";
                } else if (docente.tempoIngresso(anoAtual) <= 2) {
                    recredenciado = "PPJ";
                } else if (pontuacao >= regraAtual.getPontuacaoMin()
                        && Recredenciamento.verificaPubMin(veiculos, docente,
                                anoAtual, regraAtual.getQtdeAnosArtigo(), regraAtualQuantMin, regraAtualQualisMin)) {
                    recredenciado = "Sim";
                } else {
                    recredenciado = "Não";
                }
            }

            listaRecredenciamento.add(new Recredenciamento(docente.getNome(), pontuacao,
                    recredenciado));

        }
        listaRecredenciamento.sort(new listaComparatorR());
        return listaRecredenciamento;
    }

    // auxilia na verificação de publicações mínimas;
    public static Boolean verificaPubMin(ArrayList<Veiculo> veiculos, Docente docente, int anoAtual,
            int quantAnosPontos, int quantPubMin,
            String QualiMin) {

        ArrayList<Publicacao> publicacoes = docente.getPublicacoes();
        int limiteAno = anoAtual - quantAnosPontos;
        int quantMinAux = quantPubMin;

        for (Publicacao publicacao : publicacoes) {
            Enum<ordemQualis> qualisEnumPub = ordemQualis.valueOf(publicacao.getQuali());
            Enum<ordemQualis> qualisEnumMin = ordemQualis.valueOf(QualiMin);
            Character tipoVeiculo = Veiculo.verificaTipoVeiculo(veiculos, publicacao.getSiglaVeiculo());

            if ((publicacao.getAno() >= limiteAno) && (qualisEnumPub.ordinal() <= qualisEnumMin.ordinal())
                    && (tipoVeiculo == 'P')) {
                quantMinAux--;
            }
        }

        if (quantMinAux <= 0) {
            return true;
        } else {
            return false;
        }

    }

    public static Float calculaPontuacao(Float vetorPontos[], Docente docente, int quantAnosPontos, int anoAtual) {
        Float pontuacao = 0.0f;
        ArrayList<Publicacao> publicacoes = docente.getPublicacoes();
        for (Publicacao publicacao : publicacoes) {
            String quali = publicacao.getQuali().trim();
            int anoPublicacao = publicacao.getAno();
            int limiteAno = anoAtual - quantAnosPontos;
            if (anoPublicacao >= limiteAno && anoPublicacao < anoAtual) {
                if (quali.equals("A1")) {
                    pontuacao += vetorPontos[0].floatValue();
                } else if (quali.equals("A2")) {
                    pontuacao += vetorPontos[1].floatValue();
                } else if (quali.equals("A3")) {
                    pontuacao += vetorPontos[2].floatValue();
                } else if (quali.equals("A4")) {
                    pontuacao += vetorPontos[3].floatValue();
                } else if (quali.equals("B1")) {
                    pontuacao += vetorPontos[4].floatValue();
                } else if (quali.equals("B2")) {
                    pontuacao += vetorPontos[5].floatValue();
                } else if (quali.equals("B3")) {
                    pontuacao += vetorPontos[6].floatValue();
                } else if (quali.equals("B4")) {
                    pontuacao += vetorPontos[7].floatValue();
                } else if (quali.equals("B5")) {
                    pontuacao += vetorPontos[8].floatValue();
                } else if (quali.equals("C")) {
                    pontuacao += vetorPontos[9].floatValue();
                }
            }
        }
        return pontuacao;
    }

    public Recredenciamento(String nomeDocente, double pontuacao, String recredenciado) {
        this.nomeDocente = nomeDocente;
        this.pontuacao = pontuacao;
        this.recredenciado = recredenciado;
    }

    @Override
    public String toString() {
        return nomeDocente + ";" + String.format("%.1f", pontuacao) + ";" + recredenciado;
    }

    public String getNomeDocente() {
        return nomeDocente;
    }

    public void setNomeDocente(String nomeDocente) {
        this.nomeDocente = nomeDocente;
    }

    public double getPontuacao() {
        return pontuacao;
    }

    public void setPontuacao(double pontuacao) {
        this.pontuacao = pontuacao;
    }

    public String getRecredenciado() {
        return recredenciado;
    }

    public void setRecredenciado(String recredenciado) {
        this.recredenciado = recredenciado;
    }

    public static class listaComparatorR implements Comparator<Recredenciamento> {
        @Override
        public int compare(Recredenciamento r1, Recredenciamento r2) {
            return r1.getNomeDocente().compareTo(r2.getNomeDocente());
        }
    }

}
