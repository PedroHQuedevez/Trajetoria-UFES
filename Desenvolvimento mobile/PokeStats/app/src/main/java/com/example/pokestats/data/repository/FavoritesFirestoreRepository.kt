package com.example.pokestats.data.repository

import android.util.Log
import com.example.pokestats.Pokemon
import com.example.pokestats.utils.FirebaseManager
import com.google.firebase.firestore.FieldValue
import kotlinx.coroutines.tasks.await

/**
 * Repository para gerenciar favoritos no Firestore
 * Estrutura:
 * Collection: "treinador"
 * Document: userId
 * Field: "favoritos" (array de mapas com dados dos pokemons)
 */
class FavoritesFirestoreRepository {

    companion object {
        private const val TAG = "FavoritesFirestore"
        private const val COLLECTION_NAME = "treinador"
        private const val FAVORITES_FIELD = "favoritos"
    }

    private val db = FirebaseManager.db

    /**
     * Adiciona um pokemon aos favoritos do usuário
     */
    suspend fun addFavorite(pokemon: Pokemon): Result<Unit> {
        return try {
            val userId = FirebaseManager.getCurrentUserId()
            if (userId == null) {
                Log.e(TAG, "User not logged in")
                return Result.failure(Exception("Usuário não autenticado"))
            }

            Log.d(TAG, "Adding favorite: ${pokemon.name} for user: $userId")

            val treinadorRef = db.collection(COLLECTION_NAME).document(userId)

            // Verificar se o documento existe
            val document = treinadorRef.get().await()

            val pokemonMap = mapOf(
                "id" to pokemon.id,
                "name" to pokemon.name,
                "imageUrl" to pokemon.imageUrl,
                "hp" to pokemon.hp,
                "attack" to pokemon.attack,
                "defense" to pokemon.defense,
                "specialAttack" to pokemon.specialAttack,
                "specialDefense" to pokemon.specialDefense,
                "speed" to pokemon.speed
            )

            if (!document.exists()) {
                // Criar novo documento com o primeiro favorito
                Log.d(TAG, "Creating new trainer document")
                treinadorRef.set(
                    mapOf(
                        FAVORITES_FIELD to listOf(pokemonMap),
                        "email" to FirebaseManager.getCurrentUserEmail(),
                        "createdAt" to FieldValue.serverTimestamp()
                    )
                ).await()
            } else {
                // Verificar se já está nos favoritos
                val currentFavorites = document.get(FAVORITES_FIELD) as? List<*> ?: emptyList<Map<String, Any>>()
                val alreadyExists = currentFavorites.any {
                    (it as? Map<*, *>)?.get("id") == pokemon.id
                }

                if (!alreadyExists) {
                    // Adicionar ao array de favoritos
                    Log.d(TAG, "Adding to existing favorites array")
                    treinadorRef.update(
                        FAVORITES_FIELD, FieldValue.arrayUnion(pokemonMap)
                    ).await()
                } else {
                    Log.d(TAG, "Pokemon already in favorites")
                }
            }

            Log.d(TAG, "Favorite added successfully")
            Result.success(Unit)
        } catch (e: Exception) {
            Log.e(TAG, "Error adding favorite", e)
            Result.failure(e)
        }
    }

    /**
     * Remove um pokemon dos favoritos do usuário
     */
    suspend fun removeFavorite(pokemonId: Int): Result<Unit> {
        return try {
            val userId = FirebaseManager.getCurrentUserId()
            if (userId == null) {
                Log.e(TAG, "User not logged in")
                return Result.failure(Exception("Usuário não autenticado"))
            }

            Log.d(TAG, "Removing favorite: pokemonId=$pokemonId for user: $userId")

            val treinadorRef = db.collection(COLLECTION_NAME).document(userId)
            val document = treinadorRef.get().await()

            if (document.exists()) {
                val currentFavorites = document.get(FAVORITES_FIELD) as? List<*> ?: emptyList<Map<String, Any>>()

                // Encontrar o pokemon a ser removido
                val pokemonToRemove = currentFavorites.firstOrNull {
                    (it as? Map<*, *>)?.get("id") == pokemonId.toLong() ||
                    (it as? Map<*, *>)?.get("id") == pokemonId
                }

                if (pokemonToRemove != null) {
                    Log.d(TAG, "Found pokemon to remove, updating document")
                    treinadorRef.update(
                        FAVORITES_FIELD, FieldValue.arrayRemove(pokemonToRemove)
                    ).await()
                    Log.d(TAG, "Favorite removed successfully")
                } else {
                    Log.d(TAG, "Pokemon not found in favorites")
                }
            }

            Result.success(Unit)
        } catch (e: Exception) {
            Log.e(TAG, "Error removing favorite", e)
            Result.failure(e)
        }
    }

