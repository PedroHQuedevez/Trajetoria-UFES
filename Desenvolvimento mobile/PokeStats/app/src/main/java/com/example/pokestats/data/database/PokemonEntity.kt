package com.example.pokestats.data.database

import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "favorite_pokemon")
data class PokemonEntity(
    @PrimaryKey
    val id: Int,
    val name: String,
    val imageUrl: String,
    val hp: Int,
    val attack: Int,
    val defense: Int,
    val specialAttack: Int,
    val specialDefense: Int,
    val speed: Int
)

