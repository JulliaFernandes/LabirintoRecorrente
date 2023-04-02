#include "labirinto.hpp"

using namespace std;

vector<string> nomesDosArquivos;
bool CaminhoEhVazio=true;
bool comeco=true;
bool passouTodasMatrizes=false;
int inicioLinha, inicioColuna;

tuple<int, int> PosicaoInicial(int linha, int coluna, int tam_matriz)
{
    cout << "Qual posição deseja começar: " << endl
         << ">";
    cin >> linha;
    cout << ">";
    cin >> coluna;
    while (coluna >= tam_matriz || coluna < 0 || linha >= tam_matriz || linha < 0)
    {
        cout << "Posição invalida. Digite somente valores entre 0 e " << tam_matriz - 1 << endl;
        cout << "Qual posição deseja começar: " << endl
             << ">";
        cin >> linha;
        cout << ">";
        cin >> coluna;
    }

    return make_tuple(linha, coluna);
}

tuple<int, int> LePrimeraLinha()
{
    ifstream arquivo;
    string linha, valor_str, aux_str, elemento, qtdMatriz_str;
    int aux = 0, tam = 0, cont = 0, qtdMatriz, cont2 = 0;

    arquivo.open("dataset/input.data", ios::in);
    // while(cont == 0){
    while (getline(arquivo, linha, '\n'))
    {
        if (cont == 0)
        {
            stringstream aux_str(linha);
            while (getline(aux_str, elemento, ' '))
            {
                if (aux == 2)
                {
                    if (cont2 == 0)
                    {
                        qtdMatriz_str = elemento;
                        qtdMatriz = atoi(qtdMatriz_str.c_str());
                        cout << ">QTD MATRIZ: " << qtdMatriz << endl;
                        cont2++;
                    }
                }
                else
                {
                    valor_str = elemento;
                    tam = atoi(valor_str.c_str());
                    aux++;
                    cout << "TAM: " << tam << endl;
                }
            }
            cont++;
        }
    }
    // }
    arquivo.close();
    return make_tuple(tam, qtdMatriz);
}

bool linhaVazia(const string &linha)
{
    for (char c : linha)
    {
        if (!isspace(c))
        {
            // Se o caractere não for espaço em branco, a linha não está vazia
            return false;
        }
    }
    // Se todos os caracteres forem espaços em branco, a linha está vazia
    return true;
}

void LerArquivo(string **matriz, int tam_matriz, int qtd_matriz)
{
    ifstream arquivo;
    string linha_arq, elemento;
    int aux_linha = 0, aux_coluna = 0, aux_tam = 0;
    // int linha=0, coluna=0;
    int i = 0;

    // tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    // out << "Posição inicial [" << linha << "]" << "[" << coluna << "]" <<endl;

    arquivo.open("dataset/input.data", ios::in);

    while (!arquivo.eof())
    {
        while (getline(arquivo, linha_arq, '\n'))
        {
            if (aux_tam == 0)
            {
                aux_tam++;
            }
            else
            {
                if (linhaVazia(linha_arq))
                {
                    // cout << "---------------------------------------------";
                    // cout << "\n\t---Nova Matriz---" << endl;
                    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
                    // ImprimirMatriz(matriz, tam_matriz);
                    aux_coluna = 0;
                    aux_linha = 0;
                }
                else
                {
                    // está criando um fluxo de caracteres para que a função getline possa ler e manipular os dados
                    stringstream aux(linha_arq);

                    // lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                    while (getline(aux, elemento, ' '))
                    {
                        if (aux_coluna < tam_matriz && aux_linha < tam_matriz)
                        {
                            matriz[aux_linha][aux_coluna] = elemento;
                            aux_coluna++;
                        }
                    }

                    if (aux_coluna > 0 && aux_linha < tam_matriz)
                    {
                        aux_linha++;
                        aux_coluna = 0;
                    }
                }
            }
        }
    }
    arquivo.close();

    // cout << "---------------------------------------------";
    // cout << "\n\taa---Nova Matriz---" << endl;
    CriandoArquivoParaCadaMatriz(matriz, tam_matriz, qtd_matriz, i);
    // ImprimirMatriz(matriz, tam_matriz);
}

