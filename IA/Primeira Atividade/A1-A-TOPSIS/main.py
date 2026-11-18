import sys
import numpy as np
from utils import *
from topsis import topsis


#função def_main para ler os 3 arquivos de entrada e armazenar
def main():
    if len(sys.argv) != 4:
        print("error: invalid number of arguments")
        sys.exit(1)

    #abrir e ler os arquivos de entrada
    avg_rows = read_csv(sys.argv[1])
    avg_names = [row[0].strip() for row in avg_rows[1:]]
    avg_mat = read_csv_to_matrix(sys.argv[1])
    params = read_csv(sys.argv[2])
    std_mat = read_csv_to_matrix(sys.argv[3])


    # ler parametros por chave para evitar dependência da ordem no CSV
    param_map = {row[0].strip(): row[1].strip() for row in params[1:] if len(row) >= 2}
    avg_weight = float(param_map["avg_peso"])
    std_weight = float(param_map["std_peso"])
    criteria_1 = param_map["avg_tipo"].upper()
    criteria_2 = param_map["std_tipo"].upper()

    # T1 e T2 usam pesos uniformes por criterio (1/n) em cada matriz.
    avg_criterion_weights = np.full(avg_mat.shape[1], 1.0 / avg_mat.shape[1])
    std_criterion_weights = np.full(std_mat.shape[1], 1.0 / std_mat.shape[1])

    topsis_1 = topsis(avg_mat, avg_criterion_weights, criteria_1, do_normalize=False)
    topsis_2 = topsis(std_mat, std_criterion_weights, criteria_2, do_normalize=False)

    # T3 agrega os dois rankings e usa avg_peso/std_peso como pesos dos criterios.
    final_matrix = np.column_stack((topsis_1, topsis_2))
    weights = np.array([avg_weight, std_weight], dtype=float)
    final_result = topsis(final_matrix, weights, 'B', do_normalize=False)

    
    algorithm_names = avg_names
    
    result_matrix = [["Algorithms", "Coef"]]
    for i, name in enumerate(algorithm_names):
        result_matrix.append([name, round(float(final_result[i]), 2)])
    
    # salvar em CSV
    write_csv("resultado.csv", result_matrix)

if __name__ == "__main__":
    main()