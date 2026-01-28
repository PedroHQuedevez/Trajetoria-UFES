import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.ParseException;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Locale;

public class Regras {

    private LocalDate dataInicio;
    private LocalDate dataFim;
    private ArrayList<String> qualis1;
    private ArrayList<String> pontos;
    private int qtdeAnosPontos;
    private ArrayList<String> qualis2;
    private ArrayList<Integer> quantidadesMinimas;
    private int qtdeAnosArtigo;
    private Float pontuacaoMin;

    private static ArrayList<Regras> datasCadastradas = new ArrayList<Regras>();

    private static Boolean verificaDataValida(LocalDate inicio, LocalDate fim) {
        for (Regras regra : datasCadastradas) {
            if (inicio.isAfter(regra.dataInicio) && inicio.isBefore(regra.dataFim)
                    || fim.isAfter(regra.dataInicio) && fim.isBefore(regra.dataFim) || regra.dataInicio.equals(inicio)
                    || regra.dataFim.equals(fim)) {
                return false;
            }
            // agora para fazer as mesmas verificações na ordem inversa
            if (inicio.isBefore(regra.dataInicio) && fim.isAfter(regra.dataFim)
                    || inicio.isAfter(regra.dataInicio) && fim.isBefore(regra.dataFim)) {
                return false;
            }
        }
        return true;
    }

