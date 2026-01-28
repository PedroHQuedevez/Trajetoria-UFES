package com.example.weatherreport.repository.api.client

import com.example.weatherreport.utils.Constants
import okhttp3.OkHttpClient
import retrofit2.Retrofit
import retrofit2.converter.gson.GsonConverterFactory
import java.util.concurrent.TimeUnit

class ClientRetrofit {

    companion object {

        private fun getRetrofitInstance(): Retrofit {
            val httpClient = OkHttpClient.Builder()
                .connectTimeout(30, TimeUnit.SECONDS)
                .readTimeout(30, TimeUnit.SECONDS)
                .build()

            return Retrofit.Builder()
                .baseUrl(Constants.API.BASE_URL_WEATHER_REPORT)
                .client(httpClient)
                .addConverterFactory(GsonConverterFactory.create())
                .build()
        }

        fun <S> createService(className: Class<S>): S {
            return getRetrofitInstance().create(className)
        }
    }
}