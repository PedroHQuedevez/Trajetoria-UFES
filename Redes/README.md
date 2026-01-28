# Trab2-Redes
# Jogo de Adivinhação - Cliente/Servidor

## Descrição

Este projeto é um jogo de adivinhação de números implementado em Python utilizando sockets para comunicação entre servidor e clientes. Os jogadores se conectam ao servidor e tentam adivinhar um número secreto gerado aleatoriamente. Cada jogador tem sua vez para jogar, e o servidor gerencia a ordem dos turnos e as respostas aos palpites.

## Estrutura do Projeto

- **servidor_jogos.py:** Script do servidor que gerencia o jogo, os clientes e a lógica de adivinhação.
- **client_jogos.py:** Script do cliente que permite ao jogador se conectar ao servidor e participar do jogo.
- **simulador_clientes.py:** Script que simula múltiplos clientes conectando-se ao servidor e enviando palpites aleatórios.
- **README.md:** Documentação do projeto, com instruções de execução, funcionalidades e possíveis melhorias.

## Tecnologias Utilizadas

- **Linguagem:** Python 3
- **Bibliotecas:** `socket`, `threading`, `random`

## Como Executar

### Requisitos

- Python 3 instalado.

### Instruções de Execução

1. Clone o repositório:

   ```bash
   git clone <(https://github.com/PedroHQuedevez/Trab2-Redes)>
   cd <src>
   ```
2. Execute o servidor:

   ```bash
   python servidor_jogos.py
   ```

3. Em outro terminal, execute o cliente:

   ```bash
   python client_jogos.py
   ```

4. O jogo iniciará e os jogadores poderão se conectar ao servidor.
5. Para simular múltiplos clientes, execute o simulador de clientes:
    ```bash
    python simulador_clientes.py
    ```
## Como Testar

- Execute o servidor e conecte múltiplos clientes.
- Teste diferentes palpites e observe as respostas do servidor.
- Verifique o funcionamento do timeout e da gestão de turnos.
- Utilize o simulador de clientes para testar a conexão e interação de múltiplos clientes simultaneamente.

## Funcionalidades Implementadas

- Conexão de múltiplos clientes ao servidor.
- Geração de um número secreto aleatório.
- Gerenciamento de turnos entre os jogadores.
- Mensagens de feedback sobre os palpites.
- Controle de tempo limite para cada jogada.
- Remoção de jogadores desconectados.
- Simulação de múltiplos clientes para testes de carga e comportamento.

## Possíveis Melhorias Futuras

- Implementação de uma interface gráfica para melhor experiência do usuário.
- Suporte a configurações personalizadas (intervalo de números, tempo de espera, etc.).

---


