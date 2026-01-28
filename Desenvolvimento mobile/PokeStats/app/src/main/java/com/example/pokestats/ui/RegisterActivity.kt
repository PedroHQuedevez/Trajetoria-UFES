package com.example.pokestats.ui

import android.content.Intent
import android.os.Bundle
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import com.example.pokestats.R
import com.example.pokestats.databinding.ActivityRegisterBinding
import com.example.pokestats.utils.FirebaseManager
import com.google.firebase.auth.FirebaseAuthInvalidCredentialsException
import com.google.firebase.auth.FirebaseAuthUserCollisionException
import com.google.firebase.auth.FirebaseAuthWeakPasswordException
import com.google.firebase.FirebaseNetworkException

class RegisterActivity : AppCompatActivity() {

    private lateinit var binding: ActivityRegisterBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityRegisterBinding.inflate(layoutInflater)
        setContentView(binding.root)


        setupListeners()
    }

    private fun setupListeners() {
        binding.btnBack.setOnClickListener {
            finish()
        }

        binding.btnRegister.setOnClickListener {
            val name = binding.etName.text.toString().trim()
            val email = binding.etEmail.text.toString().trim()
            val password = binding.etPassword.text.toString().trim()
            val confirmPassword = binding.etConfirmPassword.text.toString().trim()

            if (validateInputs(name, email, password, confirmPassword)) {
                registerUser(name, email, password)
            }
        }


    }

    private fun validateInputs(
        name: String,
        email: String,
        password: String,
        confirmPassword: String
    ): Boolean {
        var isValid = true

        // Validar nome
        if (name.isEmpty()) {
            binding.tilName.error = getString(R.string.error_empty_field)
            isValid = false
        } else {
            binding.tilName.error = null
        }

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
        } else if (password.length < 6) {
            binding.tilPassword.error = getString(R.string.error_short_password)
            isValid = false
        } else {
            binding.tilPassword.error = null
        }

        // Validar confirmação de senha
        if (confirmPassword.isEmpty()) {
            binding.tilConfirmPassword.error = getString(R.string.error_empty_field)
            isValid = false
        } else if (password != confirmPassword) {
            binding.tilConfirmPassword.error = getString(R.string.error_password_mismatch)
            isValid = false
        } else {
            binding.tilConfirmPassword.error = null
        }

        return isValid
    }

    private fun registerUser(name: String, email: String, password: String) {
        binding.btnRegister.isEnabled = false

        FirebaseManager.auth.createUserWithEmailAndPassword(email, password).addOnCompleteListener({
            if (it.isSuccessful) {
                Toast.makeText(this, getString(R.string.success_register), Toast.LENGTH_SHORT).show()
                navigateToLogin()
            }
        }).addOnFailureListener({
            binding.btnRegister.isEnabled = true
            var msg = getString(R.string.error_register_generic)
            if (it is FirebaseAuthInvalidCredentialsException) {
                msg = getString(R.string.error_invalid_credentials)
            } else if (it is FirebaseAuthWeakPasswordException) {
                msg = getString(R.string.error_weak_password)
            } else if (it is FirebaseAuthUserCollisionException) {
                msg = getString(R.string.error_user_collision)
            } else if (it is FirebaseNetworkException) {
                msg = getString(R.string.error_network)
            }
            Toast.makeText(this, msg, Toast.LENGTH_SHORT).show()
        })
    }

    private fun navigateToLogin() {
        val intent = Intent(this, LoginActivity::class.java)
        startActivity(intent)
        finish()
    }
}

