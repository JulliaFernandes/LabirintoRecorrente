# LabirintoRecorrente
[![requirement](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-informational)](https://code.visualstudio.com/docs/?dv=linux64_deb)
![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue)<br>
<strong>Atividade realizada no 3º periodo para a disciplina de Algoritmos e Estrutura de Dados.</strong>

# Sumário

- [Objetivos](#Objetivos)
- [Problema apresentado](#Problema-apresentado)
- [Arquivos](#Arquivos)
- [Resolução do Problema](#Resolução-do-problema)
- [Exemplifição](#Exemplificação)
- [Pergunta](#Pergunta)
- [Resultados esperados](#Resultados-esperados)
- [Conclusão](#Conclusão)
- [Compilação e Execução](#Compilação-e-Execução)
- [Contato](#Contato)


## Objetivos
O objetivo dessa atividade é propor o desenvolvimento de um algoritmo que permita ao personagem chegar ao final de um labirinto fazendo todo seu caminho ser vazio, entretanto ha desafios pelo caminho que devem ser tratados e que pode levar o pesonagem nao cumprir sua missão.<br>
Algumas condições sao impostas para o bom funciomanto de codigo:
 - Todas as matrizes devem estar contidas no arquivo `input.data`;
 - A primeira linha do arquivo `input.data` deve conter o tamanho da matriz e a quantidade existente, seguindo esse modelo: ' 5 5 3';
   - Todas as matrizes devem ser quadradas.<br>
 - Necessidade de possuir ao mínimo uma matriz de numeros inteiros entre 0 e 9 e somente dois tipos de caracteres são permitidos:
    - '#' -Representa parede
    - '*' -Representa perigo

## Problema apresentado
- Um garoto se encontra perdido em um labirinto, o qual é compreendido por nós como sendo uma matriz cujas posição de sua localização é dada por um valor x,y dessa estrutura. Nesse labirinto há paredes que bloqueiam certos passos (#), perigos que consomem parte de sua vida (*) e trajetórias (valores positivos que devem ser subtraídos em 1 a cada passagem).
- Ao decorrer do jogo, a cada passo correto sob uma estrada, o garoto consome um item, subtraindo esse do valor que compõe a posição x,y. Gravando nessa o valor resultante. A cada subtração bem sucedida é preciso, essa vai para um banco de vida que cheio (a cada 4 ações bem sucedidas) lhe retorna 1 de vida em seu contador. Contudo, pode haver partes do caminho com zero itens, esses devem continuar sendo utilizados, porém, sem computar pontuação.
- Sua missão é percorrer as matrizes até que todo o caminho percorrido pelo garoto se torne zero ou que ele venha a morrer devido aos perigos enfrentados.

## Arquivos
<strong>Main.cpp:</strong> É feito a chamada inicialmente de uma função que ira retornar o tamanho da matriz presente no arquivo input.data e quantas matriz possuem nesse arquivo, é feita tambem a chamada das tres funções principais do funcionamento do codigo, `LerArquivo`, `StartJogo` e `PercorrerMatriz`, é nela em que todo nosso codigo sera executado.<br>
<strong>Labirinto.hpp:</strong> Onde é criada todas as nossas funções que serão executadas no decorrer do algoritmo.<br>
<strong>Labirinto.cpp:</strong> Onde é feita a estruturação de todas as funções criadas e onde sera desenvolvido todo o codigo.<br>
<strong>Terminal:</strong> Aparece ao usuario, o total de casas percorridas durante a execução do codigo, o total de itens coletados, o total de perigos enfrentados, o numero de posições que foram visitadas e quantas posiçoes nao foram acessadas durante o percurso gerado pelo codigo.<br>
<strong>dataset/input.data:</strong> Arquivo contendo o tamanho da matriz, a quantidade matrizes, e as matrizes que serão utlizadas.<br>
<strong>dataset/output.data:</strong> Arquivo contento todas as matrizes, as que foram modificadas ou não, para fins visuais de quais posições foram percorridas.

## Resolução do problema 
As funções principais que fazem o funcionamento do codigo sao: `LerArquivo`, `StartJogo` e `PercorrerMatriz`, são nelas que é feita toda a implementação do desenvolvimento do codigo, cumprimindo todas as codiçoes passadas pelo professor.<br>

<strong>Explicação detalhada da função 'LerArquivo':</strong>

- É feita a abertura do arquivo input.data, pois é nela que esta armazenado todas as nossas matrizes que usaremos durante todo o nosso jogo.</li>
- O arquivo input.data é lido de maneira que a cada linha vazia vista, é sinal de que toda uma matriz foi percorrida, e desse modo podemos salvar essa matriz lida em um arquivo que contera somente ela.
   - Nesse codigo, a fim de melhorar o desempenho e nao ocupar tanta memoria RAM, foi adotado que cada matriz presente no arquivo orignal, tera um arquivo contendo somente ela.
- Esse arquivo unico de cada matriz é feito na função `CriandoArquivoParaCadaMatriz`(linha X) na qual cada arquivo recebera um nome diferente, basedo na sua matriz correspondente, ou seja, para a primeira matriz lida, o nome de seu arquivo sera: 'dataset/matriz1.data'<br>

<strong>OBS:</strong> Todos os arquivos de matrizes criados ficaram salvos na pasta dataset, que ao final do jogo todas elas seram excluidas para liberação de memoria.


<div align="center">
  <img src="/imgs/ArquivosCriados_Exemplo.PNG" alt="Pasta Dataset">
  <p align="center"><em> Exemplificação pasta dataset </em></p>
</div>

<strong>Explicação detalhada da função 'Startjogo':</strong><br>
De maneira geral nessa função é feita a abertura do arquivo que contem a matriz a ser percorrida no momento, é chamado a função que ira percorrer a matriz e é onde é feito a analise do numero de vidas se devemos ou não continuar no jogo e por fim é nela que nos teletrasportamos para a proxima matriz.

- É pedido ao usuario que digite o numero da posição inical em que deseja começar o jogo
  - importante ressaltar que se a posição digitada pelo ususario for uma parede(#), a posição de inicio sera gerada aleatoriamente ate que seja uma posição aceita pelo programa, as exeções são: se forem paredes ou entao se for a ultima linha ou ultima coluna, sendo as duas ultimas, as condiçoes de teletranspote de uma matriz para a outra. O jogo só começará se tudo isso for cumprido.
- É criado uma matriz de string auxiliar que sera ela que usaremos durante todo nosso codigo para armazenarmos as matrizes lidas de seus respectivos arquivos e usa-las para percorrer
- Uma variavel recebera os nomes, um por vez e em sequencia, do vetor que armazena o nome de todos os arquivos criados para as matrizes, pois é essa variavel que fara o controle de qual arquivo de matriz estamos e qual sera a matriz alterada durante o percurso.
- Se todos os criterios acima estiverem de acordo, começamos o jogo, chamando a função `PercorrerMatriz`(linha X)
- Apos feito todo o percurso de nossa matriz, a mesma se encontra diferente de antes logo ela deve ser passada para o seu arquivo ja modificada, para isso chamamos a função `PassaNovaMatrizParaArquivo`(linha X)
- Logo apos a chamada da função de percorrer é visto tambem se nossa vida acabou, pois se sim, devemos parar o codigo e informar ao usuario que o jogo foi finalizado e que ele chegou ao nivel zero de vidas.
- Por fim a função é atualizada para proseguirmos para o proximo arquivo e faremos os mesmos passos se tudo continuar sendo cumprido.
- Essa iteração ocorre enquanto tivermos vida, ou se o todo o caminho feito ainda possuir itens a serem coletados.<br>
  <!-- - <strong>Importante:</strong> a decisao para qual matriz o personagem sera teletransportado é feita de modo sequencial, ou seja seguimos a ordem das matrizes que foram lidas do arquivo `input.data`, se chegado a ultima matriz do arquivo voltamos a primeira matriz. 
  - O criterio de decição para começar uma nova matriz é sempre a posição inicial em que começou o jogo, se a posição for alterada devido a existencia de parede as matrizes seguintes iram começar com essa nova posição. -->


<strong>Explicação detalhada da função 'PercorrerMatriz':</strong><br>
Essa função tem como criterio de decisão qual direção o usuario ira, feita por switch's, sendo cada 'case' uma direção possivel.

- Assim que inicializado essa função, a posição em que o personagem se encontra ja sofrerá mudanças, ate mesmo a posição inical em que o usuario começa o jogo.
- Ela é realizada por um loop que somente se atingirmos a posicao que nos levara a outra matriz ou entao se nossa vida chegar a zero, ele é parado. (Os criterios de teletransporte ja foram explicados acima)
- É gerado um numero randomico entre 0 a 7 e que cada um representara a decisao de direção a ser seguida.
- É tratado os casos de extremidades da matriz, quando gerado um numero em que a posição nao é possivel ser seguida, que é a existencia de parede(#), é gerado um outro numero aleatorio ate que seja possivel o personagem se mover.
- É visto se a posição em que o personagem irá é um perigo(*) ou um item(numeros de 0 a 9), se em caso de perigo, o personagem sofre um dano em sua vida e perde uma, se em caso de item, ele recebe um item que ira para sua mochila e o numero naquela posição diminui em 1 unidade.
   - Sempre que a mochila chega a 4 itens, os itens sao trocados em 1 vida e é zerada a mochila novamente, para os casos em que a vida ja esteja totalmente cheia, nada ocorre à vida mas sua mochila será zerada.
   - Se a posição em que se encontra ja estiver zerada, nada mais ocorre a ela.

<p align="center">
<strong><em>Direçãoes possiveis em cada 'case' presente no switch </em></strong>
</p>

<table border="1" align="center">
  <tr>
      <td><strong>Case</strong></td>
      <td><strong>Direção</strong></td>
  </tr>
  <tr>
      <td>0</td>
      <td>Direta</td>
  </tr>
  <tr>
      <td>1</td>
      <td>Esquerda</td>
  </tr>
  <tr>
      <td>2</td>
      <td>Cima</td>
  </tr>
  <tr>
      <td>3</td>
      <td>Baixo</td>
  </tr>
  <tr>
      <td>4</td>
      <td>Diagonal esq. sup.</td>
  </tr>
  <tr>
      <td>5</td>
      <td>Diagonal dir. sup.</td>
  </tr>
  <tr>
      <td>6</td>
      <td>Diagonal esq. inf.</td>
  </tr>
  <tr>
      <td>7</td>
      <td>Diagonal dir. inf.</td>
  </tr>
</table>

<h3>Informações importantes</h3>
<ul>
   <li>A decisao para qual matriz o personagem sera teletransportado é feita de modo sequencial, ou seja seguimos a ordem das matrizes que foram lidas do arquivo `input.data`, se chegado a ultima matriz do arquivo voltamos a primeira matriz.</li>
   <li>O criterio de decição para a posição inicial de uma nova matriz é sempre a posição inicial em que começou o jogo, se a posição for alterada devido a existencia de parede as matrizes seguintes iram começar com essa nova posição.</li>
   <li>É criado um arquivo 'output.data' que ira armazenar todas as matrizes modificadas ou nao ao final do jogo, dessa maneira o usuario poderá comparar com as matrizes presente no arquivo 'input.data' e ver as posições que foram acessadas pelo personagem</li>
 <li>É tratado quando o personagem se teltransporta para uma nova matriz se a posição inicial em que se encontra, se em seu entorno possui somente paredes, pois se possuir é gerado uma nova posição para o mesmo iniciar</li>
   <li>Na função 'Vida' é necessária indicar o tipo de ação que irá ocorrer com ela. A tabela abaixo exemplifica o que cada número significa:</li>
</ul>
    
<div align="center">

| Ação             |  Função                                                 |                     
| -----------------| --------------------------------------------------------|
| '-1'             | Diminiu a vida em 1 unidade                             |
| '0'              | Somente para fins de obtenção da situação da vida       |
| '1'              | Adicionar 1 unidade à vida                              |

<li>Outros valores diferentes dos mostrados na tabela podem levar ao mal funcionamento do código.</li>
</div>

## Exemplificação
Nesse gif é possivel observar o funcionamento do codigo de uma maneira mais visual.<br>
Acontecimentos:
<ul>
<li>Matriz inicial sem mudanças e o nome de seu arquivo</li>
<li>Posição escolhida pelo usuario impossivel devido a existencia de parede.</li>
<li>Gerou uma nova posição aleatoria para começar, devido ao item acima;</li>
<li>Posição gerada pelo switch impossivel de ir devido a parede(#);</li>
<li>Perde vida ao enfrentar um perigo;</li>
<li>Mochila aumentando de item e as posições diminuindo;</li>
<li>Mochila no maximo e fazendo a trocando por vida, logo apos esvaziando a mochila;</li>
<li>Chegando a extremidade da matriz e finalizando a função ja que irá se teletransportar a outra matriz</li>
</ul>

<p align="center">
<img src="/imgs/gif_maze.gif" alt="Gif Maze">
</p>

## Pergunta
<h3>Qual o custo computacional da sua estratégia randômica? Se mostrou uma boa alternativa de execução?</h3>
    Conclui-se que o custo do algoritmo é inclusivo, devido ao fato de ser um o algoritmo do tipo randômico, tornando impossível o calculo do custo. Mas é possível usar o cálculo do tempo gasto para executar o algoritmo como uma medida aproximada de seu desempenho. Uma técnica comum para isso é a execução repetida do algoritmo com a mesma entrada de dados, a presente no arquivo inpput.data, e o cálculo da média do tempo gasto, com isso baseado em 10 execuções do codigo foi possível obter uma média de tempo para compilação de 2.2 segundos.

<!-- 
## Custo Computacional
O custo desse algoritmo é inclusivo devido ao algoritmo ser do tipo randomico oque se torna impossivel o calculo do custo visto que a cada hora que rodamos o valor poderá ser alterado e dessa forma nao se pode calcular o custo do mesmo. Entretanto foi feito o calculo do tempo gasto para a compilação do codigo esse valor é de:  2.2 segundos, essse valor foi obtido pelo calculo da media do resultado de tempo gasto para  a cada compilação do programa com a mesma entrada de dados, a presente no arquivo input.data, que foi analisada 10 vezes. 
-->

## Resultados esperados 
É esperado que apareça ao usuarios todas essas informções referentes a missão do personagem e ao caminho que ele percorreu, dizendo se ele conseguiu cumprir sua missão ou se morreu tentando, tudo a respeito do que foi enfrentado e percorrido durante o jogo e o tempo que foi gasto para ser rodado esse algoritmo.
<p align="center">
<img src="/imgs/Terminal.png" alt="Terminal Usuario">
</p>

## Conclusão 
Foi possivel concluir com essa atividades novas formas de implementação de caminhamento por matrizes, alem de desenvolviemnto de melhores estrategias para ajudar ao personagem a concluir sua missão, que é concluir um caminho completamente de zeros, sua implementação foi feita de modo que economize memoria ao usuario que esta jogando, graças aos conhecimentos obtidos sobre problemas que poderiam ocorrer no decorrer da atividade como por exemplo estouro de memoria ao analisarmos uma matriz muito grande, discutidas em aula,  e foram aplicados estrategias para um melhor desenvolvimento do codigo, por mais de que tenha um custo mais caro de memoria,devido a criação de arquivos para cada matriz, esse algorimo se torna melhor no desempenho visto que se pode analisar matrizes muito grandes sem problemas à dificuldade de leitura, foi possivel tambem concluir que nao ha meios de calcular o custo de algoritmos randomicos entao uma outra opção de exemplificação do custo seria mostrando o tempo de execução. 

## Compilação e Execução

O codigo disponibilizado foi criado e executado em notebook Acer core i5 Aspire M com sistema operacional Windowns 10 e utlizado um terminal de comando com WSL.

O codigo possui um arquivo Makefile que realiza todo o procedimento de compilação e execução. Para tanto, temos as seguintes diretrizes de execução:


| Comando                |  Função                                                                                           |                     
| -----------------------| ------------------------------------------------------------------------------------------------- |
|  `make clean`          | Apaga a última compilação realizada contida na pasta build                                        |
|  `make`                | Executa a compilação do programa utilizando o g++, e o resultado vai para a pasta build           |
|  `make run`            | Executa o programa da pasta build após a realização da compilação                                 |

## Contato
<div>
 <p align="justify"> Jullia Fernandes</p>
 <a href="https://t.me/JulliaFernandes">
 <img align="center" src="https://img.shields.io/badge/Telegram-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white"/> 
 </div>

<a style="color:black" href="mailto:julliacefet@gmail.com?subject=[GitHub]%20Source%20Dynamic%20Lists">
✉️ <i>julliacefet@gmail.com</i>
</a>
