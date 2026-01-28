package com.example.pokestats.ui

import android.content.Intent
import android.os.Bundle
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.pokestats.R
import com.example.pokestats.databinding.ActivityLoginBinding
import com.example.pokestats.utils.FirebaseManager

class LoginActivity : AppCompatActivity() {

    private lateinit var binding: ActivityLoginBinding

    companion object {
        private const val TAG = "LoginActivity"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(TAG, "==================== LOGIN ACTIVITY STARTED ====================")

        try {
            Log.d(TAG, "Step 1: Inflating layout")
            binding = ActivityLoginBinding.inflate(layoutInflater)

            Log.d(TAG, "Step 2: Setting content view")
            setContentView(binding.root)
            Log.d(TAG, "Layout inflated successfully")

            Log.d(TAG, "Step 3: Checking if user is logged in")
            // Verificar se já está logado
            if (FirebaseManager.isUserLoggedIn()) {
                Log.d(TAG, "User already logged in, navigating to main")
                navigateToMain()
                return
            }

            Log.d(TAG, "Step 4: User not logged in, setting up listeners")
            setupListeners()
            Log.d(TAG, "==================== LOGIN ACTIVITY COMPLETED SUCCESSFULLY ====================")
        } catch (e: Exception) {
            Log.e(TAG, "==================== ERROR IN LOGIN ACTIVITY ====================")
            Log.e(TAG, "Error class: ${e.javaClass.simpleName}")
            Log.e(TAG, "Error message: ${e.message}")
            Log.e(TAG, "Full stack trace:")
            e.printStackTrace()
            Log.e(TAG, "================================================================")
            Toast.makeText(this, "Erro ao inicializar tela de login: ${e.message}", Toast.LENGTH_LONG).show()
        }
    }

    private fun setupListeners() {
        binding.btnLogin.setOnClickListener {
            Log.d(TAG, "Login button clicked")
            val email = binding.etEmail.text.toString().trim()
            val password = binding.etPassword.text.toString().trim()
            Log.d(TAG, "Email: $email, Password length: ${password.length}")

            if (validateInputs(email, password)) {
                loginUser(email, password)
            }
        }

        binding.btnRegister.setOnClickListener {
            Log.d(TAG, "Register button clicked")
            val intent = Intent(this, RegisterActivity::class.java)
            startActivity(intent)
        }

        binding.tvForgotPassword.setOnClickListener {
            Log.d(TAG, "Forgot password clicked")
            val email = binding.etEmail.text.toString().trim()
            if (email.isEmpty()) {
                binding.tilEmail.error = getString(R.string.error_empty_field)
                return@setOnClickListener
            }

            resetPassword(email)
        }
    }

    private fun validateInputs(email: String, password: String): Boolean {
        var isValid = true

        // Validar email
        if (email.isEmpty()) {
            binding.tilEmail.error = getString(R.string.error_empty_field)
            isValid = false
        } else if (!android.util.Patterns.EMAIL_ADDRESS.matcher(email).matches()) {
            binding.tilEmail.error = getString(R.string.error_invalid_email)
            isValid = false
        } else {
            binding.tilEmail.error = null
        }

        // Validar senha
        if (password.isEmpty()) {
            binding.tilPassword.error = getString(R.string.error_empty_field)
            isValid = false
        } else {
            binding.tilPassword.error = null
        }

        return isValid
    }

    private fun loginUser(email: String, password: String) {
        binding.btnLogin.isEnabled = false

        FirebaseManager.auth.signInWithEmailAndPassword(email, password)
            .addOnCompleteListener(this) { task ->
                binding.btnLogin.isEnabled = true

                if (task.isSuccessful) {
                    navigateToMain()
                } else {
                    Toast.makeText(
                        this,
                        getString(R.string.error_login),
                        Toast.LENGTH_SHORT
                    ).show()
                }
            }
    }

    private fun resetPassword(email: String) {
        FirebaseManager.auth.sendPasswordResetEmail(email)
            .addOnCompleteListener { task ->
                if (task.isSuccessful) {
                    Toast.makeText(
                        this,
                        "Email de recuperação enviado!",
                        Toast.LENGTH_SHORT
                    ).show()
                } else {
                    Toast.makeText(
                        this,
                        "Erro ao enviar email de recuperação",
                        Toast.LENGTH_SHORT
                    ).show()
                }
            }
    }

    private fun navigateToMain() {
        val intent = Intent(this, MainActivity::class.java)
        intent.flags = Intent.FLAG_ACTIVITY_NEW_TASK or Intent.FLAG_ACTIVITY_CLEAR_TASK
        startActivity(intent)
        finish()
    }
}

