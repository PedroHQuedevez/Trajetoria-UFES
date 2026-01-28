package com.example.weatherreport.repository.api.service

import com.example.weatherreport.repository.api.model.ReportRequestEntity
import retrofit2.http.GET
import retrofit2.http.Query

interface ReportRequestService {

    @GET("weather")
    suspend fun getWeather(
        @Query("q") city: String,
        @Query("appid") apiKey: String,
        @Query("units") units: String = "metric",
        @Query("lang") lang: String = "pt"
    ): ReportRequestEntity
}