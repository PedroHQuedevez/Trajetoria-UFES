import socket

# Configuração do cliente
HOST = '127.0.0.1'  # Endereço IP do servidor
PORT = 65432         # Porta do servidor

def start_client():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
            print("Conectado ao servidor!")
        except Exception as e:
            print(f"Erro ao conectar ao servidor: {e}")
            return
        
        while True:
            try:
                # Recebe e exibe mensagens do servidor
                data = s.recv(1024).decode()
                if not data:
                    print("Servidor desconectado.")
                    break
                print(data)
                
                if "Sua vez de jogar!" in data:
                    guess = input("")
                    s.sendall(guess.encode())
                    
                    if guess.lower() == 'sair':
                        print("Saindo do jogo...")
                        break
            except Exception as e:
                print(f"Erro na comunicação com o servidor: {e}")
                break
        
if __name__ == "__main__":
    start_client()
