package com.example.weatherreport.repository.api

import com.example.weatherreport.utils.Constants
import com.example.weatherreport.repository.api.client.ClientRetrofit
import com.example.weatherreport.repository.api.service.ReportRequestService

class WeatherRepository {

    private val api = ClientRetrofit.createService(ReportRequestService::class.java)
    suspend fun getWeather(city: String): Result<com.example.weatherreport.repository.api.model.ReportRequestEntity> {
        return try {
            val response = api.getWeather(city, Constants.API.API_KEY)
            Result.success(response)
        } catch (e: Exception) {
            Result.failure(e)
        }
    }
}