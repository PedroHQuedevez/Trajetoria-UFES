package com.example.pokestats.ui

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.LinearLayout
import android.widget.Toast
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.fragment.app.Fragment
import com.example.pokestats.R
import com.example.pokestats.utils.FirebaseManager
import com.google.android.material.button.MaterialButton

class MainActivity : AppCompatActivity() {

    companion object {
        private const val TAG = "MainActivity"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(TAG, "onCreate started")

        try {
            setContentView(R.layout.main_view)
            Log.d(TAG, "Layout set successfully")

            // Abrir HomeFragment primeiro
            if (savedInstanceState == null) {
                Log.d(TAG, "Opening HomeFragment")
                abrirFragment(HomeFragment())
            }

            // Configurar clique nos ícones
            findViewById<LinearLayout>(R.id.icon1).setOnClickListener {
                Log.d(TAG, "Icon1 clicked - HomeFragment")
                abrirFragment(HomeFragment())
            }

            findViewById<LinearLayout>(R.id.icon2).setOnClickListener {
                Log.d(TAG, "Icon2 clicked - FavoritesFragment")
                abrirFragment(FavoritesFragment())
            }

            findViewById<LinearLayout>(R.id.icon3).setOnClickListener {
                Log.d(TAG, "Icon3 clicked - PokedexFragment")
                abrirFragment(PokedexFragment())
            }

            // Configurar botão de logout
            findViewById<MaterialButton>(R.id.btnLogout).setOnClickListener {
                Log.d(TAG, "Logout button clicked")
                showLogoutConfirmation()
            }

            Log.d(TAG, "MainActivity setup completed")
        } catch (e: Exception) {
            Log.e(TAG, "Error in MainActivity onCreate: ${e.message}", e)
        }
    }

    private fun abrirFragment(fragment: Fragment) {
        Log.d(TAG, "Opening fragment: ${fragment::class.simpleName}")
        supportFragmentManager.beginTransaction()
            .replace(R.id.fragmentContainer, fragment)
            .commit()
    }

    private fun showLogoutConfirmation() {
        AlertDialog.Builder(this)
            .setTitle(getString(R.string.btn_logout))
            .setMessage(getString(R.string.logout_confirmation))
            .setPositiveButton("Sim") { dialog, _ ->
                dialog.dismiss()
                performLogout()
            }
            .setNegativeButton("Não") { dialog, _ ->
                dialog.dismiss()
            }
            .show()
    }

    private fun performLogout() {
        try {
            Log.d(TAG, "Performing logout")
            FirebaseManager.signOut()

            Toast.makeText(this, getString(R.string.logout_success), Toast.LENGTH_SHORT).show()

            // Navegar para a tela de login
            val intent = Intent(this, LoginActivity::class.java)
            intent.flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
            startActivity(intent)
            finish()
        } catch (e: Exception) {
            Log.e(TAG, "Error during logout: ${e.message}", e)
            Toast.makeText(this, "Erro ao fazer logout", Toast.LENGTH_SHORT).show()
        }
    }
}