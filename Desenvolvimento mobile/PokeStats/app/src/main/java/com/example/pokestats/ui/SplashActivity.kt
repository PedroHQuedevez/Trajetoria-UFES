package com.example.pokestats.ui

import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.util.Log
import androidx.appcompat.app.AppCompatActivity
import com.example.pokestats.R

class SplashActivity : AppCompatActivity() {

    companion object {
        private const val TAG = "SplashActivity"
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        Log.d(TAG, "onCreate started")

        try {
            setContentView(R.layout.activity_splash_screen)
            Log.d(TAG, "Splash screen layout set")

            Handler(Looper.getMainLooper()).postDelayed({
                Log.d(TAG, "Navigating to LoginActivity")
                val intent = Intent(this, LoginActivity::class.java)
                startActivity(intent)
                finish()
                Log.d(TAG, "SplashActivity finished")
            }, 2000)
        } catch (e: Exception) {
            Log.e(TAG, "Error in SplashActivity: ${e.message}", e)
        }
    }
}