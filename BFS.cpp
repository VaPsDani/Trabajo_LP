#include <vector>
#include <iostream>
#include <queue>
#include "BFS.h"

using namespace std;

struct Nodo {
    int x, y;
    Nodo() : x(-1), y(-1) {} // Default constructor
    Nodo(int x, int y) : x(x), y(y) {}
};

vector<vector<int>> BFS(int ix, int iy, int fx, int fy, int cellWidth, int cellHeight, int cellStates[6][12]) {
    bool visitado[6][12] = {false};
    Nodo padre[6][12];
    queue<Nodo> orden ;
    int z = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 12; ++j) {
            padre[i][j] = Nodo();
        }
    }// Inicializar a -1

    queue<Nodo> Cola;
    Cola.push(Nodo(ix, iy));
    visitado[ix/cellWidth][(iy-225)/cellHeight] = true;

    int dx[4] = {-cellWidth, 0, cellWidth, 0};
    int dy[4] = {0, cellHeight, 0, -cellHeight};

    vector<vector<int>> ruta;

    while (!Cola.empty()) {

        Nodo nodo = Cola.front();
        Cola.pop();
        cout << nodo.x << endl;
        cout << nodo.y << endl;
        cout << "----------------" << endl;
        if (nodo.x == fx && nodo.y == fy) {
            cout << "Ruta encontrada" << endl;
            int x = fx/cellWidth, y = (fy-225)/cellHeight;
            while (!padre[x][y].x == -1 && !padre[x][y].y == -1) {
                ruta.push_back({x, y});
                Nodo temp = padre[x][y];
                x = temp.x;
                y = temp.y;
            }
            ruta.push_back({ix, iy });
            return ruta;
        }

        for (int i = 0; i < 4; i++) {
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];
            

            if (newX >= 0 && newY >= 0 && newX < 675 && newY < 1600 && !visitado[newX/cellWidth][(newY-225)/cellHeight] && cellStates[newX/cellWidth][(newY-225)/cellHeight] != 1) {
                Cola.push(Nodo(newX, newY));
                orden.push(Nodo(newX, newY));
                visitado[newX/cellWidth][(newY-225)/cellHeight] = true;
                padre[newX/cellWidth][(newY-225)/cellHeight] = nodo;

            }

        }
    }

    for (int i = 0; i < orden.size(); i++)
    {
        int a =  orden.front().x / cellWidth;
        int b = (orden.front().y - 225) / cellHeight;
        cout << a << b << endl;
        orden.pop();
    }
    


    cout << "No se encontró una ruta válida" << endl;
    return ruta;
}
