import React from 'react';
import {
  Chart as ChartJS,
  RadialLinearScale,
  PointElement,
  LineElement,
  Filler,
  Tooltip,
  Legend,
} from 'chart.js';
import { Radar } from 'react-chartjs-2';

ChartJS.register(
  RadialLinearScale,
  PointElement,
  LineElement,
  Filler,
  Tooltip,
  Legend
);

const GameRadarChart = ({ reviews }) => {
/**
 * Componente para exibir gráfico radar de atributos de um jogo.
 * @module GameRadarChart
 * @param {Object} props Propriedades do componente
 * @param {Object} props.data Dados do gráfico
 * @returns {JSX.Element} Elemento React do gráfico radar
 */
  // Calcular médias de cada aspecto
  /**
   * Calcula as médias dos aspectos avaliados nas reviews.
   * @returns {Object} Médias de cada aspecto
   */
  const calculateAverages = () => {
    if (!reviews || reviews.length === 0) {
      return {
        gameplayRating: 0,
        visualRating: 0,
        audioRating: 0,
        difficultyRating: 0,
        immersionRating: 0,
        historyRating: 0
      };
    }

    const totals = reviews.reduce((acc, review) => {
      acc.gameplayRating += review.ratings.gameplay || 0;
      acc.visualRating += review.ratings.visual || 0;
      acc.audioRating += review.ratings.audio   || 0;
      acc.difficultyRating += review.ratings.difficulty || 0;
      acc.immersionRating += review.ratings.immersion || 0;
      acc.historyRating += review.ratings.history || 0;
      return acc;
    }, {
      gameplayRating: 0,
      visualRating: 0,
      audioRating: 0,
      difficultyRating: 0,
      immersionRating: 0,
      historyRating: 0
    });

    const count = reviews.length;
    
    return {
      gameplayRating: (totals.gameplayRating / count).toFixed(1),
      visualRating: (totals.visualRating / count).toFixed(1),
      audioRating: (totals.audioRating / count).toFixed(1),
      difficultyRating: (totals.difficultyRating / count).toFixed(1),
      immersionRating: (totals.immersionRating / count).toFixed(1),
      historyRating: (totals.historyRating / count).toFixed(1)
    };
  };

  const averages = calculateAverages();

  const data = {
    labels: [
      'Gameplay',
      'Visual',
      'Áudio',
      'Dificuldade',
      'Imersão',
      'História'
    ],
    datasets: [
      {
        label: 'Avaliação Média',
        data: [
          averages.gameplayRating,
          averages.visualRating,
          averages.audioRating,
          averages.difficultyRating,
          averages.immersionRating,
          averages.historyRating
        ],
        backgroundColor: 'rgba(41, 182, 246, 0.2)',
        borderColor: 'rgba(41, 182, 246, 1)',
        borderWidth: 2,
        pointBackgroundColor: 'rgba(41, 182, 246, 1)',
        pointBorderColor: '#fff',
        pointHoverBackgroundColor: '#fff',
        pointHoverBorderColor: 'rgba(41, 182, 246, 1)',
        pointRadius: 5,
        pointHoverRadius: 7,
      },
    ],
  };

  const options = {
    responsive: true,
    maintainAspectRatio: false,
    plugins: {
      legend: {
        position: 'top',
        labels: {
          font: {
            size: 12,
            weight: 'bold'
          },
          color: '#fff'
        }
      },
      tooltip: {
        callbacks: {
          label: function(context) {
            return `${context.label}: ${context.parsed.r}/5`;
          }
        }
      },
    },
    scales: {
      r: {
        angleLines: {
          display: true,
          color: 'rgba(255, 255, 255, 0.2)'
        },
        grid: {
          color: 'rgba(255, 255, 255, 0.2)'
        },
        pointLabels: {
          font: {
            size: 11,
            weight: 'bold'
          },
          color: '#ccc'
        },
        suggestedMin: 0,
        suggestedMax: 5,
        ticks: {
          display: true,
          stepSize: 1,
          font: {
            size: 10
          },
          color: '#ccc',
          backdropColor: 'transparent'
        }
      },
    },
  };

  if (!reviews || reviews.length === 0) {
    return (
      <div className="radar-chart-container">
        <div className="chart-header">
          <h3>Avaliação Geral por Aspectos</h3>
          <p>Ainda não há avaliações para este jogo</p>
        </div>
        <div className="chart-wrapper">
          <Radar data={{
            ...data,
            datasets: [{
              ...data.datasets[0],
              data: [0, 0, 0, 0, 0, 0],
              backgroundColor: 'rgba(128, 128, 128, 0.2)',
              borderColor: 'rgba(128, 128, 128, 1)',
              pointBackgroundColor: 'rgba(128, 128, 128, 1)',
            }]
          }} options={options} />
        </div>
        <div className="chart-legend">
          <div className="legend-stats">
            <div className="stat-item">
              <span className="stat-label">Gameplay:</span>
              <span className="stat-value">-/5</span>
            </div>
            <div className="stat-item">
              <span className="stat-label">Visual:</span>
              <span className="stat-value">-/5</span>
            </div>
            <div className="stat-item">
              <span className="stat-label">Áudio:</span>
              <span className="stat-value">-/5</span>
            </div>
            <div className="stat-item">
              <span className="stat-label">Dificuldade:</span>
              <span className="stat-value">-/5</span>
            </div>
            <div className="stat-item">
              <span className="stat-label">Imersão:</span>
              <span className="stat-value">-/5</span>
            </div>
            <div className="stat-item">
              <span className="stat-label">História:</span>
              <span className="stat-value">-/5</span>
            </div>
          </div>
        </div>
      </div>
    );
  }

  return (
    <div className="radar-chart-container">
      <div className="chart-header">
        <h3>Avaliação Geral por Aspectos</h3>
        <p>Baseado em {reviews.length} avaliaç{reviews.length !== 1 ? 'ões' : 'ão'}</p>
      </div>
      <div className="chart-wrapper">
        <Radar data={data} options={options} />
      </div>
      <div className="chart-legend">
        <div className="legend-stats">
          {Object.entries(averages).map(([key, value]) => {
            const labels = {
              gameplayRating: 'Gameplay',
              visualRating: 'Visual',
              audioRating: 'Áudio',
              difficultyRating: 'Dificuldade',
              immersionRating: 'Imersão',
              historyRating: 'História'
            };
            
            return (
              <div key={key} className="stat-item">
                <span className="stat-label">{labels[key]}:</span>
                <span className="stat-value">{value}/5</span>
              </div>
            );
          })}
        </div>
      </div>
    </div>
  );
};

export default GameRadarChart;