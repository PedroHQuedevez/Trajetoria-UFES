import java.util.Arrays;

public class Qualificacoes {
    private int ano;
    private String siglaVeiculo;
    private String qualis;

    // para realizar a verificação de Qualis válido;
    public static String[] qualisValidos = { "A1", "A2", "A3", "A4", "B1", "B2", "B3", "B4", "B5", "C" };

    public Qualificacoes(String csvline) throws excecao {
        String[] campos = csvline.split(";");
        try {
            if (campos.length == 3) {
                this.ano = Integer.parseInt(campos[0]);
                if (!Veiculo.siglasCadastradas.contains(campos[1].trim())) {
                    throw new excecao(
                            "Sigla de veículo não definida usada na qualificação do ano " + "\"" + campos[0].trim()
                                    + "\": "
                                    + campos[1].trim() + ".");
                }
                this.siglaVeiculo = campos[1];
                if (!Arrays.asList(qualisValidos).contains(campos[2].trim())) {
                    throw new excecao(
                            "Qualis desconhecido para qualificação do veículo " + campos[1].trim() + " no ano "
                                    + campos[0].trim()
                                    + ": " + campos[2].trim() + ".");
                }
                this.qualis = campos[2];
            }
        } catch (java.lang.NumberFormatException e) {
            System.out.println("Erro de formatacao");
        }
    }

    @Override
    public String toString() {
        return ano + ";" + siglaVeiculo + ";" + qualis;
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

    public String getQualis() {
        return qualis;
    }

    public void setQualis(String qualis) {
        this.qualis = qualis;
    }
}
