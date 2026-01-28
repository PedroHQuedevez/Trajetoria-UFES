package com.example.pokestats.ui

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.appcompat.app.AlertDialog
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.LinearLayoutManager
import com.example.pokestats.R
import com.example.pokestats.databinding.FavoritesFragmentBinding
import com.example.pokestats.ui.adapter.FavoritesAdapter
import com.example.pokestats.viewmodel.PokemonViewModel
import java.util.Locale

class FavoritesFragment : Fragment() {

    private var _binding: FavoritesFragmentBinding? = null
    private val binding get() = _binding!!

    private lateinit var viewModel: PokemonViewModel
    private lateinit var favoritesAdapter: FavoritesAdapter

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FavoritesFragmentBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        viewModel = ViewModelProvider(requireActivity())[PokemonViewModel::class.java]

        setupRecyclerView()
        observeFavorites()
    }

    private fun setupRecyclerView() {
        favoritesAdapter = FavoritesAdapter { pokemon ->
            // Mostrar dialog de confirmação antes de remover
            showRemoveConfirmationDialog(pokemon.id, pokemon.name)
        }

        binding.favoritesRecyclerView.apply {
            layoutManager = LinearLayoutManager(requireContext())
            adapter = favoritesAdapter
        }
    }

    private fun showRemoveConfirmationDialog(pokemonId: Int, pokemonName: String) {
        val formattedName = pokemonName.replaceFirstChar {
            if (it.isLowerCase()) it.titlecase(Locale.getDefault()) else it.toString()
        }

        AlertDialog.Builder(requireContext())
            .setTitle(getString(R.string.confirm_remove_favorite_title))
            .setMessage(getString(R.string.confirm_remove_favorite_message, formattedName))
            .setPositiveButton(getString(R.string.btn_confirm)) { dialog, _ ->
                // Confirmar remoção
                viewModel.removeFavorite(pokemonId)
                dialog.dismiss()
            }
            .setNegativeButton(getString(R.string.btn_cancel)) { dialog, _ ->
                // Cancelar
                dialog.dismiss()
            }
            .show()
    }

    private fun observeFavorites() {
        viewModel.allFavorites.observe(viewLifecycleOwner) { favorites ->
            favoritesAdapter.submitList(favorites)

            // Mostrar/ocultar mensagem de lista vazia
            if (favorites.isEmpty()) {
                binding.emptyStateLayout.visibility = View.VISIBLE
                binding.favoritesRecyclerView.visibility = View.GONE
            } else {
                binding.emptyStateLayout.visibility = View.GONE
                binding.favoritesRecyclerView.visibility = View.VISIBLE
            }
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}
