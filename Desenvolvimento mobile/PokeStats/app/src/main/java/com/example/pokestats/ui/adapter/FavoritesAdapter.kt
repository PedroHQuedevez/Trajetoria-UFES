package com.example.pokestats.ui.adapter

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.pokestats.R
import com.example.pokestats.data.database.PokemonEntity
import com.example.pokestats.databinding.ItemFavoritePokemonBinding
import com.squareup.picasso.Picasso
import java.util.Locale

class FavoritesAdapter(
    private val onRemoveFavorite: (PokemonEntity) -> Unit
) : ListAdapter<PokemonEntity, FavoritesAdapter.FavoriteViewHolder>(DiffCallback()) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): FavoriteViewHolder {
        val binding = ItemFavoritePokemonBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        return FavoriteViewHolder(binding, onRemoveFavorite)
    }

    override fun onBindViewHolder(holder: FavoriteViewHolder, position: Int) {
        holder.bind(getItem(position))
    }

    class FavoriteViewHolder(
        private val binding: ItemFavoritePokemonBinding,
        private val onRemoveFavorite: (PokemonEntity) -> Unit
    ) : RecyclerView.ViewHolder(binding.root) {

        fun bind(pokemon: PokemonEntity) {
            // Carregar imagem
            Picasso.get()
                .load(pokemon.imageUrl)
                .placeholder(R.drawable.pokebola)
                .error(R.drawable.pokebola)
                .into(binding.pokemonImage)

            // Mostrar nome
            binding.pokemonName.text = pokemon.name.replaceFirstChar {
                if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString()
            }

            // Configurar botão de remover favorito
            binding.favoriteButton.setOnClickListener {
                onRemoveFavorite(pokemon)
            }
        }
    }

    class DiffCallback : DiffUtil.ItemCallback<PokemonEntity>() {
        override fun areItemsTheSame(oldItem: PokemonEntity, newItem: PokemonEntity): Boolean {
            return oldItem.id == newItem.id
        }

        override fun areContentsTheSame(oldItem: PokemonEntity, newItem: PokemonEntity): Boolean {
            return oldItem == newItem
        }
    }
}

