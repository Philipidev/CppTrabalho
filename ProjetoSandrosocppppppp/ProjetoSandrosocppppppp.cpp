// ProjetoSandrosocppppppp.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>

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
        
        void Mover(char mover, int m, int n){
            mover = toupper(mover);

            if(!(x-1 <= 0 && mover == 'A') && !(x-1 >= n-1 && mover == 'D') && !(y-1 <= 0 && mover == 'W') && !(y-1 >= m-1 && mover == 'S'))
            {
                if (mover == 'A') {
                    x--;
                }
                if (mover == 'S') {
                    y++;
                }
                if (mover == 'D') {
                    x++;
                }
                if (mover == 'W') {
                    y--;
                }
            }
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

        int GetM() {
            return M;
        }

        int GetN() {
            return N;
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
    
    Mundo* mundo = new Mundo(14,19);
    Walls* walls = new Walls();
    bool continuar = true;
    char mover;

    do {
        mundo->Imprimir();
        mover=getchar();
        mundo->Mover(mover, mundo->GetM(), mundo->GetN());

        system("cls");
    } while (continuar);

    //cout << mundo->estado;
    system("pause");
}

