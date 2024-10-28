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
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 12; ++j) {
            padre[i][j] = Nodo();
            padre[i][j].x = -1;
            padre[i][j].y = -1;
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
        if (nodo.x == fx && nodo.y == fy) {
            cout << "Ruta encontrada" << endl;
            int a = fx/cellWidth, b = (fy-225)/cellHeight;
            while (padre[a][b].x != -1) {
                ruta.push_back({a, b});
                Nodo temp = padre[a][b];
                a = temp.x/cellWidth;
                b = (temp.y-225)/cellHeight;
            }
            ruta.push_back({a, b});
            return ruta;
        }

        for (int i = 0; i < 4; i++) {
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];
            

            if (newX >= 0 && newY >= 225 && newX < 1600  && newY < 897 && !visitado[newX/cellWidth][(newY-225)/cellHeight] && cellStates[newX/cellWidth][(newY-225)/cellHeight] != 1) {
                Cola.push(Nodo(newX, newY));
                cout << "Nodo: " << newX/cellWidth<< " " << (newY-225)/cellHeight << endl;
                cout << nodo.x << " " << nodo.y << endl;
                cout << "----------------" << endl;
                visitado[newX/cellWidth][(newY-225)/cellHeight] = true;
                padre[newX/cellWidth][(newY-225)/cellHeight] = nodo;

            }

        }
    }

    

    cout << "No se encontró una ruta válida" << endl;
    return ruta;
}
