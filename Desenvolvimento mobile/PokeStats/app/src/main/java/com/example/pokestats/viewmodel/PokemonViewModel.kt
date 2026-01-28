package com.example.pokestats.viewmodel

import android.app.Application
import android.util.Log
import androidx.lifecycle.AndroidViewModel
import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.viewModelScope
import com.example.pokestats.Pokemon
import com.example.pokestats.data.api.PokeApiService
import com.example.pokestats.data.database.PokemonDatabase
import com.example.pokestats.data.database.PokemonEntity
import com.example.pokestats.data.repository.PokemonRepository
import kotlinx.coroutines.launch

class PokemonViewModel(application: Application) : AndroidViewModel(application) {

    private val repository: PokemonRepository

    val allFavorites: LiveData<List<PokemonEntity>>

    private val _searchResult = MutableLiveData<Pokemon?>()
    val searchResult: LiveData<Pokemon?> = _searchResult

    private val _errorMessage = MutableLiveData<String?>()
    val errorMessage: LiveData<String?> = _errorMessage

    private val _isLoading = MutableLiveData<Boolean>()
    val isLoading: LiveData<Boolean> = _isLoading

    private val _isFavorite = MutableLiveData<Boolean>()
    val isFavorite: LiveData<Boolean> = _isFavorite

    private val _pokemonList = MutableLiveData<List<Pokemon>>(emptyList())
    val pokemonList: LiveData<List<Pokemon>> = _pokemonList

    private val _isLoadingList = MutableLiveData<Boolean>()
    val isLoadingList: LiveData<Boolean> = _isLoadingList

    private var currentOffset = 0
    private val pageSize = 20
    private var isLastPage = false

    init {
        val pokemonDao = PokemonDatabase.getDatabase(application).pokemonDao()
        val apiService = PokeApiService.create()
        repository = PokemonRepository(pokemonDao, apiService)
        allFavorites = repository.allFavorites
    }

    fun searchPokemon(name: String) {
        Log.d("PokemonViewModel", "searchPokemon called with: $name")

        if (name.isBlank()) {
            Log.d("PokemonViewModel", "Name is blank")
            _errorMessage.value = "Digite um nome"
            return
        }

        _isLoading.value = true
        Log.d("PokemonViewModel", "Starting search...")

        viewModelScope.launch {
            try {
                Log.d("PokemonViewModel", "Calling repository.searchPokemon")
                val pokemon = repository.searchPokemon(name)
                Log.d("PokemonViewModel", "Pokemon found: ${pokemon.name}")

                _searchResult.value = pokemon
                checkIfFavorite(pokemon.id)
                _errorMessage.value = null
            } catch (e: Exception) {
                Log.e("PokemonViewModel", "Error searching pokemon", e)
                e.printStackTrace()
                _errorMessage.value = "Pokémon não encontrado: ${e.localizedMessage ?: e.message}"
                _searchResult.value = null
            } finally {
                _isLoading.value = false
                Log.d("PokemonViewModel", "Search completed")
            }
        }
    }

    fun addFavorite(pokemon: Pokemon) {
        viewModelScope.launch {
            repository.addFavorite(pokemon)
            _isFavorite.value = true
        }
    }

    fun removeFavorite(pokemonId: Int) {
        viewModelScope.launch {
            repository.removeFavorite(pokemonId)
            _isFavorite.value = false
        }
    }

    fun checkIfFavorite(pokemonId: Int) {
        viewModelScope.launch {
            _isFavorite.value = repository.isFavorite(pokemonId)
        }
    }

    fun clearError() {
        _errorMessage.value = null
    }

    fun clearSearchResult() {
        _searchResult.value = null
    }

    fun loadPokemonList() {
        Log.d("PokemonViewModel", "loadPokemonList called - resetting list")
        currentOffset = 0
        isLastPage = false
        loadPokemonPage()
    }

    fun loadMorePokemons() {
        Log.d("PokemonViewModel", "loadMorePokemons called, current offset: $currentOffset")
        if (isLastPage || _isLoadingList.value == true) {
            Log.d("PokemonViewModel", "Already loading or last page reached, skipping")
            return
        }
        currentOffset += pageSize
        loadPokemonPage()
    }

    private fun loadPokemonPage() {
        if (_isLoadingList.value == true) {
            Log.d("PokemonViewModel", "Already loading, skipping")
            return
        }

        _isLoadingList.value = true
        Log.d("PokemonViewModel", "Loading page at offset: $currentOffset")

        viewModelScope.launch {
            try {
                val pokemons = repository.getPokemonList(currentOffset, pageSize)
                Log.d("PokemonViewModel", "Loaded ${pokemons.size} pokemons")

                if (pokemons.size < pageSize) {
                    isLastPage = true
                    Log.d("PokemonViewModel", "Last page reached")
                }

                // CORREÇÃO: Sempre substituir a lista (não acumular) - sempre 20 na memória
                _pokemonList.value = pokemons

                _errorMessage.value = null
            } catch (e: Exception) {
                Log.e("PokemonViewModel", "Error loading pokemon list", e)
                _errorMessage.value = "Erro ao carregar Pokémons: ${e.localizedMessage ?: e.message}"
            } finally {
                _isLoadingList.value = false
            }
        }
    }
}

