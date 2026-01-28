package com.example.pokestats.data.database

import androidx.lifecycle.LiveData
import androidx.room.*

@Dao
interface PokemonDao {

    @Query("SELECT * FROM favorite_pokemon ORDER BY name ASC")
    fun getAllFavorites(): LiveData<List<PokemonEntity>>

    @Query("SELECT * FROM favorite_pokemon WHERE id = :pokemonId")
    suspend fun getFavoriteById(pokemonId: Int): PokemonEntity?

    @Insert(onConflict = OnConflictStrategy.REPLACE)
    suspend fun insertFavorite(pokemon: PokemonEntity)

    @Delete
    suspend fun deleteFavorite(pokemon: PokemonEntity)

    @Query("DELETE FROM favorite_pokemon WHERE id = :pokemonId")
    suspend fun deleteFavoriteById(pokemonId: Int)

    @Query("SELECT EXISTS(SELECT 1 FROM favorite_pokemon WHERE id = :pokemonId)")
    suspend fun isFavorite(pokemonId: Int): Boolean
}

