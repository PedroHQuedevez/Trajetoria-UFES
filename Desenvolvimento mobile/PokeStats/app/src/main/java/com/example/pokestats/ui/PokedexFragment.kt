package com.example.pokestats.ui

import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.lifecycle.ViewModelProvider
import androidx.recyclerview.widget.GridLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.example.pokestats.R
import com.example.pokestats.databinding.PokedexFragmentBinding
import com.example.pokestats.ui.adapter.PokedexAdapter
import com.example.pokestats.viewmodel.PokemonViewModel

class PokedexFragment : Fragment() {

    private var _binding: PokedexFragmentBinding? = null
    private val binding get() = _binding!!

    private lateinit var viewModel: PokemonViewModel
    private lateinit var pokedexAdapter: PokedexAdapter
    private lateinit var gridLayoutManager: GridLayoutManager

    private var isLoading = false
    private var isFirstLoad = true

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = PokedexFragmentBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        viewModel = ViewModelProvider(requireActivity())[PokemonViewModel::class.java]

        setupRecyclerView()
        observeViewModel()
        setupFab()

        // Carregar primeira página apenas se for a primeira vez
        if (isFirstLoad) {
            viewModel.loadPokemonList()
            isFirstLoad = false
        }
    }

    private fun setupFab() {
        binding.fabLoadMore.setOnClickListener {
            // Carregar mais Pokémons ao clicar no botão +
            viewModel.loadMorePokemons()
        }
    }

    private fun setupRecyclerView() {
        gridLayoutManager = GridLayoutManager(requireContext(), 2) // 2 colunas

        pokedexAdapter = PokedexAdapter { pokemon ->
            // Abrir detalhes do Pokémon
            val fragment = PokemonDetailFragment()
            val args = Bundle()
            args.putSerializable("pokemon", pokemon as java.io.Serializable)
            fragment.arguments = args

            parentFragmentManager.beginTransaction()
                .replace(R.id.fragmentContainer, fragment)
                .addToBackStack(null)
                .commit()
        }

        binding.pokedexRecyclerView.apply {
            layoutManager = gridLayoutManager
            adapter = pokedexAdapter

            // Detectar overscroll - quando o usuário tenta puxar além do final
            addOnScrollListener(object : RecyclerView.OnScrollListener() {
                override fun onScrolled(recyclerView: RecyclerView, dx: Int, dy: Int) {
                    super.onScrolled(recyclerView, dx, dy)

                    // Verificar se não pode mais scrollar para baixo (chegou no fim)
                    // E o usuário está tentando scrollar para baixo (dy > 0)
                    if (dy > 0 && !isLoading) {
                        // canScrollVertically(1) retorna false quando NÃO pode mais scrollar para baixo
                        if (!recyclerView.canScrollVertically(1)) {
                            // Usuário está no FINAL e tentando puxar para baixo
                            // Mas para evitar trigger imediato, vamos adicionar um pequeno threshold
                            // Carrega apenas se o usuário realmente "insistir" no scroll
                            if (dy > 5) {  // Movimento significativo
                                viewModel.loadMorePokemons()
                            }
                        }
                    }
                }
            })
        }
    }

    private fun observeViewModel() {
        viewModel.pokemonList.observe(viewLifecycleOwner) { pokemons ->
            pokedexAdapter.submitList(pokemons) {
                // Callback após submeter a lista
            }
        }

        viewModel.isLoadingList.observe(viewLifecycleOwner) { loading ->
            isLoading = loading

            if (loading) {
                binding.progressBar.visibility = View.VISIBLE
                binding.fabLoadMore.visibility = View.GONE
            } else {
                binding.progressBar.visibility = View.GONE
                binding.fabLoadMore.visibility = View.VISIBLE
            }
        }
        
        viewModel.errorMessage.observe(viewLifecycleOwner) { error ->
            error?.let {
                Toast.makeText(requireContext(), it, Toast.LENGTH_SHORT).show()
            }
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}

