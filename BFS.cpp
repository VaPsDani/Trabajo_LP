#include <vector>
#include <iostream>
#include <queue>
#include "BFS.h"

using namespace std;

struct Nodo {
    int x, y;
    Nodo(int x, int y) : x(x), y(y) {}
};

vector<vector<int>> BFS(int ix, int iy, int fx, int fy, int cellWidth, int cellHeight, int cellStates[6][12]) {
    bool visitado[6][12] = {false};
    int padre[6][12][2];
    fill(&padre[0][0][0], &padre[0][0][0] + sizeof(padre) / sizeof(int), -1); // Inicializar a -1

    queue<Nodo> Cola;
    Cola.push(Nodo(ix, iy));
    visitado[ix/cellWidth][iy/cellHeight] = true;

    int dx[4] = {-cellWidth, 0, cellWidth, 0};
    int dy[4] = {0, cellHeight, 0, -cellHeight};

    vector<vector<int>> ruta;

    while (!Cola.empty()) {
        
        Nodo nodo = Cola.front();
        Cola.pop();

        if (nodo.x == fx && nodo.y == fy) {
            cout << "Ruta encontrada" << endl;
            int x = fx/cellWidth, y = fy/cellHeight;
            while (padre[x][y][0] != -1) {
                ruta.push_back({x, y});
                int tempX = padre[x][y][0];
                int tempY = padre[x][y][1];
                x = tempX;
                y = tempY;
            }
            ruta.push_back({ix, iy });
            return ruta;
        }

        for (int i = 0; i < 4; i++) {
            int newX = nodo.x + dx[i];
            int newY = nodo.y + dy[i];
            

            if (newX >= 0 && newY >= 0 && newX < 675 && newY < 1600 && !visitado[newX/cellWidth][newY/cellHeight] && cellStates[newX/cellWidth][newY/cellHeight] != 1) {
                Cola.push(Nodo(newX, newY));
                visitado[newX/cellWidth][newY/cellHeight] = true;
                padre[newX/cellWidth][newY/cellHeight][0] = nodo.x;
                padre[newX/cellWidth][newY/cellHeight][1] = nodo.y;
            }
        }
    }

    cout << "No se encontró una ruta válida" << endl;
    return ruta;
}
