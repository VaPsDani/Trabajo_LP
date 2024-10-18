#include <vector>
#include <iostream>
#include <queue>
#include "BFS.h"

using namespace std;

struct Nodo {
    int x, y;
    Nodo(int x, int y) : x(x), y(y) {}
};

vector<vector<float>> BFS(int ix, int iy, int fx, int fy, float cellWidth, float cellHeight, int cellStates[15][15]) {
    bool visitado[15][15] = {false};
    float padre[15][15][2];
    fill(&padre[0][0][0], &padre[0][0][0] + sizeof(padre) / sizeof(float), -1); // Inicializar a -1

    queue<Nodo> Cola;
    Cola.push(Nodo(ix, iy));
    visitado[ix][iy] = true;

    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, 1, 0, -1};

    vector<vector<float>> ruta;

    while (!Cola.empty()) {
        Nodo nodo = Cola.front();
        Cola.pop();

        if (nodo.x == fx && nodo.y == fy) {
            cout << "Ruta encontrada" << endl;
            int x = fx, y = fy;
            while (padre[x][y][0] != -1) {
                ruta.push_back({x * cellWidth, y * cellHeight});
                int tempX = padre[x][y][0];
                int tempY = padre[x][y][1];
                x = tempX;
                y = tempY;
            }
            ruta.push_back({ix * cellWidth, iy * cellHeight});
            return ruta;
        }

        for (int i = 0; i < 4; i++) {
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];

            if (newX >= 0 && newY >= 0 && newX < 6 && newY < 12 && !visitado[newX][newY] && cellStates[newX][newY] != 1) {
                Cola.push(Nodo(newX, newY));
                visitado[newX][newY] = true;
                padre[newX][newY][0] = nodo.x;
                padre[newX][newY][1] = nodo.y;
            }
        }
    }

    cout << "No se encontró una ruta válida" << endl;
    return ruta;
}