    /**
     * Verifica se um pokemon está nos favoritos
     */
    suspend fun isFavorite(pokemonId: Int): Boolean {
        return try {
            val userId = FirebaseManager.getCurrentUserId()
            if (userId == null) {
                Log.e(TAG, "User not logged in")
                return false
            }

            val document = db.collection(COLLECTION_NAME)
                .document(userId)
                .get()
                .await()

            if (document.exists()) {
                val favorites = document.get(FAVORITES_FIELD) as? List<*> ?: emptyList<Map<String, Any>>()
                val isFav = favorites.any {
                    (it as? Map<*, *>)?.get("id") == pokemonId.toLong() ||
                    (it as? Map<*, *>)?.get("id") == pokemonId
                }
                Log.d(TAG, "isFavorite for pokemonId=$pokemonId: $isFav")
                return isFav
            }

            false
        } catch (e: Exception) {
            Log.e(TAG, "Error checking if favorite", e)
            false
        }
    }

    /**
     * Obtém todos os favoritos do usuário
     */
    suspend fun getAllFavorites(): List<Pokemon> {
        return try {
            val userId = FirebaseManager.getCurrentUserId()
            if (userId == null) {
                Log.e(TAG, "User not logged in")
                return emptyList()
            }

            Log.d(TAG, "Getting all favorites for user: $userId")

            val document = db.collection(COLLECTION_NAME)
                .document(userId)
                .get()
                .await()

            if (document.exists()) {
                val favorites = document.get(FAVORITES_FIELD) as? List<*> ?: emptyList<Map<String, Any>>()

                val pokemonList = favorites.mapNotNull { item ->
                    try {
                        val map = item as? Map<*, *> ?: return@mapNotNull null
                        Pokemon(
                            id = (map["id"] as? Long)?.toInt() ?: (map["id"] as? Int) ?: 0,
                            name = map["name"] as? String ?: "",
                            imageUrl = map["imageUrl"] as? String ?: "",
                            hp = (map["hp"] as? Long)?.toInt() ?: (map["hp"] as? Int) ?: 0,
                            attack = (map["attack"] as? Long)?.toInt() ?: (map["attack"] as? Int) ?: 0,
                            defense = (map["defense"] as? Long)?.toInt() ?: (map["defense"] as? Int) ?: 0,
                            specialAttack = (map["specialAttack"] as? Long)?.toInt() ?: (map["specialAttack"] as? Int) ?: 0,
                            specialDefense = (map["specialDefense"] as? Long)?.toInt() ?: (map["specialDefense"] as? Int) ?: 0,
                            speed = (map["speed"] as? Long)?.toInt() ?: (map["speed"] as? Int) ?: 0
                        )
                    } catch (e: Exception) {
                        Log.e(TAG, "Error parsing pokemon from map", e)
                        null
                    }
                }

                Log.d(TAG, "Retrieved ${pokemonList.size} favorites")
                pokemonList
            } else {
                Log.d(TAG, "No favorites document found")
                emptyList()
            }
        } catch (e: Exception) {
            Log.e(TAG, "Error getting all favorites", e)
            emptyList()
        }
    }

    /**
     * Observa mudanças nos favoritos em tempo real
     */
    fun observeFavorites(onFavoritesChanged: (List<Pokemon>) -> Unit) {
        val userId = FirebaseManager.getCurrentUserId()
        if (userId == null) {
            Log.e(TAG, "User not logged in")
            onFavoritesChanged(emptyList())
            return
        }

        Log.d(TAG, "Setting up favorites listener for user: $userId")

        db.collection(COLLECTION_NAME)
            .document(userId)
            .addSnapshotListener { snapshot, error ->
                if (error != null) {
                    Log.e(TAG, "Error listening to favorites", error)
                    onFavoritesChanged(emptyList())
                    return@addSnapshotListener
                }

                if (snapshot != null && snapshot.exists()) {
                    val favorites = snapshot.get(FAVORITES_FIELD) as? List<*> ?: emptyList<Map<String, Any>>()

                    val pokemonList = favorites.mapNotNull { item ->
                        try {
                            val map = item as? Map<*, *> ?: return@mapNotNull null
                            Pokemon(
                                id = (map["id"] as? Long)?.toInt() ?: (map["id"] as? Int) ?: 0,
                                name = map["name"] as? String ?: "",
                                imageUrl = map["imageUrl"] as? String ?: "",
                                hp = (map["hp"] as? Long)?.toInt() ?: (map["hp"] as? Int) ?: 0,
                                attack = (map["attack"] as? Long)?.toInt() ?: (map["attack"] as? Int) ?: 0,
                                defense = (map["defense"] as? Long)?.toInt() ?: (map["defense"] as? Int) ?: 0,
                                specialAttack = (map["specialAttack"] as? Long)?.toInt() ?: (map["specialAttack"] as? Int) ?: 0,
                                specialDefense = (map["specialDefense"] as? Long)?.toInt() ?: (map["specialDefense"] as? Int) ?: 0,
                                speed = (map["speed"] as? Long)?.toInt() ?: (map["speed"] as? Int) ?: 0
                            )
                        } catch (e: Exception) {
                            Log.e(TAG, "Error parsing pokemon from map", e)
                            null
                        }
                    }

                    Log.d(TAG, "Favorites changed, new count: ${pokemonList.size}")
                    onFavoritesChanged(pokemonList)
                } else {
                    Log.d(TAG, "No favorites document exists yet")
                    onFavoritesChanged(emptyList())
                }
            }
    }
}

