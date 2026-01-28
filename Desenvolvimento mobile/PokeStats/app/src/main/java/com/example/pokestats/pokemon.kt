package com.example.pokestats

import java.io.Serializable

data class Pokemon(
    val id: Int,
    val name: String,
    val imageUrl: String,
    val hp: Int,
    val attack: Int,
    val defense: Int,
    val specialAttack: Int,
    val specialDefense: Int,
    val speed: Int
) : Serializable
