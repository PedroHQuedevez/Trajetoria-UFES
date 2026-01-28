import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;

public class leitorCsv {

    public static ArrayList<Docente> lerArquivoDocentes(String nomeArquivo) throws excecao {

        ArrayList<Docente> docentes = new ArrayList<Docente>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {
                Docente docente = new Docente(linha);
                docentes.add(docente);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return docentes;
    }

    // apenas para teste
    public static void escreverDocentes(String nomeArquivo, ArrayList<Docente> docentes) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Docente docente : docentes) {
                bw.write(docente.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static ArrayList<Ocorrencia> lerArquivoOcorrencias(String nomeArquivo) throws excecao {
        ArrayList<Ocorrencia> ocorrencias = new ArrayList<Ocorrencia>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {

                Ocorrencia Ocorrencia = new Ocorrencia(linha);
                ocorrencias.add(Ocorrencia);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return ocorrencias;
    }

    // apenas para teste
    public static void escreverOcorrencias(String nomeArquivo, ArrayList<Ocorrencia> Ocorrencias) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Ocorrencia Ocorrencia : Ocorrencias) {
                bw.write(Ocorrencia.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static ArrayList<Veiculo> lerArquivoVeiculos(String nomeArquivo) throws excecao {

        ArrayList<Veiculo> Veiculos = new ArrayList<Veiculo>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {

                Veiculo Veiculo = new Veiculo(linha);
                Veiculos.add(Veiculo);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return Veiculos;
    }

    // apenas para teste
    public static void escreverVeiculos(String nomeArquivo, ArrayList<Veiculo> Veiculos) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Veiculo Veiculo : Veiculos) {
                bw.write(Veiculo.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static ArrayList<Qualificacoes> lerArquivoQualificacoes(String nomeArquivo) throws excecao {
        ArrayList<Qualificacoes> Qualificacoess = new ArrayList<Qualificacoes>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {

                Qualificacoes Qualificacoes = new Qualificacoes(linha);
                Qualificacoess.add(Qualificacoes);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return Qualificacoess;
    }

    // apenas para teste
    public static void escreverQualificacoess(String nomeArquivo, ArrayList<Qualificacoes> Qualificacoess)
            throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Qualificacoes Qualificacoes : Qualificacoess) {
                bw.write(Qualificacoes.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static ArrayList<Publicacao> lerArquivoPublicacaos(String nomeArquivo) throws excecao {
        ArrayList<Publicacao> Publicacaos = new ArrayList<Publicacao>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {

                Publicacao Publicacao = new Publicacao(linha);
                Publicacaos.add(Publicacao);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return Publicacaos;
    }

    // apenas para teste
    public static void escreverPublicacaos(String nomeArquivo, ArrayList<Publicacao> Publicacaos) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Publicacao Publicacao : Publicacaos) {
                bw.write(Publicacao.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static ArrayList<Regras> lerArquivoRegras(String nomeArquivo) throws excecao {

        ArrayList<Regras> Regras = new ArrayList<Regras>();

        try (BufferedReader br = new BufferedReader(
                new InputStreamReader(new FileInputStream(nomeArquivo), Charset.forName("UTF-8")))) {
            String linha;
            linha = br.readLine(); // pula a primeira linha
            while ((linha = br.readLine()) != null) {

                Regras Regra = new Regras(linha);
                Regras.add(Regra);
            }

        } catch (IOException e) {
            throw new excecao("Erro de I/O");
        }

        return Regras;
    }

    public static void escreverRegras(String nomeArquivo, ArrayList<Regras> Regras) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("codigo;nome;dataNascimento;dataIngresso\n");
            for (Regras Regra : Regras) {
                bw.write(Regra.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------
    // ESCRITA DOS RELATÓRIOS;
    public static void escreverListaPublicacoes(String nomeArquivo,
            ArrayList<ItemListaPublicacoes> ItemListaPublicacoess) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("Ano;Sigla Veículo;Veículo;Qualis;Fator de Impacto;Título;Docentes\n");
            for (ItemListaPublicacoes ItemListaPublicacoes : ItemListaPublicacoess) {
                bw.write(ItemListaPublicacoes.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    public static void escreverListaPublicacoesBranco(String nomeArquivo) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {

        } catch (IOException e) {
            System.out.println("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    // ------------------------------------------------------------------------------

    public static void escreverEstPub(String nomeArquivo,
            ArrayList<ItemEstPub> ItemEstPubs) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("Qualis;Qtd. Artigos;Média Artigos / Docente\n");
            for (ItemEstPub ItemEstPub : ItemEstPubs) {
                bw.write(ItemEstPub.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    public static void escreverEstPubBranco(String nomeArquivo) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {

        } catch (IOException e) {
            System.out.println("Erro ao escrever arquivo: " + e.getMessage());
        }
    }
    // ------------------------------------------------------------------------------

    public static void escreverRecredenciamentos(String nomeArquivo,
            ArrayList<Recredenciamento> Recredenciamentos) throws excecao {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {
            bw.write("Docente;Pontuação;Recredenciado?\n");
            for (Recredenciamento Recredenciamento : Recredenciamentos) {
                bw.write(Recredenciamento.toString() + "\n");
            }
        } catch (IOException e) {
            throw new excecao("Erro ao escrever arquivo: " + e.getMessage());
        }
    }

    public static void escreverRecredenciamentosBranco(String nomeArquivo) {
        try (BufferedWriter bw = new BufferedWriter(new FileWriter(nomeArquivo))) {

        } catch (IOException e) {
            System.out.println("Erro ao escrever arquivo: " + e.getMessage());
        }
    }
}