    public Regras(
            String csvLine) throws excecao {
        String[] campos = csvLine.split(";");
        try {
            if (campos.length == 9) {

                DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.getDefault());
                symbols.setDecimalSeparator(',');
                DecimalFormat decimalFormat = new DecimalFormat("#.##", symbols);
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");

                // this.dataInicio = new Date();

                this.dataInicio = LocalDate.parse(campos[0].trim(), formatter);
                this.dataFim = LocalDate.parse(campos[1].trim(), formatter);

                if (!verificaDataValida(dataInicio, dataFim)) {
                    throw new excecao("Múltiplas regras de pontuação para o mesmo período: "
                            + formatter.format(dataInicio) + " : "
                            + formatter.format(dataFim) + ".");
                }

                String[] qualis1 = campos[2].split("-");
                this.qualis1 = new ArrayList<String>();
                for (String quali : qualis1) {
                    if (!Arrays.asList(Qualificacoes.qualisValidos).contains(quali)) {
                        throw new excecao(
                                "Qualis desconhecido para regras de " + campos[0] + ": " + quali + ".");
                    }
                    this.qualis1.add(quali);
                }
                String[] pontos = campos[3].split("-");
                this.pontos = new ArrayList<String>();
                for (String ponto : pontos) {
                    this.pontos.add(ponto);
                }
                this.qtdeAnosPontos = Integer.parseInt(campos[4].trim());

                String[] qualis2 = campos[5].split("-");
                this.qualis2 = new ArrayList<String>();
                for (String quali : qualis2) {
                    if (!Arrays.asList(Qualificacoes.qualisValidos).contains(quali)) {
                        throw new excecao(
                                "Qualis desconhecido para regras de " + campos[0].trim() + ": " + quali + ".");
                    }
                    this.qualis2.add(quali);
                }

                String[] quantidadesMinimas = campos[6].split("-");
                this.quantidadesMinimas = new ArrayList<Integer>();
                for (String quantidade : quantidadesMinimas) {
                    int quant = Integer.parseInt(quantidade);
                    this.quantidadesMinimas.add(quant);
                }

                this.qtdeAnosArtigo = Integer.parseInt(campos[7]);
                try {
                    this.pontuacaoMin = decimalFormat.parse(campos[8].trim()).floatValue();
                } catch (Exception e) {
                    throw new excecao("Erro de formatacao");
                }
            }
        } catch (java.lang.NumberFormatException e) {
            throw new excecao("Erro de formatacao");
        }
        datasCadastradas.add(this);

    }

    public Float[] constroiVetorPontos() {

        DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.getDefault());
        symbols.setDecimalSeparator(',');
        DecimalFormat decimalFormat = new DecimalFormat("#.##", symbols);

        String todosQualis[] = { "A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "B5", "C" }; // vai usar i para iterar;
        Float vetorPontos[] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f }; // vai usar i para iterar;
        ArrayList<String> limitesPontos = this.getQualis1(); // o valor do index vai alterar quando equals for
                                                             // verdadeiro;
        ArrayList<String> pontos = this.getPontos(); // o valor do index vai alterar quando equals for verdadeiro;
                                                     // possuem mesmo tamanho;
        int contAux = 0;
        Float pontuacaoAtual = 0.0f;

        for (int i = 0; i < vetorPontos.length; i++) {
            if (limitesPontos.get(contAux).equals(todosQualis[i])) { // verifica quando se atinge um dos limites para a
                                                                     // mudança de pontuação;

                try {
                    pontuacaoAtual = decimalFormat.parse(pontos.get(contAux)).floatValue(); // muda a pontuação a ser
                                                                                            // atribuída de acordo
                } catch (ParseException e) {
                    e.printStackTrace();
                }

                contAux++; // com os limites;
                if (contAux == limitesPontos.size()) {
                    contAux--; // gambiarra para não dar erro de index out of bounds;
                }
                // System.out.println(pontuacaoAtual + " " + contAux);
            }
            vetorPontos[i] = pontuacaoAtual; // armazena a pontuação no vetor;
        }
        return vetorPontos;
    }

    public static Regras getRegraAtual(ArrayList<Regras> regras, int ano) {
        for (Regras regra : regras) {
            LocalDate dataVerificacao = LocalDate.of(ano, 01, 01);
            if ((dataVerificacao.isAfter(regra.dataInicio) && dataVerificacao.isBefore(regra.dataFim))
                    || dataVerificacao.equals(regra.dataInicio) || dataVerificacao.equals(regra.dataFim)) {
                return regra;
            }
        }

        return null;
    }

    @Override
    public String toString() {
        return dataInicio + ";" + dataFim + ";" + qualis1 + ";" + pontos + ";" + qtdeAnosPontos + ";" + qualis2 + ";"
                + quantidadesMinimas + ";" + qtdeAnosArtigo + ";" + pontuacaoMin;
    }

    public LocalDate getDataInicio() {
        return dataInicio;
    }

    public void setDataInicio(LocalDate dataInicio) {
        this.dataInicio = dataInicio;
    }

    public LocalDate getDataFim() {
        return dataFim;
    }

    public void setDataFim(LocalDate dataFim) {
        this.dataFim = dataFim;
    }

    public ArrayList<String> getQualis1() {
        return qualis1;
    }

    public void setQualis1(ArrayList<String> qualis1) {
        this.qualis1 = qualis1;
    }

    public ArrayList<String> getPontos() {
        return pontos;
    }

    public void setPontos(ArrayList<String> pontos) {
        this.pontos = pontos;
    }

    public Integer getQtdeAnosPontos() {
        return qtdeAnosPontos;
    }

    public void setQtdeAnosPontos(Integer qtdeAnosPontos) {
        this.qtdeAnosPontos = qtdeAnosPontos;
    }

    public ArrayList<String> getQualis2() {
        return qualis2;
    }

    public void setQualis2(ArrayList<String> qualis2) {
        this.qualis2 = qualis2;
    }

    public ArrayList<Integer> getQuantidadesMinimas() {
        return quantidadesMinimas;
    }

    public void setQuantidadesMinimas(ArrayList<Integer> quantidadesMinimas) {
        this.quantidadesMinimas = quantidadesMinimas;
    }

    public Integer getQtdeAnosArtigo() {
        return qtdeAnosArtigo;
    }

    public void setQtdeAnosArtigo(Integer qtdeAnosArtigo) {
        this.qtdeAnosArtigo = qtdeAnosArtigo;
    }

    public Float getPontuacaoMin() {
        return pontuacaoMin;
    }

    public void setPontuacaoMin(Float pontuacaoMin) {
        this.pontuacaoMin = pontuacaoMin;
    }

}