void ImprimirMatriz(string **matriz, int tam_matriz)
{
    cout << endl;
    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
}

void PercorrerMatriz(string **matriz, int linha, int coluna, int tam_matriz, int &vida, int &totalCasas, int &totalItens, int &totalPerigo, int &qtdCasasNaoAndadas, string Nome1Arquivo, int& mochila)
{
    srand(42);

    int linha_aux = linha, coluna_aux = coluna;
    int acao = 0, i=0, contVezesEntradas=0;
    bool auxVida = Vida(vida, acao);
    //string ArquivoPrimeiro = nomesDosArquivos[i];
    // caminho=false;
    // bool auxCaminho=false;

    // cout << "\n\t---Matriz Inicial---" << endl;
    // ImprimirMatriz(matriz, tam_matriz);
    // cout << endl;

    while (linha_aux < tam_matriz && coluna_aux < tam_matriz && auxVida != false){
        //comeco=false;
        cout << ">>Posição atual[" << linha_aux << "]" << "[" << coluna_aux << "]" << endl;
        if (linha_aux != tam_matriz - 1 && coluna_aux != tam_matriz - 1){   
            if(contVezesEntradas!=0){
                if(Nome1Arquivo == nomesDosArquivos[i] && linha_aux == inicioLinha && coluna_aux == inicioColuna){
                    comeco=true;
                    cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
                }
            }
            contVezesEntradas++;
            int direcaoAleatoria = rand() % 8;
            cout << "Numero aleatorio: " << direcaoAleatoria << endl << endl;

            switch (direcaoAleatoria){
                case 0: // irei para direita;
                    if(coluna_aux < tam_matriz - 1 && matriz[linha_aux][coluna_aux + 1] != "#"){
                        if (matriz[linha_aux][coluna_aux + 1] == "*"){
                            coluna_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            acao = -1;
                            Vida(vida, acao);
                            cout << "Vida: " << vida << endl << endl;
                            TotalDePerigosEnfrentados(totalPerigo);
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            coluna_aux++;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, voce ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl << endl;
                            }
                            else
                            { // o valor nessa casa é igual de zero
                                
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    // cout << "----------------------------VALOR BOLL CAMINHOVAZIO: " << caminhoVazio << endl;
                    break;

                case 1: // irei para a esquerda
                    if (coluna_aux > 0 && matriz[linha_aux][coluna_aux - 1] != "#"){
                        if (matriz[linha_aux][coluna_aux - 1] == "*"){
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            acao = -1;
                            Vida(vida, acao);
                            cout << "Vida: " << vida << endl << endl;
                            TotalDePerigosEnfrentados(totalPerigo);
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            coluna_aux--;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 2: // irei para cima
                    if (linha_aux > 0 && matriz[linha_aux - 1][coluna_aux] != "#"){
                        if (matriz[linha_aux - 1][coluna_aux] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl
                                << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            linha_aux--;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl
                                    << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 3: // irei para baixo
                    if (linha_aux < tam_matriz - 1 && matriz[linha_aux + 1][coluna_aux] != "#"){
                        if (matriz[linha_aux + 1][coluna_aux] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl
                                << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é numero
                            linha_aux++;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl
                                    << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 4: // irei para diagonal-esquerda-superior
                    if (linha_aux != 0 && coluna_aux != 0 && matriz[linha_aux - 1][coluna_aux - 1] != "#"){
                        if (matriz[linha_aux - 1][coluna_aux - 1] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux--;
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl
                                << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            linha_aux--;
                            coluna_aux--;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl
                                    << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 5: // irei para a diagonal-direita-superior
                    if (linha_aux != 0 && coluna_aux != tam_matriz - 1 && matriz[linha_aux - 1][coluna_aux + 1] != "#"){
                        if (matriz[linha_aux - 1][coluna_aux + 1] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux--;
                            coluna_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl
                                << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            linha_aux--;
                            coluna_aux++;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl
                                    << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 6: // irei para a diagonal-esquerda-inferior
                    if (linha_aux != tam_matriz - 1 && coluna_aux != 0 && matriz[linha_aux + 1][coluna_aux - 1] != "#"){
                        if (matriz[linha_aux + 1][coluna_aux - 1] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux++;
                            coluna_aux--;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl
                                << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é um numero
                            linha_aux++;
                            coluna_aux--;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;

                case 7: // irei para a diagonal-direita-inferior
                    if (linha_aux != tam_matriz - 1 && coluna_aux != tam_matriz - 1 && matriz[linha_aux + 1][coluna_aux + 1] != "#"){
                        if (matriz[linha_aux + 1][coluna_aux + 1] == "*"){
                            acao = -1;
                            Vida(vida, acao);
                            TotalDePerigosEnfrentados(totalPerigo);
                            linha_aux++;
                            coluna_aux++;
                            ImprimirMatriz(matriz, tam_matriz);
                            cout << "Vida: " << vida << endl << endl;
                            CasasPercorridasAoTodo(totalCasas);
                        }
                        else{ // é pq é numero
                            linha_aux++;
                            coluna_aux++;
                            CasasPercorridasAoTodo(totalCasas);
                            if (matriz[linha_aux][coluna_aux] != "0"){
                                MudaValorCaminho(matriz, linha_aux, coluna_aux);
                                mochila++;
                                TotalDeItensConsumidos(totalItens);
                                CaminhoEhVazio=false;
                                if (mochila == 4){
                                    if (vida < 10){
                                        cout << "\n>Mochila: " << mochila << endl;
                                        cout << "Mochila atingiu seu limite, ganhou uma vida" << endl;
                                        int acao_aux;
                                        acao_aux = 1;
                                        cout << "vida antes: " << vida << endl;
                                        Vida(vida, acao_aux);
                                        cout << "vida depois: " << vida << endl;
                                    }
                                    mochila = 0;
                                }
                                ImprimirMatriz(matriz, tam_matriz);
                                cout << "Mochila: " << mochila << endl << endl;
                            }
                            else
                            {
                            }
                        }
                        CasasNaoPercorridas(qtdCasasNaoAndadas);
                    }
                    acao = 0;
                    auxVida = Vida(vida, acao);
                    break;
            }
            cout << "--------------------------------CAMINHO È VAZIO::::::: " << CaminhoEhVazio << endl << endl;
            cout << "--------------------------------COMECO::::::: " << comeco << endl << endl;
        }
         else{ // estou ou na ultima linha ou na ultima coluna, e devo me teletransportar para a nova matriz
         // preciso so chamar para ir pro proximo. 
            break;
        }
        /* if(contVezesEntradas!=0){
                if(Nome1Arquivo == nomesDosArquivos[i] && linha_aux == inicioLinha && coluna_aux == inicioColuna){
                    comeco=true;
                    cout << "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa" << endl;
                }
        } */
    }
}

void CriandoArquivoParaCadaMatriz(string **matriz, int tam_matriz, int qtd_matriz, int &i)
{
    string PATH = "dataset/";
    string nomeArquivo;
    string numeroArquivo_str;
    int numeroArquivo;
    stringstream aux;
    cout << "NUMERO I: " << i << endl;
    cout << "QTD_MAtriz" << qtd_matriz << endl;
    if (i < qtd_matriz)
    {
        numeroArquivo = i + 1;
        aux << numeroArquivo;
        numeroArquivo_str = aux.str();
        nomeArquivo = PATH + "matriz" + numeroArquivo_str + ".data";
        nomesDosArquivos.push_back(nomeArquivo);
        aux.str("");
        i++;
    }
    cout << "Nome: " << nomeArquivo << endl;

    ofstream arquivo;
    arquivo.open(nomeArquivo, ios::out);
    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            arquivo << matriz[i][j] << " ";
        }
        arquivo << endl;
    }
    arquivo.close();
}

void StartJogo(int linha, int coluna, int tam_matriz, int qtd_matriz, int &vida)
{
    ifstream arquivo_leitura;
    string linha_arq;
    string nomeArquivo, elemento, nome1arquivo;
    int i = 0, aux_linha = 0, aux_coluna = 0, acao = 0;
    bool auxVida = Vida(vida, acao);
    int mochila=0;
    int cont_1vez = 0, totalCasas = 0, totalItens = 0, totalPerigo = 0, qtdCasas = 0;

    qtdCasas = CasasTotal(tam_matriz, qtd_matriz);
    nome1arquivo=nomesDosArquivos[i];

    string **matriz_aux = new string *[tam_matriz];
    for (int i = 0; i < tam_matriz; i++)
    {
        matriz_aux[i] = new string[tam_matriz];
    }

    tie(linha, coluna) = PosicaoInicial(linha, coluna, tam_matriz);
    cout << "Posição inicial [" << linha << "]" << "[" << coluna << "]" << endl;
    inicioLinha = linha;
    inicioColuna = coluna;

    while (auxVida == true)
    {
        cout << "aaaaa" << endl; // ainda nao morri e ainda tem lugar pra passar
        if(passouTodasMatrizes && comeco && i==qtd_matriz){ 
            cout << "ENTRIE NO IF 3 LLLLLLLLLLLLLLLLLLLLLL" << endl;//se passou em todas as matrizes se passou na posição inicial
            if(CaminhoEhVazio==true){
                cout << "CAMINHO ZERADO. VOCE CHEGOU AO FINAL DO JOGO, PARABENS :) !!" << endl;
                break;
            }
            cout << "ENTROOU AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII " << endl;
            CaminhoEhVazio=true;
        }
        if (i == qtd_matriz)
        {   
            cout << "PASOUUUUUUUUUUUUUUUUUUUUUUUUUUU" << endl;
            passouTodasMatrizes=true;
            i = 0;
        }
        /* if(passouTodasMatrizes && comeco && i==qtd_matriz){ //se passou em todas as matrizes se passou na posição inicial
            if(CaminhoEhVazio==true){
                cout << "CAMINHO ZERADO. VOCE CHEGOU AO FINAL DO JOGO, PARABENS :) !!" << endl;
                break;
            }
            cout << "ENTROOU AQUIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIII " << endl;
            CaminhoEhVazio=true;
        }*/
        nomeArquivo = nomesDosArquivos[i];
        i++;

        cout << "NOME ARQUIVO: " << nomeArquivo << endl;
        // cout << "CONT1Vida: " << cont_1vez << endl;
        arquivo_leitura.open(nomeArquivo, ios::in);
        while (!arquivo_leitura.eof())
        {
            while (getline(arquivo_leitura, linha_arq, '\n'))
            {
                stringstream aux(linha_arq);
                while (getline(aux, elemento, ' '))
                { // lendo a cada elemento presente na minha linha armazena para minha variavel elemento e tendo o delimitador ''
                    if (aux_coluna < tam_matriz && aux_linha < tam_matriz)
                    {
                        matriz_aux[aux_linha][aux_coluna] = elemento;
                        aux_coluna++;
                    }
                }

                if (aux_coluna > 0 && aux_linha < tam_matriz)
                {
                    aux_linha++;
                    aux_coluna = 0;
                }
            }
        }
        arquivo_leitura.close();
        aux_coluna = 0;
        aux_linha = 0;

        // ImprimirMatriz(matriz_aux, tam_matriz);
        if (cont_1vez == 0)
        { // mantem a primeira vez que a pessoa digitou.
            cont_1vez++;
            PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida, totalCasas, totalItens, totalPerigo, qtdCasas, nomeArquivo, mochila);
            auxVida = Vida(vida, acao);
            PassaNovaMatrizParaArquivo(matriz_aux, nomeArquivo, tam_matriz);
        }
        else
        {
            // cout << ">>>Posição[" << linha << "]" << "[" << coluna << "]" <<endl;
            if (matriz_aux[linha][coluna] == "#" || linha == tam_matriz-1 || coluna == tam_matriz-1)
            {   
                cout << "AAAAAAAAAAAAAAAA" << endl;
                while (matriz_aux[linha][coluna] == "#" || linha == tam_matriz-1 || coluna == tam_matriz-1)
                {
                    linha = rand() % tam_matriz;
                    coluna = rand() % tam_matriz;
                    cout << "Posição inicial mudada [" << linha << "]" << "[" << coluna << "]" << endl;
                }
                PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida, totalCasas, totalItens, totalPerigo, qtdCasas, nomeArquivo, mochila);
                auxVida = Vida(vida, acao);
                PassaNovaMatrizParaArquivo(matriz_aux, nomeArquivo, tam_matriz);
            }
            else
            {
                PercorrerMatriz(matriz_aux, linha, coluna, tam_matriz, vida, totalCasas, totalItens, totalPerigo, qtdCasas, nomeArquivo, mochila);
                auxVida = Vida(vida, acao);
                PassaNovaMatrizParaArquivo(matriz_aux, nomeArquivo, tam_matriz);
            }
            // cout << ">>>Posição[" << linha << "]" << "[" << coluna << "]" <<endl;
        }
        // cout << "----------------------------------------------------------" << endl;
        // ImprimirMatriz(matriz_aux, tam_matriz);
    }
    cout << "\n\n>TOTAL DE CASAS PERCORRIDAS: " << totalCasas << endl;
    cout << ">TOTAL DE ITENS CONSUMIDOS: " << totalItens << endl;
    cout << ">TOTAL DE PERIGOS ENFRENTADOS: " << totalPerigo << endl;
    cout << ">QUATIDADE DE CASAS NAO VISITADAS: " << qtdCasas << endl;
    // ExcluiArquivosCriados(qtd_matriz);
}

bool Vida(int &vida, int acao)
{
    if (vida > 1)
    {
        if (acao == 1){ // é porque vou ganhar vida
            vida++;
            return true;
        }
        else if (acao == 0){ // é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            return true; // ainda tenho vida
        }
        else{ // perdendo vida, acao é -1;
            vida--;
            // return false;
            return true;
        }
    }
    else{ // vida em 1 ai, vejo se vou morrer ou ganhar mais vida
        if (acao == 1){
            vida++;
            return true;
        }
        else if (acao == 0){ // é so para saber se ainda tenho vida, feito para usar na funçao de startjogo
            if (vida != 0){
                return true; // ainda tenho vida
            }
            else{
                return false;
            }
        }
        else{ // é pq é -1 a minha vida e vou morrer
            vida--;
            cout << "Voce morreu :(" << endl;
            return false;
        }
    }
}

void MudaValorCaminho(string **matriz, int linha, int coluna)
{
    string valorCaminho_str;
    int valorCaminho;
    stringstream aux;

    valorCaminho_str = matriz[linha][coluna];
    valorCaminho = atoi(valorCaminho_str.c_str());
    valorCaminho--;
    aux << valorCaminho;
    valorCaminho_str = aux.str();
    aux.str("");
    matriz[linha][coluna] = valorCaminho_str;
}

void PassaNovaMatrizParaArquivo(string **matriz, string nomeArq, int tam_matriz)
{
    ofstream arquivo_escrita;

    arquivo_escrita.open(nomeArq, ios::out);
    for (int i = 0; i < tam_matriz; i++)
    {
        for (int j = 0; j < tam_matriz; j++)
        {
            arquivo_escrita << matriz[i][j] << " ";
        }
        arquivo_escrita << endl;
    }
    arquivo_escrita.close();
}

void ExcluiArquivosCriados(int qtd_matriz)
{
    for (int i = 0; i < qtd_matriz; i++)
    {
        char nomeArquivoRemovido[100];
        strcpy(nomeArquivoRemovido, nomesDosArquivos[i].c_str());
        // remove(nomeArquivoRemovido);
        int resultado = remove(nomeArquivoRemovido);
        if (resultado != 0)
        {
            perror("Erro ao excluir arquivo");
        }
    }
}

void CasasPercorridasAoTodo(int &total)
{
    total++;
}

void TotalDeItensConsumidos(int &total_itens)
{
    total_itens++;
}

void TotalDePerigosEnfrentados(int &totalPerigo)
{
    totalPerigo++;
}

int CasasTotal(int tam_matriz, int qtd_matriz)
{
    int qtdCasasNaoPercorridas = 0;
    qtdCasasNaoPercorridas = (tam_matriz * tam_matriz) * qtd_matriz;

    return qtdCasasNaoPercorridas;
}

void CasasNaoPercorridas(int &qtdCasasNaoPercorridas)
{
    qtdCasasNaoPercorridas--;
}

//void MudaPosicaoAtual(string **matriz, int acaoLinha, int acaoColuna);


/* bool CaminhoVazio(bool &caminho)
{
    if (caminho == false)
    {
        caminho = false;
        return caminho;
    }
    else
    {
        caminho = true;
        return caminho;
    }
} */