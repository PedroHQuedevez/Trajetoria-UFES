import java.util.ArrayList;

public class utils {

    // realiza as vinculações necessárias;

    public static void vincularOcorrenciasDocentes(ArrayList<Docente> docentes, ArrayList<Ocorrencia> ocorrencias) {
        for (int i = 0; i < ocorrencias.size(); i++) {
            Ocorrencia ocorrencia = ocorrencias.get(i);
            Long cod2 = ocorrencia.getCodigo();
            for (int j = 0; j < docentes.size(); j++) {
                Docente docente = docentes.get(j);
                Long cod1 = docente.getCodigo();
                if (cod1.equals(cod2)) {
                    docente.addOcorrencia(ocorrencia);
                    j = docentes.size(); // pular para a próxima iteração de i;
                } else {

                }
            }
        }
    }

    public static void vinculaPublicacoesDocentes(ArrayList<Docente> docentes, ArrayList<Publicacao> publicacoes) {
        for (int i = 0; i < publicacoes.size(); i++) {
            Publicacao publicacao = publicacoes.get(i);
            ArrayList<Long> autores = publicacao.getListaAutores();
            for (int k = 0; k < autores.size(); k++) {
                Long autor = autores.get(k);
                for (int j = 0; j < docentes.size(); j++) {
                    Docente docente = docentes.get(j);
                    Long cod1 = docente.getCodigo();
                    if (cod1.equals(autor)) {
                        docente.addPublicacao(publicacao);
                        j = docentes.size(); // pular para a psóxima iteração de k;
                    }
                }
            }
        }
    }

    public static void vinculaQualisPublicacao(ArrayList<Publicacao> publicacoes, ArrayList<Qualificacoes> qualis,
            int anoAtual) {
        for (int i = 0; i < publicacoes.size(); i++) {
            Publicacao publicacao = publicacoes.get(i);
            String sigla = publicacao.getSiglaVeiculo();
            for (int j = 0; j < qualis.size(); j++) {
                Qualificacoes q = qualis.get(j);
                String quali = q.getQualis();
                String sigla2 = q.getSiglaVeiculo();
                int ano2 = q.getAno();
                if (sigla.trim().equals(sigla2.trim()) && anoAtual > ano2) {
                    publicacao.setQuali(quali);
                }
            }
        }
    }

    public static void vinculaPublicacaoVeiculo(ArrayList<Publicacao> publicacoes, ArrayList<Veiculo> veiculos) {
        for (int i = 0; i < publicacoes.size(); i++) {
            Publicacao publicacao = publicacoes.get(i);
            String sigla = publicacao.getSiglaVeiculo();
            for (int j = 0; j < veiculos.size(); j++) {
                Veiculo veiculo = veiculos.get(j);
                String sigla2 = veiculo.getSigla();
                if (sigla.equals(sigla2)) {
                    veiculo.addPublicacao(publicacao);
                    j = veiculos.size(); // pular para a próxima iteração de i;

                }
            }
        }
    }

}
