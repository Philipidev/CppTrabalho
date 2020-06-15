// ProjetoSandrosocppppppp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <string.h>
#include <stdbool.h>

using namespace std; 

class  Agente {
    int x = 4;
    int y = 3;
    int estado = 1;

    public:
        void Inicializar(int paramx, int paramy) {
            x = paramx;
            y = paramy;

        }
        
        void Mover(int novox, int novoy) {
            x = novox;
            y = novoy;
        }

        void Decidir(int decisao) {
            estado = decisao;
        }

        void Executar() {

        }

        int GetX() {
            return x;
        }
        int GetY() {
            return y;
        }
};

class Mundo : public Agente {
   
    int M = NULL;
    int N = NULL;
    public:
        Mundo(int posM, int posN) {
            M = posM;
            N = posN;
        }
        Mundo() {
        }

        void Imprimir() {
            int posx = GetX()-1;
            int posy = GetY()-1;
            for (int i = 0; i < M; i++) {
                for (int i2 = 0; i2 < N; i2++) {
                    if (posy == i && posx == i2) {
                        cout << "1";
                    }
                    else {
                        cout << "0";
                    }
                    cout << " ";
                }
                cout << "\n";
            }
        }
  
};

class Walls : public Agente {

};


int main(int argc, char *argv[])
{
    
    Mundo* teste = new Mundo(14,19);
    bool continuar = true;
    teste->Imprimir();

    //do {
    //    


    //} while (continuar);

    //cout << teste->estado;
    system("pause");
}

