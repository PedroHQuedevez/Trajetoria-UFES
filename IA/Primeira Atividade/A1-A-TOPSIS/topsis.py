import numpy as np

def normalize_matrix(matrix):
    norm = np.linalg.norm(matrix, axis=0)
    return matrix / norm

def apply_weights(matrix, weights):
    return matrix * weights


# pelo o que entendi, a ideia é pegar o maior e o menor valor de cada coluna
# para criar a solução ideal para critério de custo e de benefício.
def ideal_solution(matrix,criteria):
    A_plus = []
    A_minus = []

    for j in range(matrix.shape[1]): #shape[1] número de colunas
        if criteria == 'C':
            A_plus.append(np.min(matrix[:,j]))  #esse slice pega todos os valores da coluna j
            A_minus.append(np.max(matrix[:,j]))
        else:
            A_plus.append(np.max(matrix[:,j]))
            A_minus.append(np.min(matrix[:,j]))

    return A_plus, A_minus


# pelo o que entendi², devemos pegar cada linha e calcular a distância dela para 
# a solução ideal, ou seja, para cada linha será calculada a distância de cada
# critério(coluna) para o ideal que pode ser o máximo ou o mínimo daquela coluna. 

def dist_euclidean(matrix, A_plus, A_minus):
     #broadcasting para calcular cada valor da linha pelo ideal da coluna
    d_plus = np.sqrt(np.sum((matrix - A_plus) ** 2, axis=1))
    d_minus = np.sqrt(np.sum((matrix - A_minus) ** 2 , axis=1))

    return d_plus, d_minus

# o resultado aqui vai ter o tamanho do número de linhas do csv (matriz)


# sendo os d_plus e d_minus dois vetores de mesmo tamanho idealmente.
def final_ranking(d_plus, d_minus):
    return d_minus / (d_plus + d_minus)


def topsis(matrix, weight, criteria, do_normalize=True):
    if do_normalize:
        matrix_used = normalize_matrix(matrix)
    else:
        matrix_used = matrix

    weighted_matrix = apply_weights(matrix_used, weight)
    A_plus, A_minus = ideal_solution(weighted_matrix, criteria)
    d_plus, d_minus = dist_euclidean(weighted_matrix, A_plus, A_minus)
    return final_ranking(d_plus, d_minus)