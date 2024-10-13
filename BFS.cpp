#include <vector>
#include <iostream>
#include <queue>
#include "BFS.h"
using namespace std;
struct Nodo{
        int x, y;
        Nodo(int x, int y) : x(x), y(y) {}
    }; 
vector<vector<float>> BFS(int ix, int iy, int fx, int fy) /////////chekear tipo de retorno
{   
    bool visitado[6][12]={false};
    float padre[6][12][2]={-1};
    queue<Nodo> Cola;
    Cola.push(Nodo(ix, iy));
    visitado[ix][iy]=true;
    padre[ix][iy][0]=-1;
    float ruta[36][2];
    int contador=0;

    int dx[4] = {-1, 0, 1, 0}; // Direcciones de movimiento: arriba, derecha, abajo, izquierda
    int dy[4] = {0, 1, 0, -1};

    while (!Cola.empty())
    {
        Nodo nodo = Cola.front();
        Cola.pop();

        if ((nodo.x==fx) && (nodo.y=fy)){
            int x = fx, y = fy;
            while (padre[x][y][0] != -1) {
                cout << "(" << x << ", " << y << ") <- ";
                int tempX = padre[x][y][0];
                int tempY = padre[x][y][1];
                x = tempX;
                y = tempY;
                ruta[contador][0]=x;
                ruta[contador][1]=y;
                contador+=1;
            }
            ///cout << "(" << ix << ", " << iy << ")" << endl;
            return ruta;
        }

        for (int i = 0; i < 4; i++) {
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];

            if(newX >= 0 && newY >= 0 && newX < 6 && newY < 12){
                Cola.push(Nodo(newX, newY));
                visitado[newX][newY] = true;
                padre[newX][newY][0] = nodo.x;
                padre[newX][newY][1] = nodo.y;
            }
        }
    }
    cout <<"No se encontro una ruta valida" <<endl; /////////Poner tilde p
};