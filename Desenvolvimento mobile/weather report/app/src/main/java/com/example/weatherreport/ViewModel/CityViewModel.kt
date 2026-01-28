package com.example.weatherreport.ViewModel

import androidx.lifecycle.LiveData
import androidx.lifecycle.MutableLiveData
import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import kotlinx.coroutines.launch
import com.example.weatherreport.repository.api.WeatherRepository

class CityViewModel : ViewModel() {

    private var cityName = MutableLiveData<String>()
    private val repository = WeatherRepository()


    private val _weatherData = MutableLiveData<com.example.weatherreport.repository.api.model.ReportRequestEntity?>()
    val weatherData: LiveData<com.example.weatherreport.repository.api.model.ReportRequestEntity?> = _weatherData

    private val _isLoading = MutableLiveData<Boolean>()
    val isLoading: LiveData<Boolean> = _isLoading

    private val _errorMessage = MutableLiveData<String>()
    val errorMessage: LiveData<String> = _errorMessage

    fun getCity(): LiveData<String> {
        return cityName
    }


    fun searchWeather(city: String) {
        if (city.isBlank()) {
            _errorMessage.value = "Digite uma cidade válida"
            return
        }

        _isLoading.value = true
        _errorMessage.value = ""

        viewModelScope.launch {
            try {
                val result = repository.getWeather(city)
                if (result.isSuccess) {
                    _weatherData.value = result.getOrNull()
                    cityName.value = city
                    _errorMessage.value = ""
                } else {
                    _errorMessage.value = "Cidade não encontrada: $city"
                    _weatherData.value = null
                }
            } catch (e: Exception) {
                _errorMessage.value = "Erro de conexão: ${e.message}"
                _weatherData.value = null
            } finally {
                _isLoading.value = false
            }
        }
    }
}