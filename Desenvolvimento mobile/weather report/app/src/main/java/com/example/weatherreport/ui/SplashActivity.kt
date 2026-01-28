package com.example.weatherreport.ui

import android.content.Intent
import android.os.Bundle
import android.os.Handler
import android.os.Looper
import androidx.appcompat.app.AppCompatActivity
import com.example.weatherreport.R

class SplashActivity : AppCompatActivity() {
    override fun onCreate(savedInstance: Bundle?){
        super.onCreate(savedInstance)
        setContentView(R.layout.activity_splashscreen)

        Handler(Looper.getMainLooper()).postDelayed({
            startActivity(Intent(this, CityActivity::class.java))
            finish()
        }, 2000)


    }
}