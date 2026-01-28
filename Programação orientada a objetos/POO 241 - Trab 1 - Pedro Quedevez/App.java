import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Locale;
import java.util.Scanner;

public class App {
    public static void main(String[] args) {

        // parcial: 16,15
        // completo: 13,14,21,28

        Locale.setDefault(Locale.forLanguageTag("pt-BR"));
        DecimalFormat decimalFormat = (DecimalFormat) NumberFormat.getNumberInstance();
        DecimalFormatSymbols symbols = decimalFormat.getDecimalFormatSymbols();
        symbols.setDecimalSeparator(',');
        decimalFormat.setDecimalFormatSymbols(symbols);

        Scanner scanner = new Scanner(System.in);
        int anoDeConsulta = scanner.nextInt();

        leitorCsv.escreverEstPubBranco(args[0] + "/saida/1-recredenciamento.csv");
        leitorCsv.escreverListaPublicacoesBranco(args[0] + "/saida/2-publicacoes.csv");
        leitorCsv.escreverRecredenciamentosBranco(args[0] + "/saida/3-estatisticas.csv");

        try {
            // C:\Users\Pedro Quedevez\Desktop\4 semestre\POO\Casos
            ArrayList<Regras> regras = leitorCsv.lerArquivoRegras(args[0] + "/regras.csv");
            ArrayList<Docente> docentes = leitorCsv.lerArquivoDocentes(args[0] + "/docentes.csv");
            ArrayList<Veiculo> veiculos = leitorCsv.lerArquivoVeiculos(args[0] + "/veiculos.csv");
            ArrayList<Qualificacoes> qualis = leitorCsv.lerArquivoQualificacoes(args[0] + "/qualis.csv");
            ArrayList<Ocorrencia> Ocorrencias = leitorCsv.lerArquivoOcorrencias(args[0] + "/ocorrencias.csv");
            ArrayList<Publicacao> publicacoes = leitorCsv.lerArquivoPublicacaos(args[0] + "/publicacoes.csv");

            utils.vincularOcorrenciasDocentes(docentes, Ocorrencias);
            utils.vinculaPublicacoesDocentes(docentes, publicacoes);
            utils.vinculaQualisPublicacao(publicacoes, qualis, anoDeConsulta);
            utils.vinculaPublicacaoVeiculo(publicacoes, veiculos);

            ArrayList<Recredenciamento> listaRecredenciamentos = Recredenciamento.listaRecredenciamento(docentes,
                    regras, veiculos,
                    anoDeConsulta);

            ArrayList<ItemListaPublicacoes> listaPublicacoes = ItemListaPublicacoes.criaListaPublicacoes(publicacoes,
                    docentes,
                    veiculos);

            ArrayList<ItemEstPub> estats = ItemEstPub.criaListEstats(publicacoes);

            leitorCsv.escreverRecredenciamentos(args[0] + "/saida/1-recredenciamento.csv", listaRecredenciamentos);

            leitorCsv.escreverListaPublicacoes(args[0] + "/saida/2-publicacoes.csv",
                    listaPublicacoes);

            leitorCsv.escreverEstPub(args[0] + "/saida/3-estatisticas.csv", estats);

        } catch (excecao e) {

            System.out.println(e.getMessage());

        }
        scanner.close();
    }

}
