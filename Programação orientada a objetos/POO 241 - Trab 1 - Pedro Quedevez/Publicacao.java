import java.util.ArrayList;

public class Publicacao {

    private int ano;
    private String siglaVeiculo;
    private String titulo;
    private ArrayList<Long> listaAutores;
    private int numero;
    private int volume;
    private String localConferencia;
    private int paginaInicial;
    private int paginaFinal;
    private String quali;

    public Publicacao(String csvLine) throws excecao {
        String[] campos = csvLine.split(";");
        for (int i = 0; i < campos.length; i++) {
            if (campos[i].equals("")) {
                campos[i] = "-1"; // ta servindo pra algo ainda?
            }
        }
        try {
            if (campos.length == 9) {
                this.ano = Integer.parseInt(campos[0].trim());
                if (!Veiculo.siglasCadastradas.contains(campos[1].trim())) {
                    throw new excecao(
                            "Sigla de veículo não definida usada na publicação " + "\"" + campos[2] + "\"" + ": "
                                    + campos[1]
                                    + ".");
                }
                this.siglaVeiculo = campos[1].trim();
                this.titulo = campos[2].trim();
                this.listaAutores = new ArrayList<Long>();
                String[] autores = campos[3].split(",");
                for (String autor : autores) {
                    Long autorLong = Long.parseLong(autor.trim()); // algumas strings tem espaços no final;
                    if (!Docente.codigosCadastrados.contains(autorLong)) {
                        throw new excecao(
                                "Código de docente não definido usado na publicação " + "\"" + campos[2] + "\"" + ": "
                                        + autorLong
                                        + ".");
                    }
                    this.listaAutores.add(autorLong);
                }
                this.numero = Integer.parseInt(campos[4].trim());
                this.volume = Integer.parseInt(campos[5].trim());
                this.localConferencia = campos[6].trim();
                this.paginaInicial = Integer.parseInt(campos[7].trim());
                this.paginaFinal = Integer.parseInt(campos[8].trim());
                this.quali = "";
            }
        } catch (java.lang.NumberFormatException e) {
            throw new excecao("Erro de formatacao");
        }
    }

    @Override
    public String toString() {
        String autores = "";
        for (Long autor : listaAutores) {
            autores += autor + ",";
        }
        return ano + ";" + siglaVeiculo + ";" + titulo + ";" + autores + ";" + numero + ";" + volume + ";"
                + localConferencia + ";" + paginaInicial + ";" + paginaFinal;
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

    public String getTitulo() {
        return titulo;
    }

    public void setTitulo(String titulo) {
        this.titulo = titulo;
    }

    public ArrayList<Long> getListaAutores() {
        return listaAutores;
    }

    public void setListaAutores(ArrayList<Long> listaAutores) {
        this.listaAutores = listaAutores;
    }

    public int getNumero() {
        return numero;
    }

    public void setNumero(int numero) {
        this.numero = numero;
    }

    public int getVolume() {
        return volume;
    }

    public void setVolume(int volume) {
        this.volume = volume;
    }

    public String getLocalConferencia() {
        return localConferencia;
    }

    public void setLocalConferencia(String localConferencia) {
        this.localConferencia = localConferencia;
    }

    public int getPaginaInicial() {
        return paginaInicial;
    }

    public void setPaginaInicial(int paginaInicial) {
        this.paginaInicial = paginaInicial;
    }

    public int getPaginaFinal() {
        return paginaFinal;
    }

    public void setPaginaFinal(int paginaFinal) {
        this.paginaFinal = paginaFinal;
    }

    public String getQuali() {
        return quali;
    }

    public void setQuali(String quali) {
        this.quali = quali;
    }

}