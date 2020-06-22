#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <time.h>

//TAMANHO MAXIMO DO MUNDO
#define M 10
#define N 10

//ALGUNS ESTADOS - ADICIONE QUANTOS DESEJAR
#define ANDAR_ALEATORIO 0
#define FUGIR 1
#define PERSEGUIR 2

using namespace std;

class Agente;
int tipoAgente(Agente* a);

//Representação do Mundo (Matriz de Agentes)
class Mundo {

public:

    Agente* matriz[M][N];

    //Inicializa o mundo atribuíndo NULL iniciamente para todas as células
    void inicializa() {
        cout << "inicializando mundo..." << endl;
        for (int i = 0; i < M; i++)
            for (int j = 0; j < N; j++)
                matriz[i][j] = NULL;
    }

    //Imprime a matriz de Agentes
    void imprimir() {
        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                cout << tipoAgente(matriz[i][j]) << " | ";
            }
            cout << endl;
        }
        cout << endl;
    }
    //TO-DO: IMPLEMENTE O MÉTODO QUE RECEBE O NOME DE UM ARQUIVO E CARREGUE OS DADOS/AGENTES NA MATRIZ
    void carregar(char* nome_arquivo) {

    }
    //TO-DO: IMPLEMENTE O MÉTODO QUE RECEBE O NOME DE UM ARQUIVO E SALVA OS DADOS/AGENTES EM UM ARQUIVO
    void salvar(char* nome_arquivo) {

    }
};


class Agente {

protected:
    int x;
    int y;
    int estado = 0; //Os agentes podem assumir diferentes estados. (ex. estado 1 = andar aleatoriamente)

public:

    int tipo = 0; //Define o tipo do agente (ex. tipo 1 = Gato)
    int getTipo() {
        return tipo;
    }
    Mundo* mundo;

    //Inicializa o agente no mundo com uma posição inicial
    void inicializa(Mundo* m, int x_inicial, int y_inicial) {
        x = x_inicial;
        y = y_inicial;
        mundo = m;
        mundo->matriz[y][x] = this;
    }

    //Verifica se o agente pode ir para uma nova posição
    bool podeMover(int novo_x, int novo_y) {

        if (mundo->matriz[novo_y][novo_x] == NULL)
            return true;
        return false;
    }

    void mover(int novo_x, int novo_y) {

        if (podeMover(novo_x, novo_y)) {
            mundo->matriz[y][x] = NULL;
            x = novo_x;
            y = novo_y;
            mundo->matriz[y][x] = this;
        }
    }

    int GetX() {
        return x;
    }
    int GetY() {
        return y;
    }
    void decidir();
    void executar();

    //TO DO: IMPLEMENTE O MÉTODO DE DESLOCAMENTO ALEATÓRIO.
    // CUIDADO PARA O AGENTE NÃO SOBREPOR OUTRO AGENTE OU CAIR FORA DO MUNDO/MATRIZ.
    void deslocarAleatorio() {

    }
};


class Presa : public Agente {

public:

    Presa() {
        estado = ANDAR_ALEATORIO;// Estado Inicial
        tipo = 1;
        cout << "Inicializando Presa | Tipo = " << tipo << endl;
    }

    //TO DO: IMPLEMENTE O ALGORITMO DE DECISAO DO AGENTE
    void decidir(int mPresa,int nPresa,int mPreda,int nPreda) {

        //TO DO: EXEMPLO DE UM AGENTE QUE SOBE E DESCE
        cout << "Estado Atual - Presa: " << estado << "| ";

        int mpp = mPresa - mPreda;
        int npp = nPresa - nPreda;
        if (mpp < 0)
            mpp *= -1;
        if (npp < 0)
            npp *= -1;

        if ((npp <= 2) && (mpp <= 2)) {
            estado = FUGIR;
        }
        else {
            estado = ANDAR_ALEATORIO;
        }
        cout << "Estado Escolhido - Presa: " << estado << endl;

        
    }

