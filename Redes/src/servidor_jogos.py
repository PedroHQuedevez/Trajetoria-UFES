import random
import socket
import threading

# Configuração do servidor
HOST = '0.0.0.0'
PORT = 65432

target_number = random.randint(1, 100)
print(f"Número secreto gerado: {target_number}")

clients = {}
turns_list = []
lock = threading.Lock()
guessed_numbers = []
server_running = True

# Tempo limite para cada jogador (em segundos)
TIMEOUT = 10


# Função para enviar mensagens para um cliente específico
def send_message(client, message):
    try:
        client.sendall(message.encode())
    except:
        remove_player(client)

# Função para enviar mensagens para todos os clientes
def broadcast(message):
    for client in list(clients.values()):
        send_message(client, message)

# Função para atualizar a ordem dos turnos
def update_turn():
    global turns_list
    if turns_list:
        turns_list.append(turns_list.pop(0))
    if turns_list:
        next_player = turns_list[0]
        broadcast(f"Agora é a vez do Jogador {next_player}.\n")
        broadcast(f"Números já tentados: {', '.join(map(str, guessed_numbers))}\n")

# Função para remover um jogador
def remove_player(client):
    global turns_list, clients
    player_id = None
    for pid, c in clients.items():
        if c == client:
            player_id = pid
            break
    if player_id is not None:
        del clients[player_id]
        if player_id in turns_list:
            turns_list.remove(player_id)
        broadcast(f"O jogador {player_id} saiu do jogo.\n")
        #if turns_list:
            #update_turn()
    client.close()

# Função para desconectar todos os clientes e encerrar o servidor
def shutdown_server(server):
    global server_running
    server_running = False
    broadcast("Servidor está sendo encerrado. Todos serão desconectados.\n")
    for client in list(clients.values()):
        client.close()
    clients.clear()
    turns_list.clear()
    server.close()
    print("Servidor encerrado.")

# Função para lidar com o timeout de um jogador
def handle_client(conn, addr, player_id):
    global target_number, guessed_numbers

    clients[player_id] = conn
    turns_list.append(player_id)
    
    print(f"Nova conexão: {addr} como Jogador {player_id}")
    send_message(conn, f"Bem-vindo ao jogo, Jogador {player_id}! Adivinhe um número entre 1 e 100.\n")

    while server_running:
        if not turns_list or turns_list[0] != player_id:
            continue
        
        send_message(conn, f"Sua vez de jogar! Digite um número ou 'sair' (Tempo limite: {TIMEOUT} segundos).\n")
        
        # Set a timer to handle timeout
        timeout_event = threading.Event()
        timer = threading.Timer(TIMEOUT, timeout_event.set)
        timer.start()
        

        try:
            # Wait for the client to send a guess or for the timeout to occur
            guess = None
            conn.settimeout(TIMEOUT)  # Set a timeout on the socket
            try:
                data = conn.recv(1024).decode().strip()
                if data:
                    guess = data
            except socket.timeout:
                # Timeout occurred, no data received
                pass
            except ConnectionResetError:
                # Client disconnected abruptly
                print(f"Jogador {player_id} desconectou abruptamente.")
                break

            if timeout_event.is_set() or guess is None:
                broadcast(f"O jogador {player_id} excedeu o tempo limite. Passando a vez.\n")                
                guess = "sair"
                break

            print(f"Jogador {player_id} enviou: {guess}")
            if not guess:
                break
            
            if guess.lower() == 'sair':
                send_message(conn, "Você saiu do jogo. Até mais!\n")
                break
            
            if not guess.isdigit():
                send_message(conn, "Número inválido. Tente novamente.\n")
                continue
            
            guess = int(guess)
            guessed_numbers.append(guess)
            
            if guess < target_number:
                broadcast(f"O jogador {player_id} tentou {guess}. Muito baixo.\n")
            elif guess > target_number:
                broadcast(f"O jogador {player_id} tentou {guess}. Muito alto.\n")
            else:
                broadcast(f"Parabéns! O jogador {player_id} acertou o número {target_number}! Reiniciando...\n")
                target_number = random.randint(1, 100)
                guessed_numbers.clear()
                print(f"Novo número secreto: {target_number}")
            
            update_turn()
        except Exception as e:
            print(f"Erro ao receber dado de Jogador {player_id}: {e}")
            break
        finally:
            timer.cancel()
            try:
                if conn.fileno() != -1:  # Check if the socket is still open
                    conn.settimeout(None)  # Reset the socket timeout
            except OSError:
                # Socket is already closed, no need to reset timeout
                pass

    remove_player(conn)

# Inicialização do servidor
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()
print(f"Servidor rodando em {HOST}:{PORT}")

player_id = 0
try:
    while True:
        conn, addr = server.accept()
        thread = threading.Thread(target=handle_client, args=(conn, addr, player_id))
        thread.daemon = True  # Mark the thread as a daemon thread
        thread.start()
        player_id += 1
except KeyboardInterrupt:
    print("\nServidor recebeu sinal de interrupção. Encerrando...")
    shutdown_server(server)