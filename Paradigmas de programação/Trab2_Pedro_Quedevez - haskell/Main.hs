module Main where

import System.IO
import Data.List (minimumBy, maximumBy, sortBy, delete, intercalate)
import Data.Function (on)
import Text.Read (readMaybe)

data Ponto = Ponto
    { identificador :: Int
    , coordenadas :: [Double]
    } deriving (Show, Eq)

data Ligacao = Ligacao
    { pontoOrigem :: Ponto
    , pontoDestino :: Ponto
    , distancia :: Double
    } deriving (Show, Eq)

data Grupo = Grupo
    { pontos :: [Ponto]
    , ligacoes :: [Ligacao]
    } deriving (Show, Eq)

-- Função para calcular distância euclidiana entre dois pontos
distanciaEuclidiana :: Ponto -> Ponto -> Double
distanciaEuclidiana p1 p2 = sqrt $ sum $ zipWith (\x y -> (x - y) ** 2) (coordenadas p1) (coordenadas p2)

-- Função para criar uma nova ligação
criarLigacao :: Ponto -> Ponto -> Ligacao
criarLigacao p1 p2 = Ligacao p1 p2 (distanciaEuclidiana p1 p2)

-- Função para ler CSV e criar pontos
lerCSV :: String -> IO [Ponto]
lerCSV nomeArquivo = do
    conteudo <- readFile nomeArquivo
    let linhas = lines conteudo
    let pontosComId = zipWith criarPonto [1..] linhas
    return pontosComId
  where
    criarPonto :: Int -> String -> Ponto
    criarPonto id linha = 
        let coords = map read $ words $ map (\c -> if c == ',' then ' ' else c) linha
        in Ponto id coords


-- Função para adicionar ponto ao grupo (se o ponto não existir) -- adiciona no final da lista
adicionarPonto :: Ponto -> Grupo -> Grupo
adicionarPonto ponto grupo@(Grupo pts ligs)
    | ponto `elem` pts = grupo
    | otherwise = Grupo (pts ++ [ponto]) ligs

-- Função para adicionar ligação ao grupo
adicionarLigacao :: Ligacao -> Grupo -> Grupo
adicionarLigacao ligacao (Grupo pts ligs) = Grupo pts (ligacao : ligs)

-- Função para remover ligação do grupo
removerLigacao :: Ligacao -> Grupo -> Grupo
removerLigacao ligacao (Grupo pts ligs) = Grupo pts (delete ligacao ligs)

-- Função de agrupamento inicial
agruparPontos :: [Ponto] -> Grupo
agruparPontos [] = Grupo [] []  -- Caso lista vazia
agruparPontos (primeiroPonto:resto) = 
    -- criar um grupo vazio
    let grupoVazio = Grupo [] []
        
        -- calcular todas as ligações do primeiro ponto para os demais
        ligacoesIniciais = map (criarLigacao primeiroPonto) resto
        menorLigacaoInicial = minimumBy (compare `on` distancia) ligacoesIniciais
        destinoMenorLigacao = pontoDestino menorLigacaoInicial
        
        -- Adicionar a menor ligação ao grupo
        grupoComLigacao = adicionarLigacao menorLigacaoInicial grupoVazio
        
        --adicionar o primeiro ponto ao grupo e removê-lo da lista
        grupoComPrimeiroPonto = adicionarPonto primeiroPonto grupoComLigacao
        
    in agruparRecursivo resto grupoComPrimeiroPonto destinoMenorLigacao
  where
    agruparRecursivo :: [Ponto] -> Grupo -> Ponto -> Grupo
    agruparRecursivo [] grupo _ = grupo  -- Lista vazia, retorna grupo atual
    agruparRecursivo listaPontos grupo pontoCorrente =
        -- procurar o ponto destino na lista
        if pontoCorrente `elem` listaPontos then
            let -- calcular ligações do ponto corrente com os demais
                pontosRestantes = filter (/= pontoCorrente) listaPontos
                ligacoesDoPontoCorrente = map (criarLigacao pontoCorrente) pontosRestantes

            in if null ligacoesDoPontoCorrente then
                -- Se não há mais ligações possíveis, adiciona o ponto e termina
                let grupoFinal = adicionarPonto pontoCorrente grupo
                    novaListaPontos = delete pontoCorrente listaPontos
                in agruparRecursivo novaListaPontos grupoFinal pontoCorrente
            else
                -- encontrar menor ligação
                let menorLigacao = minimumBy (compare `on` distancia) ligacoesDoPontoCorrente
                    novoDestino = pontoDestino menorLigacao
                    
                    grupoComNovaLigacao = adicionarLigacao menorLigacao grupo
                    
                    grupoComNovoPonto = adicionarPonto pontoCorrente grupoComNovaLigacao
                    
                    novaListaPontos = delete pontoCorrente listaPontos
                    
                in agruparRecursivo novaListaPontos grupoComNovoPonto novoDestino
        else
            -- Se o ponto destino não está na lista, algo deu errado
            grupo

