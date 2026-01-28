package com.example.weatherreport.ui

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.example.weatherreport.R
import com.example.weatherreport.databinding.ActivityReportBinding

class ReportActivity : AppCompatActivity() {

    private lateinit var binding: ActivityReportBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityReportBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Receber dados da intent
        val cityName = intent.getStringExtra("CITY_NAME") ?: "Cidade Desconhecida"
        val temperature = intent.getDoubleExtra("TEMPERATURE", 0.0)
        val feelsLike = intent.getDoubleExtra("FEELS_LIKE", 0.0)
        val tempMin = intent.getDoubleExtra("TEMP_MIN", 0.0)
        val tempMax = intent.getDoubleExtra("TEMP_MAX", 0.0)
        val humidity = intent.getIntExtra("HUMIDITY", 0)
        val windSpeed = intent.getDoubleExtra("WIND_SPEED", 0.0)
        val country = intent.getStringExtra("COUNTRY") ?: ""
        val weatherCondition = intent.getStringExtra("WEATHER_CONDITION") ?: ""
        val weatherDescription = intent.getStringExtra("WEATHER_DESCRIPTION") ?: ""


        binding.cityname.text = "$cityName, $country"


        val weatherType = getWeatherTypeInPortuguese(weatherCondition, weatherDescription)
        binding.temperature.text = "${temperature.toInt()}°C, $weatherType"

        binding.feelsLike.text = "Sensação: ${feelsLike.toInt()}°C"
        binding.tempMinMax.text = "Min: ${tempMin.toInt()}°C / Max: ${tempMax.toInt()}°C"
        binding.humidity.text = "Umidade: ${humidity}%"
        binding.wind.text = "Vento: ${windSpeed} km/h"


        setWeatherIcon(weatherCondition)

        binding.back.setOnClickListener {
            finish()
        }
    }

    private fun setWeatherIcon(weatherCondition: String) {
        val iconRes = when {
            weatherCondition.contains("rain", ignoreCase = true) -> R.drawable.rain_icon
            weatherCondition.contains("cloud", ignoreCase = true) -> R.drawable.cloudy_icon
            weatherCondition.contains("clear", ignoreCase = true) -> R.drawable.sunny_icon
            weatherCondition.contains("sun", ignoreCase = true) -> R.drawable.sunny_icon
            else -> R.drawable.weather_svgrepo_com
        }
        binding.weatherIcon.setImageResource(iconRes)
    }


    private fun getWeatherTypeInPortuguese(condition: String, description: String): String {
        return when {
            condition.contains("clear", ignoreCase = true) -> "ensolarado"
            condition.contains("cloud", ignoreCase = true) -> "nublado"
            condition.contains("rain", ignoreCase = true) -> "chuvoso"
            condition.contains("drizzle", ignoreCase = true) -> "garoa"
            condition.contains("thunderstorm", ignoreCase = true) -> "tempestade"
            condition.contains("snow", ignoreCase = true) -> "nevando"
            condition.contains("mist", ignoreCase = true) -> "névoa"
            condition.contains("fog", ignoreCase = true) -> "neblina"
            else -> description.toLowerCase()
        }
    }
}