"""Script para coletar dados de jogos da RAWG API e enviar para o banco de dados"""

import requests
from dotenv import load_dotenv
import os
import sys
import re

load_dotenv()
API_KEY = os.getenv('RAWG_API_KEY')
BACKEND_URL = os.getenv('BACKEND_URL', 'http://localhost:5000')
MAX_NUM_GAMES = 120


class GameIngestionClient:
    """Client for sending games to the backend API."""
    def __init__(self, backend_url: str):
        self.backend_url = backend_url
        self.games_endpoint = f"{backend_url}/games"
        
    def send_game(self, game_data: dict):
        """Send a single game to the backend API."""
        try:
            response = requests.post(self.games_endpoint, json=game_data)
            response.raise_for_status()
            return {'success': True, 'status': 'inserted', 'data': response.json()}
        except requests.exceptions.HTTPError as e:
            if response.status_code == 409:  # Conflict - game already exists
                return {'success': True, 'status': 'exists', 'message': 'Game already exists'}
            else:
                return {'success': False, 'status': 'error', 'message': str(e)}
        except requests.exceptions.RequestException as e:
            return {'success': False, 'status': 'error', 'message': str(e)}


class RawgClient:
    """Client for the RAWG Video Games Database API."""
    def __init__(self, api_key: str):
        self.base_url = 'https://api.rawg.io/api'
        self.api_key = api_key

    def format_game_data(self, game: dict, screenshots: list):
        """Format game data for better readability."""
        # Verificar se o jogo tem pontuação no Metacritic
        metacritic_score = game.get('metacritic')
        if not metacritic_score:
            return None  # Descartar jogos sem pontuação no Metacritic
        
        # Verificar se todos os gêneros são válidos
        genres = self.get_genres_names(game.get('genres', []))
        if not self.are_genres_valid(genres):
            return None  # Descartar jogos com gêneros inválidos
        
        # Clean HTML tags from description
        raw_description = game.get('description', '')
        clean_description = clean_html_tags(raw_description)
        
        formatted_game = {
                'name': game.get('name'),
                'releaseDate': game.get('released'),
                'description': clean_description,
                'backgroundImage': game.get('background_image'),
                'playtime': game.get('playtime'),
                'platforms': self.get_platforms_names(game.get('platforms', [])),
                'genres': genres,
                'publishers': self.get_publishers_names(game.get('publishers', [])),
                'metacriticScore': metacritic_score,
                'screenshots': screenshots
            }
        return formatted_game

    def get_platforms_names(self, platforms: list) -> list:
        """Extract platform names from the game data."""
        platforms_names = []
        for platform in platforms:
            name = platform.get('platform', {}).get('name')
            if name:
                platforms_names.append(name)
        return platforms_names
    
    def get_publishers_names(self, publishers: list) -> list:
        """Extract publisher names from the game data."""
        publishers_names = []
        for publisher in publishers:
            name = publisher.get('name')
            if name:
                publishers_names.append(name)
        return publishers_names
    
    def get_genres_names(self, genres: list) -> list:
        """Extract genre names from the game data."""
        genres_names = []
        for genre in genres:
            name = genre.get('name')
            if name:
                genres_names.append(name)
        return genres_names
    
    def are_genres_valid(self, genres: list) -> bool:
        """Check if all genres are valid according to the backend enum."""
        valid_genres = {
            'Action', 'Adventure', 'Indie', 'Massively Multiplayer',
            'Platformer', 'Puzzle', 'RPG', 'Racing', 'Shooter', 'Sports'
        }
        
        # Se não há gêneros, considera inválido
        if not genres:
            return False
            
        # Verifica se todos os gêneros estão na lista de válidos
        for genre in genres:
            if genre not in valid_genres:
                return False
        
        return True
    
    def get_game_details(self, game_id: int):
        """Fetch detailed information about a specific game."""
        params = {
            'key': self.api_key
        }
        
        try:
            response = requests.get(f'{self.base_url}/games/{game_id}', params=params)
            response.raise_for_status() 
            data = response.json()
            return data
        except requests.exceptions.RequestException as e:
            print(f"Erro ao buscar dados: {e}")
            return {}

    def get_games_by_platform(self, platforms: list, max_games: int = 100):
        """Fetch games from the RAWG API based on platforms, with pagination support."""
        all_games = []
        page = 1
        page_size = 40  # Tamanho fixo da página
        
        while len(all_games) < max_games:
            params = {
                'key': self.api_key,
                'platforms': ','.join(map(str, platforms)),
                'page_size': page_size,
                'page': page
            }

            try:
                response = requests.get(f'{self.base_url}/games', params=params)
                response.raise_for_status() 
                data = response.json()

                games_in_page = 0
                for game in data['results']:
                    if len(all_games) >= max_games:
                        break
                        
                    game_id = game.get('id')
                    game_screenshots = [item['image'] for item in game.get('short_screenshots', [])]
                    if game_details := self.get_game_details(game_id):
                        formatted = self.format_game_data(game_details, game_screenshots)
                        if formatted:  # Só adiciona se o jogo tem Metacritic
                            all_games.append(formatted)
                            games_in_page += 1

                print(f"Página {page}: coletados {games_in_page} jogos (total: {len(all_games)}/{max_games})")

                # Para de paginar se não há mais resultados ou atingiu o limite
                if not data.get('next') or len(all_games) >= max_games:
                    break
                
                page += 1

            except requests.exceptions.RequestException as e:
                print(f"Erro ao buscar dados na página {page}: {e}")
                break

        return all_games

        
    def get_platforms_ids(self):
        """Fetch all platform IDs from the RAWG API."""
        params = {
            'key': self.api_key
        }
        
        try:
            response = requests.get(f'{self.base_url}/platforms', params=params)
            response.raise_for_status() 
            data = response.json()
            return {platform['name']: platform['id'] for platform in data['results']}
        except requests.exceptions.RequestException as e:
            print(f"Erro ao buscar dados: {e}")
            return {}


