#include "raylib.h"
#include "BFS.h"
#include <iostream>
using namespace std;

int main(void) {
    int screenWidth = 1600;
    int screenHeight = 900;
    bool block = false;
    const int cellWidth = 100;
    const int cellHeight = 100;
    const int gridStartY = 225;
    int cellStates[20][20] = {0};
    static float origen[2] = { -1, -1 }; // Coordenadas de origen
    static float destino[2] = { -1, -1 }; // Coordenadas de destino
    static int modo=0;

    InitWindow(screenWidth, screenHeight, "Grupo 5 - Pathfinding");
    SetTargetFPS(144);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose()) {
        // Update
        screenWidth = GetScreenWidth();
        screenHeight = GetScreenHeight();
        int gridRows = (screenHeight / cellHeight) - 1;
        int gridCols = (screenWidth / cellWidth) - 2;
        
        SetExitKey(KEY_Q);
        ////////////////////////REINICIAR/////////////////////////////
        if (IsKeyPressed(KEY_ESCAPE)) {
            origen[0] = -1;
            origen[1] = -1;
            destino[0] = -1;
            destino[1] = -1;
            for (int i = 0; i < gridRows; i++) {
                for (int j = 0; j < gridCols; j++) {
                    cellStates[i][j] = 0;
                }
            }
            block = false;
        }
        

        if (IsKeyPressed(KEY_ENTER)) {
            if (origen[0] != -1 && destino[0] != -1) {
                vector<vector<int>> ruta = BFS(origen[0], origen[1], destino[0], destino[1], cellWidth, cellHeight, cellStates);
                // Procesar la ruta 
                for (auto& punto : ruta) {
                    cout << "(" << punto[0] << ", " << punto[1] << ") <- ";
                    cout << origen[0]/cellWidth << ", " << (origen[1]-225)/cellHeight << " <- ";
                    cout << destino[0]/cellWidth << ", " << (destino[1]-225)/cellHeight << endl;
                    if ((punto[1] != origen[0]/cellWidth || punto[0] != (origen[1]-225)/cellHeight) && (punto[1] != destino[0]/cellWidth || punto[0] != (destino[1]-225)/cellHeight)) {
                        cellStates[punto[0]][punto[1]] = 3;
                    }
                cout << endl;
                }
            }
            block = true;
        }
        ////////////////////CAMBIAR MODO//////////////////////////
        if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL)) {
            modo = !modo;
        }
        if (modo == 0) {
            DrawText("Modo Edicion", screenWidth / 2 + 587, screenHeight / 8 - 10, 20, BLACK);
        } else {
            DrawText("Modo Juego", screenWidth / 2 + 587, screenHeight / 8 - 10, 20, BLACK);
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        for (int i = 0; i < gridRows-2; i++) {
            for (int j = 0; j < gridCols; j++) {
                Rectangle cell = { j * cellWidth +100, gridStartY + i * cellHeight, cellWidth, cellHeight };
                bool cellHovered = CheckCollisionPointRec(GetMousePosition(), cell);
                if (cellHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !block) {
                    if (modo == 0 && cellStates[i][j] != 2 && !block) {
                        cellStates[i][j] = 1;
                    }
                    if (modo == 1) {
                        if (origen[0] == -1 && origen[1] == -1 && cellStates[i][j] != 1) {
                            cellStates[i][j] = 2;
                            origen[0] = (int)cell.x - 100;
                            origen[1] = (int)cell.y ;
                        } else if (destino[0] == -1 && destino[1] == -1 && cellStates[i][j] != 1) {
                            cellStates[i][j] = 2;
                            destino[0] = (int)cell.x - 100;
                            destino[1] = (int)cell.y;
                        }
                    }
                }

                if (cellHovered && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !block) {
                    if (modo == 0) {
                        if ((int)cell.x == origen[0] && (int)cell.y == origen[1]) {
                            origen[0] = -1;
                            origen[1] = -1;
                        }
                        if ((int)cell.x == destino[0] && (int)cell.y == destino[1]) {
                            destino[0] = -1;
                            destino[1] = -1;
                        }
                        cellStates[i][j] = 0;
                    }
                }

                if (cellStates[i][j] != 0) {
                    if (cellStates[i][j] == 1) {
                        DrawRectangleRec(cell, (Color){ 255, 0, 0, 255 }); // Rojo
                    } else if (cellStates[i][j] == 2) {
                        if ((int)cell.x -100 == origen[0] && (int)cell.y == origen[1]) {
                            DrawRectangleRec(cell, (Color){ 4, 255, 0, 255 }); // Verde
                        } else {
                            DrawRectangleRec(cell, (Color){ 255, 234, 0, 255 }); // Amarillo
                        }
                    }else if (cellStates[i][j] == 3) {
                        DrawRectangleRec(cell, (Color){ 0, 0, 255, 255 }); // Azul
                        DrawLine(cell.x, cell.y, cell.x + cell.width, cell.y + cell.height, BLACK); // Línea diagonal de arriba izquierda a abajo derecha
                        DrawLine(cell.x + cell.width, cell.y, cell.x, cell.y + cell.height, BLACK);
                    }
                } else {
                    DrawRectangleRec(cell, cellHovered ? (Color){ 92, 118, 127, 255 } : (Color){ 184, 237, 255, 255 });
                    DrawRectangleLinesEx(cell, 1, BLACK); // Usar DrawRectangleLinesEx para especificar el grosor

                }
            }
        }

        // Dibuja las líneas de la cuadrícula
        
        Rectangle buttonB = { screenWidth / 2 - 200, screenHeight / 8 - 20, 100, 40 };
        bool buttonHoveredB = CheckCollisionPointRec(GetMousePosition(), buttonB);

        if (buttonHoveredB && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Button action here
            DrawText("Button Pressed!", screenWidth / 2 - 130, screenHeight / 8 + 30, 20, RED);
        }
        DrawRectangleRec(buttonB, buttonHoveredB ? DARKGRAY : GRAY);
        DrawText("BFS", screenWidth / 2 - 170, screenHeight / 8 - 10, 20, WHITE);

        // Draw
        Rectangle buttonD = { screenWidth / 2 + 80, screenHeight / 8 - 20, 150, 40 };
        bool buttonHoveredD = CheckCollisionPointRec(GetMousePosition(), buttonD);

        if (buttonHoveredD && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            // Button action here
            DrawText("Button Pressed!", screenWidth / 2 + 110 , screenHeight / 8 + 30, 20, RED);
        }
        DrawRectangleRec(buttonD, buttonHoveredD ? DARKGRAY : GRAY);
        DrawText("D* focussed", screenWidth / 2 + 92 , screenHeight / 8 - 10, 20, WHITE);

        DrawRectangleLines(screenWidth / 2 + 550, screenHeight / 8 - 20, 200, 40, BLACK);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
