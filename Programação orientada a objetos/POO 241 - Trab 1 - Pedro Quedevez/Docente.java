import java.time.LocalDate;
import java.time.Period;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Docente {
    private Long codigo;
    private String nome;
    private LocalDate dataNascimento;
    private LocalDate dataIngresso;
    private ArrayList<Ocorrencia> ocorrencias;
    private ArrayList<Publicacao> publicacoes;

    public static ArrayList<Long> codigosCadastrados = new ArrayList<Long>();

    public Docente(String csvline) throws excecao {
        String[] campos = csvline.split(";");
        try {
            if (campos.length == 4) {
                if (codigosCadastrados.contains(Long.parseLong(campos[0].trim()))) {
                    throw new excecao("Código repetido para docente: " + campos[0] + ".");

                }
                codigosCadastrados.add(Long.parseLong(campos[0].trim()));
                this.codigo = Long.parseLong(campos[0]);
                this.nome = campos[1].trim();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
                this.dataNascimento = LocalDate.parse(campos[2].trim(), formatter);
                this.dataIngresso = LocalDate.parse(campos[3].trim(), formatter);
                this.ocorrencias = new ArrayList<Ocorrencia>();
                this.publicacoes = new ArrayList<Publicacao>();
            }
        } catch (java.lang.NumberFormatException e) {
            throw new excecao("Erro de formatacao");
        }
    }

    public int idadeDocente(int anoAtual) {

        LocalDate dataAtual = LocalDate.of(anoAtual, 1, 1);
        Period periodo = Period.between(dataNascimento, dataAtual);
        return periodo.getYears();

    }

    public int tempoIngresso(int anoAtual) {
        LocalDate dataAtual = LocalDate.of(anoAtual, 1, 1);
        Period periodo = Period.between(dataIngresso, dataAtual);
        return periodo.getYears();
    }

    public boolean possuiPubAnosAnteriores(int anoAtual, int qntAnosValidos, String qualiLimite, int qtnMinimaPub) {
        int anoLimite = anoAtual - qntAnosValidos;
        int qtdaux = qtnMinimaPub;
        ArrayList<Publicacao> publicacoes = this.getPublicacoes();
        for (Publicacao publicacao : publicacoes) {
            if (publicacao.getAno() >= anoLimite
                    && ItemListaPublicacoes.comparaQualis(publicacao.getQuali(), qualiLimite)) {
                qtdaux--;
            }
        }
        if (qtdaux <= 0) {
            return true;
        }
        return false;
    }

    @Override
    public String toString() {
        return codigo + ";" + nome + ";" + dataNascimento + ";" + dataIngresso;
    }

    public Long getCodigo() {
        return codigo;
    }

    public void setCodigo(Long codigo) {
        this.codigo = codigo;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public LocalDate getDataNascimento() {
        return dataNascimento;
    }

    public void setDataNascimento(LocalDate dataNascimento) {
        this.dataNascimento = dataNascimento;
    }

    public LocalDate getDataIngresso() {
        return dataIngresso;
    }

    public void setDataIngresso(LocalDate dataIngresso) {
        this.dataIngresso = dataIngresso;
    }

    public ArrayList<Ocorrencia> getOcorrencias() {
        return ocorrencias;
    }

    public void setOcorrencias(ArrayList<Ocorrencia> ocorrencias) {
        this.ocorrencias = ocorrencias;
    }

    public void addOcorrencia(Ocorrencia ocorrencia) {
        this.ocorrencias.add(ocorrencia);
    }

    public void addPublicacao(Publicacao publicacao) {
        this.publicacoes.add(publicacao);
    }

    public ArrayList<Publicacao> getPublicacoes() {
        return publicacoes;
    }

    public void setPublicacoes(ArrayList<Publicacao> publicacoes) {
        this.publicacoes = publicacoes;
    }
}
