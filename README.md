# LabirintoRecorrente
<img align="center" height="20px" width="60px" src="https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white"/> </br>
Atividade realizada no 3º periodo para a disciplina de Algoritmos e Estrutura de Dados.

# Problema apresentado
- Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor x,y dessa estrutura. Nesse labirinto há paredes que bloqueiam certos passos (#), perigos que consomem parte de sua vida (*) e trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).
- Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida é preciso, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.
- Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados.

# Arquivos
<strong>Main.cpp:</strong> É feito a chamada inicialmente de uma função que ira retornar o tamanho da matriz presente no arquivo input.data e quantas matriz possuem nesse arquivo, é feita tambem a chamada das duas funções principais do funcionamento do codigo, 'LerArquivo' e 'StartJogo', é nela em que todo nosso codigo sera executado.<br>
<strong>Labirinto.hpp:</strong> Onde é criada todas as nossas funções que seram executadas no decorrer do algoritmo.<br>
<strong>Labirinto.cpp:</strong> Onde é feita a estruturação de todas as funções criadas e onde sera desenvolvido todo o codigo.<br>
<strong>Terminal:</strong> Aparece ao usuario, quantas casas foram percorridas durante a execução do codigo, quantos itens foram coletados, a quantidade de perigos enfrentados e quantas posiçoes nao foram acessadas durante o percurso gerado pelo codigo.<br>
<strong>dataset/input.data:</strong> Arquivo contendo o tamanho da matriz, a quantidade matrizes, sendo ela(s) de numeros inteiros e dois tipos de caracteres, '*' e '#',  somente.
<ul>
  <li>Na primeira linha do arquivo é necessário ter o tamanho da matriz e a quantidade de matriz que irão compor esse arquivo, sendo implementado dessa maneira: '5 5 3' e a necessidade de possuir ao mínimo uma matriz de numeros inteiros entre 0 e 9 e somente dois tipos de caracteres ja especificados acima, do tamanho correspondente ao da primeira linha, para a boa execução do código</li>
</ul>

# Resolução do problema 
As duas funções principais que faz o funcionamento do codigo sao: `StartJogo` e `PercorrerMatriz`, são nelas que é feita toda a implementação do desenvolvimento do codigo, cumprimindo todas as codiçoes passadas pelo professor.<br>

<strong>Explicação detalhada da função 'LerArquivo':</strong>

<ul>
<li>É feita a abertura do arquivo input.data, pois é nela que esta armazenado todas as nossas matrizes que usaremos durante todo o nosso jogo.</li>
<li>O arquivo input.data é lido de maneira que a cada linha vazia vista, é sinal de que toda uma matriz foi percorrida e desse modo podemos salvar essa matriz lida em um arquivo que contera somente ela.</li>
<li>Esse arquivo unico de cada matriz é feito na função `CriandoArquivoParaCadaMatriz`(linha X) na qual cada arquivo recebera um nome diferente, basedo na sua matriz correspondente, ou seja, para a primeira matriz lida, o nome de seu arquivo sera: 'dataset/matriz1.data'</li>
<li>Os nomes de arquivos criados sao todos salvos em um vetro global para sua utlização em outro desenvolvimento</li>
</ul>

<div align="center">
  <img src="/imgs/ArquivosCriados_Exemplo.PNG" alt="Pasta Dataset">
  <p align="center"><em> Exemplificação pasta dataset </em></p>
</div>

<strong>Explicação detalhada da função 'Startjogo':</strong><br>
De maneira geral nessa função é feita a abertura do arquivo que contem a matriz a ser percorrida no momento, é chamado a função que ira percorrer a matriz e é onde é feito a analise o numero de vidas, se devemos ou não continuar no jogo e por fim é nela que nos teletrasportamos para a proxima matriz. 

<ul>
<li>É pedido ao usuario que digite o numero da posição inical em que deseja começar o jogo</li>
  - importante ressaltar que se a posição digitada pelo ususario for uma parede(#), a posição de inicio sera gerada aleatoriamente ate que seja uma posição aceita pelo programa, as exeções são: se forem paredes ou entao se for a ultima linha ou ultima coluna.   
<li>É criado uma matriz de string auxiliar que sera nela que usaremos durante todo nosso codigo para armazenarmos as lidas em seus arquivo e usa-las para percorrer</li>
<li>Depois de inicializado/tratado as execções se necessario, ja entramos em nosso looping iterativo(linha X), ele possi como condição de parada as vidas estarem a baixo de zero, pois assim significa que voce morree</li>
<li></li>
<li></li>
<li></li>
<li></li>
<li></li>
</ul>

<strong>Explicação detalhada da função 'PercorrerMatriz':</strong>
<ul>
<li></li>
<li></li>
<li></li>
<li></li>
<li></li>
<li></li>
<li></li>
</ul>

# Compilação e Execução

O codigo disponibilizado foi criado e executado em notebook Acer core i5 Aspire M com sistema operacional Windowns 10 e utlizado um terminal de comando com WSL.

O codigo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |
