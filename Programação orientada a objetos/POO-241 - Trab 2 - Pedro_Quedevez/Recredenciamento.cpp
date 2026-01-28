#include <unordered_map>
#include <iomanip>
#include "StringUtils.hpp"
#include "Regras.hpp"
#include "Recredenciamento.hpp"
#include "ItemListaPublicacoes.hpp"

using namespace cpp_util;

Recredenciamento::Recredenciamento(string nomeDocente, double pontuacao, string recrendenciado)
{
    this->nomeDocente = nomeDocente;
    this->pontuacao = pontuacao;
    this->recrendenciado = recrendenciado;
}

vector<Recredenciamento> Recredenciamento::constroiListaRecredenciamento(vector<Docente> docentes, vector<Regras> regras, int anoAtual)
{
    vector<Recredenciamento> recredenciamentos;
    vector<float> vetorPontos = constroiVetorPontos(regras, anoAtual);

    Regras regraAtual = Regras::getRegraAtual(regras, anoAtual);
    int pontuacaoMinima = regraAtual.getPontuacaoMin();

    for (Docente docente : docentes)
    {
        float pontuacao = calculaPontuacao(vetorPontos, docente, regraAtual.getQtdeAnosPontos(), anoAtual);
        string evento = verificaEventoRecredenciamento(docente, anoAtual);
        bool publicacaoMinima = verificaPubMin(regras, docente, anoAtual);

        if (evento != "")
        {
            Recredenciamento r = Recredenciamento(docente.getNome(), pontuacao, evento);
            recredenciamentos.push_back(r);
        }
        else if (pontuacao >= pontuacaoMinima && publicacaoMinima && evento == "")
        {
            Recredenciamento r = Recredenciamento(docente.getNome(), pontuacao, "Sim");
            recredenciamentos.push_back(r);
        }
        else
        {
            Recredenciamento r = Recredenciamento(docente.getNome(), pontuacao, "Não");
            recredenciamentos.push_back(r);
        }
    }

    return recredenciamentos;
}

bool Recredenciamento::verificaPubMin(vector<Regras> regras, Docente docente, int anoAtual)
{
    Regras regraAtual = Regras::getRegraAtual(regras, anoAtual);
    vector<string> qualis2 = regraAtual.getQualis2();
    vector<int> quantidadesMinimas = regraAtual.getQuantidadesMinimas();

    int quantMin = quantidadesMinimas[0];
    string qualisMin = qualis2[qualis2.size() - 1];

    vector<Publicacao> publicacoes = docente.getPublicacoes();

    for (Publicacao p : publicacoes)
    {
        Veiculo v = p.getVeiculo();
        v.getTipo();
        if ((ordemQualisMap[p.getQuali()] <= ordemQualisMap[qualisMin]) && (v.getTipo() == "P" || v.getTipo() == "p"))
        {
            quantMin--;
        }
    }

    if (quantMin > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

vector<float> Recredenciamento::constroiVetorPontos(vector<Regras> regras, int anoAtual)
{
    vector<float> vetorPontos(10, 0);

    Regras regraAtual = Regras::getRegraAtual(regras, anoAtual);
    vector<string> qualis1 = regraAtual.getQualis1();
    vector<string> pontos = regraAtual.getPontos();
    for (int i = 0; i < pontos.size(); i++)
    {
        pontos[i] = trocarVirgulaPorPonto(pontos[i]);
    }
    int qtdeAnosPontos = regraAtual.getQtdeAnosPontos();

    for (int i = 0; i < qualis1.size(); i++)
    {
        vetorPontos[ordemQualisMap[qualis1[i]]] = stof(pontos[i]); // pontos e qualis1 tem o mesmo tamanho sempre;

        for (int j = ordemQualisMap[qualis1[i]]; j < 10; j++) // preenche o vetor do ponto atual até o final com o mesmo valor;
        {
            vetorPontos[j] = stof(pontos[i]);
        }
    }

    return vetorPontos;
}

float Recredenciamento::calculaPontuacao(vector<float> &vetorPontos, Docente docente, int quantAnos, int anoAtual)
{
    float pontuacao = 0.0f;
    vector<Publicacao> publicacoes = docente.getPublicacoes();
    int limiteAno = anoAtual - quantAnos;

    for (Publicacao p : publicacoes)
    {
        if (p.getAno() >= limiteAno && p.getAno() < anoAtual)
        {
            pontuacao += vetorPontos[ordemQualisMap[p.getQuali()]];
        }
    }
    return pontuacao;
}

string Recredenciamento::verificaEventoRecredenciamento(Docente docente, int anoAtual)
{
    vector<Ocorrencia> ocorrenciasDocente = docente.getOcorrencias();
    for (Ocorrencia o : ocorrenciasDocente)
    {
        string evento = o.getEvento();
        if (trim(evento) == "Coordenador" || trim(evento) == "Licença Maternidade" || trim(evento) == "Bolsista CNPq")
        {
            return trim(evento);
        }
    }

    if (docente.idadeDocente(anoAtual) >= 60)
    {
        return "PPS";
    }

    if (docente.tempoIngresso(anoAtual) <= 2)
    {
        return "PPJ";
    }

    return "";
}

vector<Recredenciamento> Recredenciamento::ordenaListaRecredenciamento(vector<Recredenciamento> listaRecredenciamento)
{
    for (int i = 0; i < listaRecredenciamento.size(); i++)
    {
        for (int j = i + 1; j < listaRecredenciamento.size(); j++)
        {
            if (listaRecredenciamento[i].getNomeDocente() > listaRecredenciamento[j].getNomeDocente())
            {
                Recredenciamento aux = listaRecredenciamento[i];
                listaRecredenciamento[i] = listaRecredenciamento[j];
                listaRecredenciamento[j] = aux;
            }
        }
    }
    return listaRecredenciamento;
}

string Recredenciamento::getNomeDocente()
{
    return this->nomeDocente;
}

double Recredenciamento::getPontuacao()
{
    return this->pontuacao;
}

string Recredenciamento::getRecrendenciado()
{
    return this->recrendenciado;
}

void Recredenciamento::setNomeDocente(string nomeDocente)
{
    this->nomeDocente = nomeDocente;
}

void Recredenciamento::setPontuacao(double pontuacao)
{
    this->pontuacao = pontuacao;
}

void Recredenciamento::setRecrendenciado(string recrendenciado)
{
    this->recrendenciado = recrendenciado;
}

ostream &operator<<(ostream &o, Recredenciamento &r)
{
    stringstream pontuacaoAux;
    pontuacaoAux << fixed << setprecision(1) << r.getPontuacao();
    string pontuacao = trocarPontoPorVirgula(pontuacaoAux.str());

    o << r.getNomeDocente() << ";" << pontuacao << ";" << r.getRecrendenciado();
    return o;
}
