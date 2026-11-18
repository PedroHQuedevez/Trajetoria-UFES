import csv
import numpy as np

#lê um arquivo csv e retorna os dados como uma lista de listas
def read_csv(file_path):
    with open(file_path, "r", newline="") as file:
        return list(csv.reader(file))



#escreve os dados passados como um csv no caminho especificado
def write_csv(file_path, data):
    with open(file_path, "w", newline="") as file:
        writer = csv.writer(file)
        writer.writerows(data)

def read_csv_to_matrix(file_path):
    rows = read_csv(file_path)
    rows = rows[1:]
    rows = [row[1:] for row in rows]

    return np.array(rows, dtype=float)