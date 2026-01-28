package com.example.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.example.myapplication.databinding.ActivityMainBinding


class MainActivity : AppCompatActivity() {

    private lateinit var binding : ActivityMainBinding;

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

    binding.calc.setOnClickListener(){
        try {

            val salario = binding.salario.text.toString().toFloat()
            require(salario > 0) {"Salário deve ser maior que 0" }

            val gastos = binding.gastos.text.toString().toFloat()
            require(gastos >= 0) {"Campo de gastos nãão pode ser vazio"}

            val dependentes = binding.dependentes.text.toString().toInt()
            require(dependentes >= 0) {"campo dependentes não pode ser vazio"}

            val deducaoDependente = 189.59f
            val bCalc = salario - (deducaoDependente * dependentes) - gastos

            var aliquota = 0f
            var deducao = 0f

            if (bCalc in 2428.81f..2826.65f) {
                aliquota = 0.075f
                deducao = 182.16f
            } else if (bCalc in 2826.66f .. 3751.05f) {
                aliquota = 0.15f
                deducao = 394.16f
            } else if (bCalc in 3751.06f .. 4664.68f) {
                aliquota= 0.225f
                deducao = 675.49f
            } else if (bCalc >= 4664.69) {
                aliquota = 0.275f
                deducao = 908.73f
            }

            var impostoRenda = (bCalc * aliquota) - deducao

            binding.resultado.text = "R$ %.2f".format(impostoRenda)
            Toast.makeText(applicationContext, R.string.sucesso, Toast.LENGTH_SHORT).show()

            } catch (e: Exception){
            Toast.makeText(applicationContext, R.string.erro, Toast.LENGTH_SHORT).show()
            }
        }
    }
}
