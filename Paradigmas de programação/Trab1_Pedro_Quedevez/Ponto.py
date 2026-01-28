
class Ponto:
    def __init__(self, coordenadas):
        self.coordenadas = list(coordenadas)
        self.identificador = None
    
    def get_identificador(self):
        return self.identificador

    def __str__(self):
        return f" {self.identificador}"
        #return f"ID: {self.identificador} - Coordenadas: {self.coordenadas}"
    

#fora da classe:

def distancia_euclidiana(ponto1: Ponto, ponto2: Ponto):
    if len(ponto1.coordenadas) != len(ponto2.coordenadas):
        raise ValueError("Os pontos não possuem o mesmo número de dimensões.")
    
    soma = 0
    for i in range(len(ponto1.coordenadas)):
        soma += (ponto1.coordenadas[i] - ponto2.coordenadas[i]) ** 2
    return soma ** 0.5
    
