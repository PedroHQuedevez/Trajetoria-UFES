import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.ParseException;
import java.util.Locale;
import java.util.ArrayList;

public class Veiculo {
    private String sigla;
    private String nome;
    private Character tipo;
    private Double fatorImpacto;
    private String issn;
    private ArrayList<Publicacao> publicacoes;

    static ArrayList<String> siglasCadastradas = new ArrayList<String>();

    public Veiculo(String csvline) throws excecao {
        String[] campos = csvline.split(";");
        DecimalFormatSymbols symbols = new DecimalFormatSymbols(Locale.getDefault());
        symbols.setDecimalSeparator(',');
        DecimalFormat decimalFormat = new DecimalFormat("#.##", symbols);
        try {
            if (campos.length == 5) {
                if (siglasCadastradas.contains(campos[0].trim())) {
                    throw new excecao("Codigo repetido para Veiculo: " + campos[0]);
                }
                siglasCadastradas.add(campos[0].trim());
                this.sigla = campos[0].trim();
                this.nome = campos[1].trim();
                if (campos[2].charAt(0) != 'C' && campos[2].charAt(0) != 'P') {
                    throw new excecao(
                            "Tipo de veículo desconhecido para veículo " + campos[0] + ": " + campos[2] + ".");
                }
                this.tipo = campos[2].charAt(0);
                try {
                    this.fatorImpacto = decimalFormat.parse(campos[3].trim()).doubleValue();
                } catch (ParseException e) {
                    e.printStackTrace();
                }
                this.issn = campos[4].trim();
                this.publicacoes = new ArrayList<Publicacao>();
            } else if (campos.length == 4) {
                if (siglasCadastradas.contains(campos[0].trim())) {
                    throw new excecao("Codigo repetido para Veiculo: " + campos[0].trim());
                }
                siglasCadastradas.add(campos[0].trim());
                this.sigla = campos[0].trim();
                this.nome = campos[1].trim();
                if (campos[2].charAt(0) != 'C' && campos[2].charAt(0) != 'P') {
                    throw new excecao(
                            "Tipo de veículo desconhecido para veículo " + campos[0].trim() + ": " + campos[2].trim()
                                    + ".");
                }
                this.tipo = campos[2].charAt(0);
                try {
                    this.fatorImpacto = decimalFormat.parse(campos[3].trim()).doubleValue();
                } catch (ParseException e) {
                    e.printStackTrace();
                }
                this.issn = "";
                this.publicacoes = new ArrayList<Publicacao>();
            }
        } catch (java.lang.NumberFormatException e) {
            System.out.println("Erro de formatacao");
        }
    }

    public static Character verificaTipoVeiculo(ArrayList<Veiculo> veiculos, String sigla) {
        for (Veiculo veiculo : veiculos) {
            if (veiculo.getSigla().trim().equals(sigla.trim())) {
                return veiculo.getTipo();
            }
        }
        return null;
    }

    @Override
    public String toString() {
        return sigla + ";" + nome + ";" + tipo + ";" + fatorImpacto + ";" + issn;
    }

    public String getSigla() {
        return sigla;
    }

    public void setSigla(String sigla) {
        this.sigla = sigla;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public Character getTipo() {
        return tipo;
    }

    public void setTipo(Character tipo) {
        this.tipo = tipo;
    }

    public Double getFatorImpacto() {
        return fatorImpacto;
    }

    public void setFatorImpacto(Double fatorImpacto) {
        this.fatorImpacto = fatorImpacto;
    }

    public String getIssn() {
        return issn;
    }

    public void setIssn(String issn) {
        this.issn = issn;
    }

    public ArrayList<Publicacao> getPublicacoes() {
        return publicacoes;
    }

    public void setPublicacoes(ArrayList<Publicacao> publicacoes) {
        this.publicacoes = publicacoes;
    }

    public void addPublicacao(Publicacao publicacao) {
        this.publicacoes.add(publicacao);
    }
}
