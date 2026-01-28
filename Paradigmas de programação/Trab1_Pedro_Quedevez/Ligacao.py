import Ponto

class Ligacao:
    def __init__(self, ponto_origem, ponto_destino, distancia):

        self.ponto_origem = ponto_origem
        self.ponto_destino = ponto_destino
        self.distancia = distancia

    def get_ponto_origem(self):
        return self.ponto_origem
    
    def get_ponto_destino(self):
        return self.ponto_destino
    
    def get_distancia(self):
        return self.distancia

    def __str__(self):
        return f"origem={self.ponto_origem.identificador}, destino={self.ponto_destino.identificador}, distancia={self.distancia})"