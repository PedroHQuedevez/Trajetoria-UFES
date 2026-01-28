package com.example.pokestats

import android.app.Application
import android.util.Log
import com.google.firebase.FirebaseApp

class PokeStatsApplication : Application() {

    companion object {
        private const val TAG = "PokeStatsApplication"
    }

    override fun onCreate() {
        super.onCreate()
        Log.d(TAG, "Application onCreate started")

        try {
            // Initialize Firebase
            FirebaseApp.initializeApp(this)
            Log.d(TAG, "Firebase initialized successfully")
        } catch (e: Exception) {
            Log.e(TAG, "Error initializing Firebase: ${e.message}", e)
        }
    }
}

