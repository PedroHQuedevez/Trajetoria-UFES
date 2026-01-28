package com.example.pokestats.utils

import android.util.Log
import com.google.firebase.auth.FirebaseAuth
import com.google.firebase.firestore.FirebaseFirestore

object FirebaseManager {

    private const val TAG = "FirebaseManager"

    val auth: FirebaseAuth by lazy {
        Log.d(TAG, "Initializing FirebaseAuth")
        FirebaseAuth.getInstance().also {
            Log.d(TAG, "FirebaseAuth initialized, current user: ${it.currentUser?.email ?: "none"}")
        }
    }

    val db: FirebaseFirestore by lazy {
        Log.d(TAG, "Initializing Firestore")
        FirebaseFirestore.getInstance().also {
            Log.d(TAG, "Firestore initialized successfully")
        }
    }

    fun isUserLoggedIn(): Boolean {
        return try {
            val isLoggedIn = auth.currentUser != null
            Log.d(TAG, "isUserLoggedIn: $isLoggedIn")
            isLoggedIn
        } catch (e: Exception) {
            Log.e(TAG, "Error checking if user is logged in: ${e.message}", e)
            false
        }
    }

    fun getCurrentUserId(): String? {
        return auth.currentUser?.uid
    }

    fun getCurrentUserEmail(): String? {
        return auth.currentUser?.email
    }

    fun signOut() {
        Log.d(TAG, "Signing out user")
        auth.signOut()
    }
}

