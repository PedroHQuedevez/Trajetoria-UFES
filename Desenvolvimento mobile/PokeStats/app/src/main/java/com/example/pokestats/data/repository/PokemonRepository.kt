package com.example.pokestats.data.repository

import android.util.Log
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import com.example.pokestats.Pokemon
import com.example.pokestats.data.api.PokeApiService
import com.example.pokestats.data.database.PokemonDao
import com.example.pokestats.data.database.PokemonEntity
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.withContext

class PokemonRepository(
    private val pokemonDao: PokemonDao,
    private val apiService: PokeApiService
) {

    // Firestore repository para favoritos
    private val favoritesFirestoreRepository = FavoritesFirestoreRepository()

    // LiveData para favoritos - agora do Firestore
    private val _allFavorites = MutableLiveData<List<PokemonEntity>>()
    val allFavorites: LiveData<List<PokemonEntity>> = _allFavorites

    init {
        // Observar mudanças nos favoritos do Firestore em tempo real
        favoritesFirestoreRepository.observeFavorites { pokemons ->
            // Converter Pokemon para PokemonEntity para manter compatibilidade
            _allFavorites.postValue(pokemons.map { pokemon ->
                PokemonEntity(
                    id = pokemon.id,
                    name = pokemon.name,
                    imageUrl = pokemon.imageUrl,
                    hp = pokemon.hp,
                    attack = pokemon.attack,
                    defense = pokemon.defense,
                    specialAttack = pokemon.specialAttack,
                    specialDefense = pokemon.specialDefense,
                    speed = pokemon.speed
                )
            })
        }
    }

    suspend fun addFavorite(pokemon: Pokemon) {
        Log.d("PokemonRepository", "Adding favorite via Firestore: ${pokemon.name}")
        favoritesFirestoreRepository.addFavorite(pokemon)
    }

    suspend fun removeFavorite(pokemonId: Int) {
        Log.d("PokemonRepository", "Removing favorite via Firestore: $pokemonId")
        favoritesFirestoreRepository.removeFavorite(pokemonId)
    }

    suspend fun isFavorite(pokemonId: Int): Boolean {
        return favoritesFirestoreRepository.isFavorite(pokemonId)
    }

    // API calls
    suspend fun searchPokemon(name: String): Pokemon = withContext(Dispatchers.IO) {
        try {
            Log.d("PokemonRepository", "Searching for pokemon: $name")
            val response = apiService.getPokemon(name.lowercase())
            Log.d("PokemonRepository", "API response received: ${response.name}")

            val pokemon = Pokemon(
                id = response.id,
                name = response.name,
                imageUrl = response.sprites.front_default ?: "",
                hp = response.stats.find { it.stat.name == "hp" }?.base_stat ?: 0,
                attack = response.stats.find { it.stat.name == "attack" }?.base_stat ?: 0,
                defense = response.stats.find { it.stat.name == "defense" }?.base_stat ?: 0,
                specialAttack = response.stats.find { it.stat.name == "special-attack" }?.base_stat ?: 0,
                specialDefense = response.stats.find { it.stat.name == "special-defense" }?.base_stat ?: 0,
                speed = response.stats.find { it.stat.name == "speed" }?.base_stat ?: 0
            )
            Log.d("PokemonRepository", "Pokemon object created successfully")
            pokemon
        } catch (e: Exception) {
            Log.e("PokemonRepository", "Error in searchPokemon", e)
            throw e
        }
    }

    suspend fun getPokemonList(offset: Int = 0, limit: Int = 20): List<Pokemon> = withContext(Dispatchers.IO) {
        try {
            Log.d("PokemonRepository", "Fetching pokemon list: offset=$offset, limit=$limit")
            val response = apiService.getPokemonList(offset, limit)
            Log.d("PokemonRepository", "Got ${response.results.size} pokemon items")

            // Para cada item da lista, buscar os detalhes completos
            response.results.map { item ->
                try {
                    val pokemonResponse = apiService.getPokemon(item.name)
                    Pokemon(
                        id = pokemonResponse.id,
                        name = pokemonResponse.name,
                        imageUrl = pokemonResponse.sprites.front_default ?: "",
                        hp = pokemonResponse.stats.find { it.stat.name == "hp" }?.base_stat ?: 0,
                        attack = pokemonResponse.stats.find { it.stat.name == "attack" }?.base_stat ?: 0,
                        defense = pokemonResponse.stats.find { it.stat.name == "defense" }?.base_stat ?: 0,
                        specialAttack = pokemonResponse.stats.find { it.stat.name == "special-attack" }?.base_stat ?: 0,
                        specialDefense = pokemonResponse.stats.find { it.stat.name == "special-defense" }?.base_stat ?: 0,
                        speed = pokemonResponse.stats.find { it.stat.name == "speed" }?.base_stat ?: 0
                    )
                } catch (e: Exception) {
                    Log.e("PokemonRepository", "Error fetching details for ${item.name}", e)
                    null
                }
            }.filterNotNull()
        } catch (e: Exception) {
            Log.e("PokemonRepository", "Error in getPokemonList", e)
            throw e
        }
    }
}