-- comparar ligações 
compararLigacoes :: Ligacao -> Ligacao -> Ordering
compararLigacoes l1 l2 =
    let dist1 = distancia l1
        dist2 = distancia l2

        id1_min = min (identificador $ pontoOrigem l1) (identificador $ pontoDestino l1)
        id1_max = max (identificador $ pontoOrigem l1) (identificador $ pontoDestino l1)
        id2_min = min (identificador $ pontoOrigem l2) (identificador $ pontoDestino l2)
        id2_max = max (identificador $ pontoOrigem l2) (identificador $ pontoDestino l2)
        
    in -- Primeiro compara distância, depois menor ID, depois maior ID
       compare (dist1, id1_min, id1_max) (dist2, id2_min, id2_max)

-- Função para dividir grupo em dois a partir da maior ligação
dividirEm2Grupos :: Grupo -> (Grupo, Grupo)
dividirEm2Grupos (Grupo pts ligs) =
    case ligs of
        [] -> (Grupo pts [], Grupo [] [])  -- Se não há ligações, pontos vão para o primeiro grupo
        _ -> 
            
            let maiorLigacao = maximumBy compararLigacoes ligs
                
                idOrigem = identificador $ pontoOrigem maiorLigacao
                idDestino = identificador $ pontoDestino maiorLigacao
                
                ligacoesSemMaior = delete maiorLigacao ligs
                
                posicaoOrigem = encontrarPosicao idOrigem pts
                posicaoDestino = encontrarPosicao idDestino pts
                
                -- Separar pontos: anteriores + origem para grupo1, destino + posteriores para grupo2
                (pontosGrupo1, pontosGrupo2) = separarPontos pts posicaoOrigem posicaoDestino
                
                -- Separar ligações: ligações que conectam pontos do grupo1 e grupo2
                (ligacoesGrupo1, ligacoesGrupo2) = separarLigacoesPorPontos ligacoesSemMaior pontosGrupo1 pontosGrupo2
                
            in (Grupo pontosGrupo1 ligacoesGrupo1, Grupo pontosGrupo2 ligacoesGrupo2)
  where
    -- Encontrar a posição de um ponto pelo seu ID na lista
    encontrarPosicao :: Int -> [Ponto] -> Int
    encontrarPosicao targetId pontos = 
        case [i | (p, i) <- zip pontos [0..], identificador p == targetId] of
            (pos:_) -> pos
            [] -> 0  -- Se não encontrar, assume posição 0
    
    -- Separar pontos baseado nas posições de origem e destino
    separarPontos :: [Ponto] -> Int -> Int -> ([Ponto], [Ponto])
    separarPontos pontos posOrigem posDestino =
        let pontosIndexados = zip pontos [0..]
            grupo1 = [p | (p, i) <- pontosIndexados, i <= posOrigem]
            grupo2 = [p | (p, i) <- pontosIndexados, i >= posDestino]
        in (grupo1, grupo2)
    
    --Separar ligações baseado em quais pontos pertencem a cada grupo
    separarLigacoesPorPontos :: [Ligacao] -> [Ponto] -> [Ponto] -> ([Ligacao], [Ligacao])
    separarLigacoesPorPontos ligacoes pontosGrupo1 pontosGrupo2 =
        let idsGrupo1 = map identificador pontosGrupo1
            idsGrupo2 = map identificador pontosGrupo2
            
            -- Uma ligação pertence ao grupo se ambos os pontos estão no grupo
            ligacoesGrupo1 = [l | l <- ligacoes, 
                             identificador (pontoOrigem l) `elem` idsGrupo1 && 
                             identificador (pontoDestino l) `elem` idsGrupo1]
            
            ligacoesGrupo2 = [l | l <- ligacoes, 
                             identificador (pontoOrigem l) `elem` idsGrupo2 && 
                             identificador (pontoDestino l) `elem` idsGrupo2]
        in (ligacoesGrupo1, ligacoesGrupo2)

