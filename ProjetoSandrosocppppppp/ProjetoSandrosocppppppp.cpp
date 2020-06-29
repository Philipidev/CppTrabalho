#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <time.h>
#include <locale.h>

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

        if (mundo->matriz[novo_y][novo_x] == NULL && (novo_x!=10) && novo_y!=10)
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

};


class Presa : public Agente {

public:

    Presa() {
        estado = ANDAR_ALEATORIO;// Estado Inicial
        tipo = 1;
        cout << "Inicializando Presa | Tipo = " << tipo << endl;
    }

    //TO DO: IMPLEMENTE O ALGORITMO DE DECISAO DO AGENTE
    void decidir(int mPresa, int nPresa, int mPreda, int nPreda) {

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

        if ((npp <= 3) && (mpp <= 3)) {
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
            int xmover = mPreda - mPresa;
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

class Walls : public Agente {
public:
    Walls() {
        tipo = 5;
    }
};

int tipoAgente(Agente* a) {
    return a == NULL ? 0 : a->tipo;
}


int SalvarMapa(Mundo* mundo, Agente* presa, Agente* predador, Agente* walls) {

    if (presa == NULL && predador == NULL && walls != NULL) {
        FILE* fp;
        cout << "Salvando..\n\n";
        fp = fopen("MapaWalls.txt", "w+");
        if (!fp) {
            cout << "Erro na abertura do arquivo";
            return 0;
        }


        fprintf(fp, "%d", M);
        fprintf(fp, "%d", N);
        fprintf(fp, "%s", "\n");
        for (int i = 0; i < M; i++) {
            for (int i2 = 0; i2 < N; i2++) {
                if (i == walls->GetY() && i2 == walls->GetX())
                    fprintf(fp, "%d", walls->getTipo());
                else
                    fprintf(fp,"%d", 0);
            }
            fprintf(fp, "%s", "\n");
        }
        fclose(fp);
    }
    else
    {
        FILE* fp;
        cout << "Salvando..\n\n";
        fp = fopen("MapaPresaPredador.txt", "w+");
        if (!fp) {
            cout << "Erro na abertura do arquivo";
            return 0;
        }
        fprintf(fp, "%d", M);
        fprintf(fp, "%d", N);
        fprintf(fp, "%s", "\n");

        for (int i = 0; i < M; i++) {
            for (int i2 = 0; i2 < N; i2++) {
                if (i == presa->GetY() && i2 == presa->GetX())
                    fprintf(fp,"%d",presa->getTipo());
                else if (i == predador->GetY() && i2 == predador->GetX())
                    fprintf(fp,"%d",predador->getTipo());
                else
                    fprintf(fp, "%d", 0);
            }
            fputs("\n", fp);
        }
        fclose(fp);
    }
    return 1;
}



int GamePresavsPredador(int i = 0) {
    Mundo mundo;
    Presa presa;
    Predador predador;
    mundo.inicializa();
    int xpresa = 0, ypresa = 0;//1
    int xpreda = 0, ypreda = 0;//2

    if (i == 0) {

        cout << "Digite a posição X para inicializar o agente Presa:\n\n";
        cin >> xpresa;
        cout << "Digite a posição Y para inicializar o agente Presa:\n";
        cin >> ypresa;
        presa.inicializa(&mundo, xpresa, ypresa);


        cout << "Digite a posição X para inicializar o agente Predador:\n\n";
        cin >> xpreda;
        cout << "Digite a posição Y para inicializar o agente Predador:\n";
        cin >> ypreda;
        predador.inicializa(&mundo, xpreda, ypreda);
    }
    else
    {
        FILE* fl;
        int c;
        char mapa[100][100];

        if ((fl = fopen("MapaPresaPredador.txt", "r")) == NULL) {
            perror("Erro: fopen");
            exit(EXIT_FAILURE);
        }

        int deubreak = 0;
        int contador = 0;
        int prima = 0;
        while (!feof(fl)) {
            fscanf(fl, "%s", &mapa[contador]);
            
            if (prima == 0) {
                prima++;
                contador++;
                continue;
            }
            for (int i = 0; i <= strlen(mapa[contador]); i++) {
                if (mapa[contador][i] == '2') {
                    xpreda = i;
                    ypreda = contador-1;
                    deubreak ++;
                    break;
                }
                if(mapa[contador][i] == '1') {
                    xpresa = i;
                    ypresa = contador-1;
                    deubreak ++;
                    break;
                }
            }
            if (deubreak == 2)
                break;
            contador++;
        }

        mapa;
        xpresa;
        system("cls");
        ypresa;
        xpreda;
        system("cls");
        ypreda;
        system("cls");


        fclose(fl);
    }

    presa.inicializa(&mundo, xpresa, ypresa);
    predador.inicializa(&mundo, xpreda, ypreda);

    int cont = 0;
    int i2 = 1;
    int primeravez = 0;
    while (cont++ < 100 && i2 == 1) {

        if (primeravez == 0) {
            primeravez++;
            mundo.imprimir();
            cout << "Digite 1 para continuar / 2 Para salvar e sair / qualquer outra tecla para sair..\n";
            char a;
            cin >> a;
            if (a != '1' && a != '2')
                break;
            if (a == '2') {
                SalvarMapa(&mundo, &presa, &predador, NULL);
                break;
            }
        }
        //Agente Decide o vai fazer
        presa.decidir(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());
        //Agente Faz o que decidiu
        presa.executar(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());

        //Agente Decide o vai fazer
        predador.decidir(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());
        //Agente Faz o que decidiu
        predador.executar(presa.GetY(), presa.GetX(), predador.GetY(), predador.GetX());

        mundo.imprimir();




        cout << "Digite 1 para continuar / 2 Para salvar e sair / qualquer outra tecla para sair..\n";
        char a;
        cin >> a;
        if (a != '1' && a !='2')
            break;
        if (a == '2') {
            SalvarMapa(&mundo, &presa, &predador, NULL);
            break;
        }


        system("cls");
    }
    return 0;
}


int GameWalls(int i = 0) {

    Mundo mundowalls;
    Walls walls;
    int x = 0, y = 0;
    if (i == 0) {
        cout << "Digite a posição X para inicializar o agente:\n\n";
        cin >> x;
        cout << "Digite a posição Y para inicializar o agente:\n";
        cin >> y;
    }
    else
    {
        FILE* fl;
        int c;
        char mapa[100][100];

        if ((fl = fopen("MapaWalls.txt", "r")) == NULL) {
            perror("Erro: fopen");
            exit(EXIT_FAILURE);
        }

        int deubreak = 0;
        int contador = 0;
        while (!feof(fl)) {
            fscanf(fl, "%s",&mapa[contador]); 
            for (int i = 0; i <= strlen(mapa[contador]); i++) {
                if (mapa[contador][i] == '5') {
                    x = i;
                    y = contador-1;
                    deubreak = 1;
                    break;
                }
            }
            if (deubreak == 1)
                break;
            contador++;
        }
      
        fclose(fl);
    }

    mundowalls.inicializa();
    walls.inicializa(&mundowalls, x, y);


    int postemp = walls.GetY();
    int postempX, postempY;
    //cout << postemp;
    bool continuar = true;
    while (continuar && i==0) {
        walls.mover(walls.GetX(), walls.GetY() + 1);
        if (walls.GetY() == postemp) {
            continuar = false;
        }
        postemp = walls.GetY();

        mundowalls.imprimir();
        cout << "Digite 1 para continuar / qualquer outra tecla para sair..\n";
        char a;
        cin >> a;
        if (a != '1')
            return 0;
        
        system("cls");
    }

    continuar = true;
    postempX = walls.GetX();
    postempY = walls.GetY();
    int primeirovez = 0;
    do {
        if (primeirovez == 0) {
            mundowalls.imprimir();
            cout << "Digite 1 para continuar / 2 Para salvar e sair / qualquer outra tecla para sair..\n";
            char a;
            cin >> a;
            if (a != '1' && a != '2')
                break;
            if (a == '2') {
                SalvarMapa(&mundowalls, NULL, NULL, &walls);
                cout << "Jogo Salvo com sucesso";
                system("pause");
                break;
            }
        }
        primeirovez++;
        system("cls");
        if (walls.GetX() < 9 && walls.GetY() == 9) {
            walls.mover(walls.GetX() + 1, walls.GetY());
        }

        else if (walls.GetX() == 9 && walls.GetY() == 9) {
            walls.mover(walls.GetX(), walls.GetY() - 1);
        }

        else if (walls.GetX() == 9 && walls.GetY() > 0) {
            walls.mover(walls.GetX(), walls.GetY() - 1);
        }

        else if (walls.GetX() > 0 && walls.GetY() == 0) {
            walls.mover(walls.GetX() - 1, walls.GetY());
        }

        else if (walls.GetX() == 0 && walls.GetY() == 0) {
            walls.mover(0, 1);
        }

        else if (walls.GetX() == 9 && walls.GetY() < 9) {
            walls.mover(walls.GetX(), walls.GetY() + 1);
        }

        else if (walls.GetX() == 0 && walls.GetY() < 9) {
            walls.mover(walls.GetX(), walls.GetY() + 1);
        }

        mundowalls.imprimir();
        cout << "Digite 1 para continuar / 2 Para salvar e sair / qualquer outra tecla para sair..\n";
        char a;
        cin >> a;
        if (a != '1' && a != '2')
            break;
        if (a == '2') {
            SalvarMapa(&mundowalls, NULL, NULL, &walls);
            cout << "Jogo Salvo com sucesso";
            system("pause");
            break;
        }

        system("cls");
    } while (continuar);

    return 0;
}





int main()
{
    setlocale(LC_ALL, "Portuguese");
    char escolha;
    char esc;
    bool continuar = true;
    system("cls");
    do {
        cout << "Escolha:\n1)Walls\n2)Presa vs Predador\n0)Sair" << endl;
        cin >> escolha;
        switch (escolha)
        {
        case '1':
            ;
            cout << "1)Começar um novo jogo\n2)Carregar último jogo salvo" << endl;
            cin >> esc;
            if (esc == '1')
                GameWalls();
            else if (esc == '2')
                GameWalls(1);
            break;

        case '2':
            ; 
            cout << "1)Começar um novo jogo\n2)Carregar último jogo salvo" << endl;
            cin >> esc;
            if (esc == '1')
                GamePresavsPredador();
            else if (esc == '2')
                GamePresavsPredador(1);
            break;

        case '0':
            continuar = false;
            break;

        default:
            ;
            cout << "Escolha invalida..\n";
            system("pause");
            break;
        }
        system("cls");
    } while (continuar);

    cout << "\nFim! \n";
    return 0;
}

