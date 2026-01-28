import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;

public class Ocorrencia {
    private Long codigo;
    private String evento;
    private LocalDate dataInicio;
    private LocalDate dataFim;

    public Ocorrencia(String csvline) throws excecao {
        String[] campos = csvline.split(";");
        try {
            if (campos.length == 4) {
                if (!Docente.codigosCadastrados.contains(Long.parseLong(campos[0]))) {
                    throw new excecao(
                            "Código de docente não definido usado na ocorrência: " + campos[0] + ":" + campos[1]
                                    + ".");
                }
                this.codigo = Long.parseLong(campos[0].trim());
                this.evento = campos[1].trim();
                DateTimeFormatter formatter = DateTimeFormatter.ofPattern("dd/MM/yyyy");
                this.dataInicio = LocalDate.parse(campos[2].trim(), formatter);
                this.dataFim = LocalDate.parse(campos[3].trim(), formatter);
            }
        } catch (java.lang.NumberFormatException e) {
            throw new excecao("Erro de formatacao");
        }
    }

    // auxilia na verificação de eventos de recadastramento;
    public static String EventoRecadastramento(ArrayList<Ocorrencia> ocorrencias, int ano) {
        for (Ocorrencia ocorrencia : ocorrencias) {
            String evento = ocorrencia.getEvento().trim();
            evento = evento.replaceAll(" ", "");

            if (evento.equals("Coordenador")) {
                return "Coordenador";
            } else if (evento.equals("LicençaMaternidade")) {
                if (ocorrencia.getDataFim().getYear() == (ano - 1)
                        || (ocorrencia.getDataInicio().getYear() == ano
                                && ocorrencia.getDataInicio().getDayOfMonth() == 1
                                && ocorrencia.getDataInicio().getMonthValue() == 1)) {
                    return "Licença Maternidade";
                }
            } else if (evento.equals("BolsistaCNPq")) {
                LocalDate dataComparar = LocalDate.of(ano, 1, 1);
                if ((ocorrencia.getDataInicio().isBefore(dataComparar) && ocorrencia.getDataFim().isAfter(dataComparar))
                        || (ocorrencia.getDataInicio().getYear() == ano
                                && ocorrencia.getDataInicio().getDayOfMonth() == 1
                                && ocorrencia.getDataInicio().getMonthValue() == 1)
                        || (ocorrencia.getDataFim().getYear() == ano
                                && ocorrencia.getDataFim().getDayOfMonth() == 1
                                && ocorrencia.getDataFim().getMonthValue() == 1))
                    return "Bolsista CNPq";
            }
        }
        return "Nao";
    }

    @Override
    public String toString() {
        return codigo + ";" + evento + ";" + dataInicio + ";" + dataFim;
    }

    public Long getCodigo() {
        return codigo;
    }

    public void setCodigo(Long codigo) {
        this.codigo = codigo;
    }

    public String getEvento() {
        return evento;
    }

    public void setEvento(String evento) {
        this.evento = evento;
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

}