def collect_and_ingest_games(api: RawgClient, ingestion_client: GameIngestionClient, max_games: int = 100):
    """Collect games from RAWG API and send them directly to the backend."""
    platforms = api.get_platforms_ids()
    platforms_ids = [platform_id for _, platform_id in platforms.items()]
    
    print(f"Iniciando a coleta dos jogos...")
    games = api.get_games_by_platform(platforms_ids, max_games=max_games)
    
    if not games:
        print("Nenhum jogo encontrado ou ocorreu um erro durante a coleta.")
        return
    
    print(f"Coletados {len(games)} jogos da API RAWG")
    print(f"Iniciando inserção no banco de dados...")
    
    stats = {
        'collected': len(games),
        'inserted': 0,
        'updated': 0,
        'exists': 0,
        'errors': 0
    }
    
    for i, game in enumerate(games, 1):
        result = ingestion_client.send_game(game)
        
        if result['success']:
            if result['status'] == 'inserted':
                stats['inserted'] += 1
                print(f"[{i}/{len(games)}] Inserido: {game['name']}")
            elif result['status'] == 'exists':
                stats['exists'] += 1
                print(f"[{i}/{len(games)}] Já existe: {game['name']}")
        else:
            stats['errors'] += 1
            print(f"[{i}/{len(games)}] Erro com {game['name']}: {result['message']}")
    
    print(f"Jogos coletados: {stats['collected']}")
    print(f"Jogos inseridos: {stats['inserted']}")
    print(f"Jogos já existentes: {stats['exists']}")
    print(f"Erros: {stats['errors']}")


def clean_html_tags(text):
    """Remove HTML tags from text"""
    if not text:
        return ""
    
    # Remove HTML tags
    clean_text = re.sub(r'<[^>]+>', '', text)
    
    # Replace HTML entities
    html_entities = {
        '&amp;': '&',
        '&lt;': '<',
        '&gt;': '>',
        '&quot;': '"',
        '&apos;': "'",
        '&nbsp;': ' ',
        '&#39;': "'",
        '&#x27;': "'",
        '&#x2F;': '/',
        '&#x5C;': '\\',
        '&#x3D;': '='
    }
    
    for entity, char in html_entities.items():
        clean_text = clean_text.replace(entity, char)
    
    # Remove extra whitespace
    clean_text = ' '.join(clean_text.split())
    
    return clean_text
    
    
if __name__ == "__main__":
    if not API_KEY:
        print("RAWG_API_KEY não encontrada nas variáveis de ambiente")
        print("Por favor, configure RAWG_API_KEY no seu arquivo .env")
        sys.exit(1)
    
    rawg_api = RawgClient(API_KEY)
    ingestion_client = GameIngestionClient(BACKEND_URL)
    
    try:
        response = requests.get(f"{BACKEND_URL}/games")
        if response.status_code in [200, 404]:  # 404 is fine, means endpoint exists but no games
            print("Conexão com o backend bem-sucedida")
        else:
            print(f"Backend respondeu com status {response.status_code}")
    except requests.exceptions.RequestException as e:
        print(f"Não é possível conectar ao backend: {e}")
        sys.exit(1)
    
    # Collect and ingest games
    collect_and_ingest_games(rawg_api, ingestion_client, max_games=MAX_NUM_GAMES)
