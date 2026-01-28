package com.example.pokestats.data.api


import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import retrofit2.http.GET
import retrofit2.http.Path
import retrofit2.http.Query

interface PokeApiService {
    @GET("pokemon/{name}")
    suspend fun getPokemon(@Path("name") name: String): PokemonResponse

    @GET("pokemon")
    suspend fun getPokemonList(
        @Query("offset") offset: Int,
        @Query("limit") limit: Int
    ): PokemonListResponse

    companion object {
        private const val BASE_URL = "https://pokeapi.co/api/v2/"

        fun create(): PokeApiService {
            return Retrofit.Builder()
                .baseUrl(BASE_URL)
                .addConverterFactory(GsonConverterFactory.create())
                .build()
                .create(PokeApiService::class.java)
        }
    }
}

data class PokemonListResponse(
    val count: Int,
    val next: String?,
    val previous: String?,
    val results: List<PokemonListItem>
)

data class PokemonListItem(
    val name: String,
    val url: String
)

data class PokemonResponse(
    val id: Int,
    val name: String,
    val sprites: Sprites,
    val stats: List<Stat>
)

data class Sprites(
    val front_default: String?
)

data class Stat(
    val base_stat: Int,
    val stat: StatDetail
)

data class StatDetail(
    val name: String
)