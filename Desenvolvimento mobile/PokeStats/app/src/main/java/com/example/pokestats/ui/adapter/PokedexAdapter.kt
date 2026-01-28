package com.example.pokestats.ui.adapter

import android.view.LayoutInflater
import android.view.ViewGroup
import androidx.recyclerview.widget.DiffUtil
import androidx.recyclerview.widget.ListAdapter
import androidx.recyclerview.widget.RecyclerView
import com.example.pokestats.Pokemon
import com.example.pokestats.R
import com.example.pokestats.databinding.ItemPokedexPokemonBinding
import com.squareup.picasso.Picasso
import java.util.Locale

class PokedexAdapter(
    private val onPokemonClick: (Pokemon) -> Unit
) : ListAdapter<Pokemon, PokedexAdapter.PokedexViewHolder>(DiffCallback()) {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): PokedexViewHolder {
        val binding = ItemPokedexPokemonBinding.inflate(
            LayoutInflater.from(parent.context),
            parent,
            false
        )
        return PokedexViewHolder(binding, onPokemonClick)
    }

    override fun onBindViewHolder(holder: PokedexViewHolder, position: Int) {
        holder.bind(getItem(position))
    }

    class PokedexViewHolder(
        private val binding: ItemPokedexPokemonBinding,
        private val onPokemonClick: (Pokemon) -> Unit
    ) : RecyclerView.ViewHolder(binding.root) {

        fun bind(pokemon: Pokemon) {
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

            // Mostrar ID
            binding.pokemonId.text = String.format("#%03d", pokemon.id)

            // Configurar clique
            binding.root.setOnClickListener {
                onPokemonClick(pokemon)
            }
        }
    }

    class DiffCallback : DiffUtil.ItemCallback<Pokemon>() {
        override fun areItemsTheSame(oldItem: Pokemon, newItem: Pokemon): Boolean {
            return oldItem.id == newItem.id
        }

        override fun areContentsTheSame(oldItem: Pokemon, newItem: Pokemon): Boolean {
            return oldItem == newItem
        }
    }
}

