import LeitorCsv
from Grupo import dividir_k_grupos
import Grupo


def main():
    nome_arquivo_entrada = input(" Forneca o nome do arquivo de entrada: ")
    path = nome_arquivo_entrada
    conjunto_pontos = LeitorCsv.ler_csv(path)
    
    path_saida = input(" Forneca o nome do arquivo de saida: ")

    numero_grupos = int(input(" Forneca o número de grupos (K): "))


    grupo = Grupo.Grupo()
    grupo.adicionar(conjunto_pontos[0])  # Adiciona o primeiro ponto ao grupo inicial
    grupo.agrupar_pontos(conjunto_pontos)   #agrupamento inicial

    grupos = dividir_k_grupos(grupo, numero_grupos)  
    
    # Ordenar grupos por tamanho (número de pontos)
    grupos.sort(key=lambda g: len(g.pontos))


    with open(path_saida, 'w') as arquivo_saida:
        for grupo in grupos:
            grupo.pontos.sort(key=lambda x: x.get_identificador())  # Ordena os pontos por identificador
            #retira o espaço no final de cada linha
            linha = str(grupo).rstrip()
            arquivo_saida.write(linha + "\n")
    
    print(f"Agrupamentos:")
    for grupo in grupos:
        print(grupo)
 


if __name__ == "__main__":
    main()