-- Função para dividir em K grupos
dividirKgrupos :: Grupo -> Int -> [Grupo]
dividirKgrupos grupoInicial k
    | k <= 1 = [grupoInicial]  -- Se k <= 1, retorna apenas o grupo inicial
    | k > length (pontos grupoInicial) = [grupoInicial]  -- Se k > número de pontos, não pode dividir
    | otherwise = dividirRecursivo [grupoInicial] k
  where
    dividirRecursivo :: [Grupo] -> Int -> [Grupo]
    dividirRecursivo grupos numGruposDesejados
        | length grupos >= numGruposDesejados = grupos  -- Já temos K grupos
        | otherwise =
            
            case encontrarGrupoComMaiorLigacao grupos of
                Nothing -> grupos  -- Não há mais ligações para dividir
                Just grupoEscolhido ->
                    let (grupo1, grupo2) = dividirEm2Grupos grupoEscolhido
                        -- Remover o grupo original e adicionar os dois novos grupos
                        novosGrupos = grupo1 : grupo2 : delete grupoEscolhido grupos
                    
                    in dividirRecursivo novosGrupos numGruposDesejados
    
    -- Encontra o grupo com a maior ligação dentre todos os grupos
    encontrarGrupoComMaiorLigacao :: [Grupo] -> Maybe Grupo
    encontrarGrupoComMaiorLigacao grupos =
        let gruposComLigacoes = [g | g <- grupos, not (null (ligacoes g))]
        in case gruposComLigacoes of
            [] -> Nothing  -- Nenhum grupo tem ligações
            _ -> Just $ maximumBy compararGruposPorMaiorLigacao gruposComLigacoes
    
    -- Compara grupos pela sua maior ligação (seguindo os critérios de desempate)
    compararGruposPorMaiorLigacao :: Grupo -> Grupo -> Ordering
    compararGruposPorMaiorLigacao g1 g2 =
        let maiorLigacao1 = maximumBy compararLigacoes (ligacoes g1)
            maiorLigacao2 = maximumBy compararLigacoes (ligacoes g2)
        in compararLigacoes maiorLigacao1 maiorLigacao2


main :: IO ()
main = do
    putStr "Forneça o nome do arquivo de entrada: "
    hFlush stdout
    nomeArquivoEntrada <- getLine
    
    putStr "Forneça o nome do arquivo de saída: "
    hFlush stdout
    nomeArquivoSaida <- getLine
    
    putStr "Forneça o número de grupos (K): "
    hFlush stdout
    kStr <- getLine
    let k = read kStr :: Int
    
    -- Ler pontos do arquivo
    conjuntoPontos <- lerCSV nomeArquivoEntrada
    
    case conjuntoPontos of
        [] -> putStrLn "Erro: Não foi possível ler pontos do arquivo."
        _ -> do
            -- Criar grupo inicial seguindo os passos especificados
            let grupoCompleto = agruparPontos conjuntoPontos
            
            -- Dividir em K grupos
            let grupos = dividirKgrupos grupoCompleto k
            
            -- Ordenar grupos por tamanho (menor para maior)
            let gruposOrdenados = sortBy (compare `on` length . pontos) grupos
                        
            -- Escrever resultado no arquivo
            escreverResultado nomeArquivoSaida gruposOrdenados
  where

-- Função para converter grupo para string de saída (com vírgulas e espaço no início)
grupoParaString :: Grupo -> String
grupoParaString (Grupo pts _) = 
    let ptsOrdenados = sortBy (compare `on` identificador) pts
        ids = map (show . identificador) ptsOrdenados
    in " " ++ intercalate ", " ids

-- Função para escrever resultado no arquivo
escreverResultado :: String -> [Grupo] -> IO ()
escreverResultado nomeArquivo grupos = do
    let linhas = map grupoParaString grupos
    writeFile nomeArquivo (unlines linhas)

