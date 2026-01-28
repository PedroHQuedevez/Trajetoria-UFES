package com.example.pokestats.ui

import com.example.pokestats.R
import com.example.pokestats.Pokemon
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import com.example.pokestats.databinding.PokeDetailFragmentBinding
import com.example.pokestats.viewmodel.PokemonViewModel
import com.google.android.material.snackbar.Snackbar
import com.squareup.picasso.Picasso
import java.util.Locale

class PokemonDetailFragment : Fragment() {

    private var _binding: PokeDetailFragmentBinding? = null
    private val binding get() = _binding!!

    private lateinit var viewModel: PokemonViewModel
    private var currentPokemon: Pokemon? = null

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = PokeDetailFragmentBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        try {
            Log.d("PokemonDetailFragment", "onViewCreated started")

            viewModel = ViewModelProvider(requireActivity())[PokemonViewModel::class.java]
            Log.d("PokemonDetailFragment", "ViewModel initialized")

            // Obter Pokémon dos argumentos
            @Suppress("DEPRECATION")
            val pokemon = arguments?.getSerializable("pokemon") as? Pokemon
            Log.d("PokemonDetailFragment", "Pokemon retrieved: $pokemon")

            if (pokemon != null) {
                currentPokemon = pokemon
                Log.d("PokemonDetailFragment", "Calling mostrarPokemon")
                mostrarPokemon(pokemon)
                Log.d("PokemonDetailFragment", "mostrarPokemon completed")

                viewModel.checkIfFavorite(pokemon.id)
                Log.d("PokemonDetailFragment", "checkIfFavorite called")
            } else {
                Log.e("PokemonDetailFragment", "Pokemon is null!")
            }

            Log.d("PokemonDetailFragment", "Setting up observers")
            setupObservers()

            Log.d("PokemonDetailFragment", "Setting up listeners")
            setupListeners()

            Log.d("PokemonDetailFragment", "onViewCreated completed successfully")
        } catch (e: Exception) {
            Log.e("PokemonDetailFragment", "Error in onViewCreated", e)
            Toast.makeText(requireContext(), "Erro ao carregar detalhes: ${e.message}", Toast.LENGTH_LONG).show()
        }
    }

    private fun setupObservers() {
        viewModel.isFavorite.observe(viewLifecycleOwner) { isFavorite ->
            updateFavoriteButton(isFavorite)
        }
    }

    private fun setupListeners() {
        binding.backButton.setOnClickListener {
            Log.d("PokemonDetailFragment", "Back button clicked")
            parentFragmentManager.popBackStack()
        }

        binding.favoriteButton.setOnClickListener {
            currentPokemon?.let { pokemon ->
                val wasFavorite = viewModel.isFavorite.value == true

                if (wasFavorite) {
                    // Remover dos favoritos
                    viewModel.removeFavorite(pokemon.id)
                    showSnackbar(getString(R.string.removed_from_favorites, pokemon.name.replaceFirstChar {
                        if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString()
                    }))
                } else {
                    // Adicionar aos favoritos
                    viewModel.addFavorite(pokemon)
                    showSnackbar(getString(R.string.added_to_favorites, pokemon.name.replaceFirstChar {
                        if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString()
                    }))
                }
            }
        }
    }

    private fun showSnackbar(message: String) {
        Snackbar.make(binding.root, message, Snackbar.LENGTH_SHORT).show()
    }

    private fun updateFavoriteButton(isFavorite: Boolean) {
        if (isFavorite) {
            binding.favoriteButton.setImageResource(R.drawable.filled_heart)
        } else {
            binding.favoriteButton.setImageResource(R.drawable.empty_heart)
        }
    }

    private fun mostrarPokemon(pokemon: Pokemon) {
        try {
            Log.d("PokemonDetailFragment", "mostrarPokemon: Loading image from ${pokemon.imageUrl}")

            // Carregar imagem (usando Picasso)
            Picasso.get()
                .load(pokemon.imageUrl)
                .placeholder(R.drawable.pokebola)
                .error(R.drawable.pokebola)
                .into(binding.pokemonImage)

            Log.d("PokemonDetailFragment", "mostrarPokemon: Image loaded")

            // Mostrar nome e ID
            binding.pokemonName.text = pokemon.name.replaceFirstChar {
                if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString()
            }
            Log.d("PokemonDetailFragment", "mostrarPokemon: Name set")

            binding.pokemonId.text = getString(R.string.pokemon_id_format, pokemon.id)
            Log.d("PokemonDetailFragment", "mostrarPokemon: ID set")

            // Mostrar estatísticas
            binding.hpValue.text = pokemon.hp.toString()
            binding.attackValue.text = pokemon.attack.toString()
            binding.defenseValue.text = pokemon.defense.toString()
            binding.specialAttackValue.text = pokemon.specialAttack.toString()
            binding.specialDefenseValue.text = pokemon.specialDefense.toString()
            binding.speedValue.text = pokemon.speed.toString()

            Log.d("PokemonDetailFragment", "mostrarPokemon: All stats set")
        } catch (e: Exception) {
            Log.e("PokemonDetailFragment", "Error in mostrarPokemon", e)
            throw e
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}