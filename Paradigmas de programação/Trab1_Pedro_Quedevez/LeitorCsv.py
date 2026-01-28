import csv, sys, Ponto
def ler_csv(nome_arquivo):
    
    try:
        with open(nome_arquivo, mode='r', encoding='utf-8') as arquivo:
            leitor = csv.reader(arquivo)
            pontos = []
            for idx, linha in enumerate(leitor):
                coordenadas = [float(x) for x in linha]
                ponto = Ponto.Ponto(coordenadas)
                ponto.identificador = idx +1  # Atribui o contador como identificador
                pontos.append(ponto)
        return pontos
    except FileNotFoundError:
        print(f"Erro: O arquivo '{nome_arquivo}' não foi encontrado.", file=sys.stderr)
        return []
    except Exception as e:
        print(f"Erro ao ler o arquivo: {e}", file=sys.stderr)
        return []