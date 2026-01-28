"""Scripts para gerar reviews aleatórias via API"""

import random
import requests

# Configuração
API_URL = "https://playboxbase.onrender.com/"
NUM_REVIEWS = 500
USER_IDS = [2, 3, 4, 5, 6, 7, 8]  # AJUSTE com IDs reais de usuários 

# Comentários simples
COMENTARIOS = [
    "Muito bom!", "Adorei!", "Incrível!", "Recomendo!", "Excelente!",
    "Legal!", "Divertido!", "Top!", "Show!", "Perfeito!",
    "Bom jogo!", "Gostei!", "Vale a pena!", "Fantástico!", "Impressionante!",
    "Gameplay viciante!", "Visual lindo!", "História envolvente!",
    "Trilha sonora épica!", "Controles fluidos!", "Mundo incrível!"
]


def main():
    print("Buscando jogos...")
    try:
        response = requests.get(f"{API_URL}/games", timeout=5)
        if response.status_code != 200:
            print(f"Erro ao buscar jogos: Status {response.status_code}")
            return
        
        games_data = response.json()
        games = games_data.get('games', [])
        
        if not games:
            print("Nenhum jogo encontrado!")
            print("Cadastre alguns jogos primeiro")
            return
            
        print(f"{len(games)} jogos encontrados")   
    except requests.exceptions.RequestException as e:
        print(f"Erro de conexão: {e}")
        print("Certifique-se que o servidor está rodando em", API_URL)
        return
    
    print(f"\nGerando {NUM_REVIEWS} reviews...")
    success = 0
    for i in range(NUM_REVIEWS):
        # Seleciona usuário e jogo aleatórios
        user_id = random.choice(USER_IDS)
        game = random.choice(games)
        
        # Dados da review
        review_data = {
            'userId': user_id,
            'gameId': game['id'],
            'gameplayRating': random.randint(3, 5),
            'visualRating': random.randint(4, 5),
            'audioRating': random.randint(3, 5),
            'difficultyRating': random.randint(3, 5),
            'immersionRating': random.randint(3, 5),
            'historyRating': random.randint(3, 5),
            'comment': random.choice(COMENTARIOS)
        }
        
        # Tenta criar a review
        try:
            response = requests.post(f"{API_URL}/reviews", json=review_data, timeout=5)
            if response.status_code == 201:
                success += 1
                print(f"{success}. Usuário {user_id} → {game['name']}")
            else:
                print(f"Erro {response.status_code}: Usuário {user_id} → {game['name']}") 
        except requests.exceptions.RequestException as e:
            print(f"Erro de rede: {e}")
    
    print(f"Concluído: {success}/{NUM_REVIEWS} reviews criadas!")


if __name__ == "__main__":
    main()
