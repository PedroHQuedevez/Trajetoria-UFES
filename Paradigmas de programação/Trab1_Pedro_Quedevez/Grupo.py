import Ponto
import Ligacao


class Grupo:
    def __init__(self):
        self.pontos = []  
        self.ligacoes = []  # lista para armazenar as ligações entre os pontos do grupo

    def __str__(self):

        return f"{','.join(str(ponto) for ponto in self.pontos)} "
    
    def adicionar(self, ponto):
        if ponto not in self.pontos:
            self.pontos.append(ponto)
        
    def agrupar_pontos(self, conjunto_pontos):
        ponto_corrente = self.pontos[0]
        while len(conjunto_pontos) > 0:
            ligacoes = []
            for ponto in conjunto_pontos: #cria lista de ligações para o ponto corrente
                distancia = Ponto.distancia_euclidiana(ponto_corrente, ponto)
                ligacoes.append(Ligacao.Ligacao(ponto_corrente, ponto, distancia))
            ligacoes.sort(key=lambda x: x.distancia)
            ligacao_mais_proxima = ligacoes.pop(0)
            ponto_corrente = ligacao_mais_proxima.ponto_destino
            self.adicionar(ponto_corrente)
            self.ligacoes.append(ligacao_mais_proxima)
            conjunto_pontos.remove(ponto_corrente)
        self.ligacoes.pop(0)  # Remove a primeira ligação, que é desnecessária    
                
   


    def divir_2_grupos(self):
        maior_ligacao = max(self.ligacoes, key=lambda x: x.distancia)
        ponto_origem = maior_ligacao.get_ponto_origem()
        ponto_destino = maior_ligacao.get_ponto_destino()
        index_ponto_origem = self.pontos.index(ponto_origem)  
        index_ponto_destino = self.pontos.index(ponto_destino) 
        index_ligacao = self.ligacoes.index(maior_ligacao)

        grupo1 = Grupo()
        grupo2 = Grupo()

        for i, ponto in enumerate(self.pontos):
            if i <= index_ponto_origem:
                grupo1.adicionar(ponto)
            elif i >= index_ponto_destino:
                grupo2.adicionar(ponto)

        for  i, Ligacao in enumerate(self.ligacoes):
            if i < index_ligacao:
                grupo1.ligacoes.append(Ligacao)
            elif i > index_ligacao:
                grupo2.ligacoes.append(Ligacao)

        return grupo1, grupo2

def dividir_k_grupos(grupo, k):
    grupos = [grupo]

    while len(grupos) < k:
        # Encontrar o grupo e a ligação de maior distância
        maior_ligacao = None
        grupo_a_dividir = None

        for g in grupos:
            if not g.ligacoes:
                continue
            ligacao_mais_longa = max(
                g.ligacoes,
                key=lambda l: (
                    l.distancia,
                    min(l.ponto_origem.identificador, l.ponto_destino.identificador),
                    max(l.ponto_origem.identificador, l.ponto_destino.identificador)
                )
            )
            if (maior_ligacao is None) or (
                (ligacao_mais_longa.distancia,
                 min(ligacao_mais_longa.ponto_origem.identificador, ligacao_mais_longa.ponto_destino.identificador),
                 max(ligacao_mais_longa.ponto_origem.identificador, ligacao_mais_longa.ponto_destino.identificador)
                ) >
                (maior_ligacao.distancia,
                 min(maior_ligacao.ponto_origem.identificador, maior_ligacao.ponto_destino.identificador),
                 max(maior_ligacao.ponto_origem.identificador, maior_ligacao.ponto_destino.identificador)
                )
            ):
                maior_ligacao = ligacao_mais_longa
                grupo_a_dividir = g

        if grupo_a_dividir is None or maior_ligacao is None:
            break  # Não há mais como dividir

        grupo1, grupo2 = grupo_a_dividir.divir_2_grupos()
        grupos.remove(grupo_a_dividir)
        grupos.append(grupo1)
        grupos.append(grupo2)

    return grupos







