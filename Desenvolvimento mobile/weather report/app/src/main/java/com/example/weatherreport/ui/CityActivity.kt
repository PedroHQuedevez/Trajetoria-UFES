package com.example.weatherreport.ui

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.Observer
import androidx.lifecycle.ViewModelProvider
import com.example.weatherreport.databinding.ActivityCityBinding
import com.example.weatherreport.ViewModel.CityViewModel
import com.example.weatherreport.R

class CityActivity : AppCompatActivity(), View.OnClickListener {

    private lateinit var binding: ActivityCityBinding
    private lateinit var cityVM: CityViewModel

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityCityBinding.inflate(layoutInflater)
        setContentView(binding.root)

        binding.buttomPrevisao.setOnClickListener(this)

        cityVM = ViewModelProvider(this).get(CityViewModel::class.java)

        setObserver()
    }

    override fun onClick(view: View) {
        if (view.id == R.id.buttom_previsao) {
            val cidade = binding.editCityName.text.toString().trim()
            cityVM.searchWeather(cidade)
        }
    }

    fun setObserver() {

        cityVM.weatherData.observe(this, Observer { weatherData ->
            weatherData?.let {
                val weatherCondition = it.weather.firstOrNull()?.main ?: ""
                val weatherDescription = it.weather.firstOrNull()?.description ?: ""

                val intent = Intent(this, ReportActivity::class.java).apply {
                    putExtra("CITY_NAME", it.name)
                    putExtra("TEMPERATURE", it.main.temp)
                    putExtra("FEELS_LIKE", it.main.feels_like)
                    putExtra("TEMP_MIN", it.main.temp_min)
                    putExtra("TEMP_MAX", it.main.temp_max)
                    putExtra("HUMIDITY", it.main.humidity)
                    putExtra("WIND_SPEED", it.wind.speed)
                    putExtra("COUNTRY", it.sys.country)
                    putExtra("WEATHER_CONDITION", weatherCondition)
                    putExtra("WEATHER_DESCRIPTION", weatherDescription)
                }
                startActivity(intent)
            }
        })

        cityVM.errorMessage.observe(this, Observer { errorMessage ->
            if (errorMessage.isNotEmpty()) {
                Toast.makeText(this, errorMessage, Toast.LENGTH_LONG).show()
            }
        })

        cityVM.isLoading.observe(this, Observer { isLoading ->
            binding.buttomPrevisao.isEnabled = !isLoading
            binding.buttomPrevisao.text = if (isLoading) "Carregando..." else "Previsão"
        })
    }
}