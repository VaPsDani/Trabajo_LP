#include <vector>
#include <iostream>
#include <queue>
#include "BFS.h"
#include "raylib.h"

using namespace std;

struct Nodo {
    int x, y;
    Nodo() : x(-1), y(-1) {} // Default constructor
    Nodo(int x, int y) : x(x), y(y) {}
};

vector<vector<int>> BFS(int ix, int iy, int fx, int fy, int cellWidth, int cellHeight, int cellStates[20][20]) {
    bool visitado[20][20] = {false};
    Nodo padre[20][20];
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            padre[i][j] = Nodo();
            padre[i][j].x = -1;
            padre[i][j].y = -1;
        }
    }// Inicializar a -1

    queue<Nodo> Cola;
    Cola.push(Nodo(ix, iy));
    visitado[(iy-225)/cellHeight][ix/cellWidth] = true;

    int dx[4] = {-cellWidth, 0, cellWidth, 0};
    int dy[4] = {0, cellHeight, 0, -cellHeight};

    vector<vector<int>> ruta;

    while (!Cola.empty()) {

        Nodo nodo = Cola.front();
        Cola.pop();
        if (nodo.x == fx && nodo.y == fy) {
            cout << "Ruta encontrada" << endl;
            int a = (fy-225)/cellHeight, b = fx/cellWidth;
            while (padre[a][b].x != -1) {
                ruta.push_back({a, b});
                Nodo temp = padre[a][b];
                a = (temp.y-225)/cellHeight;
                b = temp.x/cellWidth;
            }
            ruta.push_back({a, b});
            return ruta;
        }
        for (int i = 0; i < 4; i++) {
            
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];

            if (newX >= 0 && newY >= 225 && newX < GetScreenWidth() - 100  && newY < GetScreenHeight() - 100 && !visitado[(newY-225)/cellHeight][newX/cellWidth] && cellStates[(newY-225)/cellHeight][newX/cellWidth] != 1) {
                Cola.push(Nodo(newX, newY));
                visitado[(newY-225)/cellHeight][newX/cellWidth] = true;
                padre[(newY-225)/cellHeight][newX/cellWidth] = nodo;
            }

        }
    }

    

    cout << "No se encontró una ruta válida" << endl;
    return ruta;
}
