package com.example.pokestats.ui

import com.example.pokestats.R
import com.example.pokestats.Pokemon
import com.example.pokestats.databinding.HomeFragmentBinding
import com.example.pokestats.viewmodel.PokemonViewModel
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider

class HomeFragment : Fragment() {

    private var _binding: HomeFragmentBinding? = null
    private val binding get() = _binding!!

    private lateinit var viewModel: PokemonViewModel

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = HomeFragmentBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        viewModel = ViewModelProvider(requireActivity())[PokemonViewModel::class.java]

        setupObservers()
        setupListeners()
    }

    private fun setupObservers() {
        Log.d("HomeFragment", "Setting up observers")

        viewModel.searchResult.observe(viewLifecycleOwner) { pokemon ->
            Log.d("HomeFragment", "searchResult observer triggered: $pokemon")
            pokemon?.let {
                Log.d("HomeFragment", "Opening details for: ${it.name}")
                abrirDetalhes(it)
                // Limpar o resultado para não reabrir ao voltar
                viewModel.clearSearchResult()
            }
        }

        viewModel.errorMessage.observe(viewLifecycleOwner) { error ->
            Log.d("HomeFragment", "errorMessage observer triggered: $error")
            error?.let {
                Toast.makeText(requireContext(), it, Toast.LENGTH_SHORT).show()
                viewModel.clearError()
            }
        }

        viewModel.isLoading.observe(viewLifecycleOwner) { isLoading ->
            Log.d("HomeFragment", "isLoading observer triggered: $isLoading")
            binding.btnBuscar.isEnabled = !isLoading
            binding.btnBuscar.text = if (isLoading) "Buscando..." else getString(R.string.btn_search)
        }
    }

    private fun setupListeners() {
        Log.d("HomeFragment", "Setting up listeners")
        binding.btnBuscar.setOnClickListener {
            val nome = binding.inputName.text.toString().trim()
            Log.d("HomeFragment", "Search button clicked with name: $nome")
            viewModel.searchPokemon(nome)
        }
    }

    private fun abrirDetalhes(pokemon: Pokemon) {
        Log.d("HomeFragment", "abrirDetalhes called for: ${pokemon.name}")
        try {
            val fragment = PokemonDetailFragment()
            val args = Bundle()
            args.putSerializable("pokemon", pokemon as java.io.Serializable)
            fragment.arguments = args

            parentFragmentManager.beginTransaction()
                .replace(R.id.fragmentContainer, fragment)
                .addToBackStack(null)
                .commit()
            Log.d("HomeFragment", "Fragment transaction committed")
        } catch (e: Exception) {
            Log.e("HomeFragment", "Error opening details", e)
            Toast.makeText(requireContext(), "Erro ao abrir detalhes: ${e.message}", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}