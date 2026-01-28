import socket
import threading
import time
import random

# Configuração do cliente
HOST = '127.0.0.1'  # Endereço IP do servidor
PORT = 65432        # Porta do servidor

# Função para simular um cliente
def simulate_client(client_id):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        try:
            s.connect((HOST, PORT))
            print(f"Cliente {client_id} conectado ao servidor!")
        except Exception as e:
            print(f"Cliente {client_id} erro ao conectar ao servidor: {e}")
            return
        
        while True:
            try:
                # Recebe e exibe mensagens do servidor
                data = s.recv(1024).decode()
                if not data:
                    print(f"Cliente {client_id} servidor desconectado.")
                    break
                #print(f"Cliente {client_id} recebeu: {data}")
                
                if "Sua vez de jogar!" in data:
                    guess = str(random.randint(1, 100))  # Envia um palpite aleatório
                    print(f"Cliente {client_id} enviando palpite: {guess}")
                    s.sendall(guess.encode())
                    
                    if guess.lower() == 'sair':
                        print(f"Cliente {client_id} saindo do jogo...")
                        break
                    

                    # Adiciona um atraso entre os envios de mensagens
                    time.sleep(2)  # Atraso de 2 segundos
           
            except Exception as e:
                print(f"Cliente {client_id} erro na comunicação com o servidor: {e}")
                break

# Número de clientes a serem simulados
NUM_CLIENTS = 10

# Cria e inicia threads para simular múltiplos clientes
threads = []
for i in range(NUM_CLIENTS):
    thread = threading.Thread(target=simulate_client, args=(i,))
    threads.append(thread)
    thread.start()
    time.sleep(1)  # Pequeno atraso para evitar conexões simultâneas exatas

# Aguarda todas as threads terminarem
for thread in threads:
    thread.join()