    //TO DO: IMPLEMENTE AQUI AS DECISÕES DO AGENTE - DEFINA OS ESTADOS ENVOLVIDOS
    void executar(int mPresa, int nPresa, int mPreda, int nPreda) {

        //TO DO: REFAZER - APENAS ILUSTRAÇÃO/EXEMPLIFICAÇÃO
        if (estado == FUGIR) {
            int xmover = nPresa - nPreda;
            int ymover = mPresa - mPreda;

            if (ymover > 0)
                ymover = 1;
            else
                ymover = -1;

            if (xmover > 0)
                xmover = 1;
            else
                xmover = -1;

            
            mover(x + xmover, y + ymover);
        }
        else if (estado == ANDAR_ALEATORIO) {
            int xmover = rand() % 3;
            int ymover = rand() % 3;

            if (xmover == 1)
                xmover = 1;
            else if (xmover == 2)
                xmover = -1;
            else
                xmover = 0;

            if (ymover == 1)
                ymover = 1;
            else if (ymover == 2)
                ymover = -1;
            else
                ymover = 0;

            mover(x + xmover, y + ymover);
        }
    }

    void fugir() {
        //TO-DO: EXEMPLO DE FUGA EM UMA UNICA DIREÇÃO. MELHORE ESSE COMPORTAMENTO.
        if (x < M - 1)
            mover(x + 1, y);
    }

};

class Predador : public Agente {

public:

    Predador() {
        estado = ANDAR_ALEATORIO;
        tipo = 2;
        cout << "Inicializando Predador | Tipo = " << tipo << endl;
    }

    //TO DO: IMPLEMENTE O ALGORITMO DE DECISAO DO AGENTE
    void decidir(int mPresa, int nPresa, int mPreda, int nPreda) {

        //TO DO: EXEMPLO DE UM AGENTE QUE VAI E VOLTA
        cout << "Estado Atual - Predador: " << estado << "| ";

        int mpp = mPreda - mPresa;
        int npp = nPreda - nPresa;
        if (mpp < 0)
            mpp *= -1;
        if (npp < 0)
            npp *= -1;

        if ( ( npp<=3) && (mpp <= 3)  ) {
            estado = PERSEGUIR;
        }
        else {
            estado = ANDAR_ALEATORIO;
        }

        cout << "Estado Escolhido - Predador: " << estado << endl;

    }


    //TO DO: IMPLEMENTE AQUI AS DECISÕES DO AGENTE - DEFINA OS ESTADOS ENVOLVIDOS
    void executar(int mPresa, int nPresa, int mPreda, int nPreda) {

        //TO DO: REFAZER - APENAS ILUSTRAÇÃO/EXEMPLIFICAÇÃO
        if (estado == PERSEGUIR) {
            int xmover = mPreda - nPresa;
            int ymover = nPreda - nPresa;
            
            if (ymover > 0)
                ymover = -1;
            else
                ymover = 1;

            if (xmover > 0)
                xmover = -1;
            else
                xmover = 1;


            mover(x + xmover, y + ymover);
        }
        else if (estado == ANDAR_ALEATORIO) {
            int xmover = rand() % 3;
            int ymover = rand() % 3;

            if (xmover == 1)
                xmover = 1;
            else if (xmover == 2)
                xmover = -1;
            else
                xmover = 0;

            if (ymover == 1)
                ymover = 1;
            else if (ymover == 2)
                ymover = -1;
            else
                ymover = 0;

            mover(x + xmover, y + ymover);
        }
    }

    //TO DO: IMPLEMENTE AQUI O COMPORTAMENTO DE PERSEGUIÇÃO DO AGENTE
    void perseguir() {

    }

};

int tipoAgente(Agente* a) {
    return a == NULL ? 0 : a->tipo;
}

int main()
{

    //srand (time(NULL));

    cout << "Bem vindo ao Quintal do felix e do bob!\n" << endl;

    Mundo mundo;
    mundo.inicializa();

    Presa presa;
    presa.inicializa(&mundo, 5, 5);

    Predador predador;
    predador.inicializa(&mundo, 1, 1);

    mundo.imprimir();

    int cont = 0;
    int p = 1;
    while (cont++ < 100 && p == 1) {

        //Agente Decide o vai fazer
        presa.decidir(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());
        //Agente Faz o que decidiu
        presa.executar(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());

        //Agente Decide o vai fazer
        predador.decidir(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());
        //Agente Faz o que decidiu
        predador.executar(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());

        mundo.imprimir();


        cout << "\nDigite 1 para continuar ou qualquer outro numero para sair \n";
        //getch();

        cin >> p;

        system("CLS");// Limpa a tela no windows
    }
    cout << "\nFim! \n";
    return 0;
}

