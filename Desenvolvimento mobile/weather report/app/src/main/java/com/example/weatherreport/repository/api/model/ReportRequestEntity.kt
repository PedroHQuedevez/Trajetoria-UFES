package com.example.weatherreport.repository.api.model

data class ReportRequestEntity(
    val name: String,
    val main: Main,
    val wind: Wind,
    val sys: Sys,
    val weather: List<Weather>
)

data class Main(
    val temp: Double,
    val feels_like: Double,
    val temp_min: Double,
    val temp_max: Double,
    val humidity: Int
)

data class Wind(
    val speed: Double
)

data class Sys(
    val country: String
)

data class Weather(
    val main: String,
    val description: String,
    val icon: String
)