#include "raylib.h"
#include "BFS.h"
#include <iostream>
using namespace std;

int main(void) {
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int gridRows = 15;
    const int gridCols = 15;
    const int cellWidth = (screenWidth / 12) + 1;
    const int cellHeight = (screenHeight - (screenHeight / 4)) / 6;
    const int gridStartY = screenHeight / 4;
    static int cellStates[gridRows][gridCols] = {0};
    static float origen[2] = { -1, -1 }; // Coordenadas de origen
    static float destino[2] = { -1, -1 }; // Coordenadas de destino
    static int modo=0;

    InitWindow(screenWidth, screenHeight, "Grupo 5 - Pathfinding");
    SetTargetFPS(144);

    while (!WindowShouldClose()) {
        // Update
        
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
        }

        if (IsKeyPressed(KEY_ENTER)) {
            if (origen[0] != -1 && destino[0] != -1) {
                vector<vector<float>> ruta = BFS(origen[0], origen[1], destino[0], destino[1], cellWidth, cellHeight, cellStates);
                // Procesar la ruta 
                for (const auto& punto : ruta) {
                cout << "(" << punto[0] << ", " << punto[1] << ") <- ";
                }
                cout << endl;
            }
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

        for (int i = 0; i < gridRows; i++) {
            for (int j = 0; j < gridCols; j++) {
                Rectangle cell = { j * cellWidth, gridStartY + i * cellHeight, cellWidth, cellHeight };
                bool cellHovered = CheckCollisionPointRec(GetMousePosition(), cell);
                if (cellHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (modo == 0 && cellStates[i][j] != 2) {
                        cellStates[i][j] = 1;
                    }
                    if (modo == 1) {
                        if (origen[0] == -1 && origen[1] == -1 && cellStates[i][j] != 1) {
                            cellStates[i][j] = 2;
                            origen[0] = (int)cell.x;
                            origen[1] = (int)cell.y;
                        } else if (destino[0] == -1 && destino[1] == -1 && cellStates[i][j] != 1) {
                            cellStates[i][j] = 2;
                            destino[0] = (int)cell.x;
                            destino[1] = (int)cell.y;
                        }
                    }
                }

                if (cellHovered && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
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
                        if ((int)cell.x == origen[0] && (int)cell.y == origen[1]) {
                            DrawRectangleRec(cell, (Color){ 4, 255, 0, 255 }); // Verde
                        } else {
                            DrawRectangleRec(cell, (Color){ 255, 234, 0, 255 }); // Amarillo
                        }
                    }
                } else {
                    DrawRectangleRec(cell, cellHovered ? (Color){ 92, 118, 127, 255 } : (Color){ 184, 237, 255, 255 });
                }
            }
        }

        // Dibuja las líneas de la cuadrícula
        for (int i = 0; i <= gridRows; i++) {
            DrawLine(0, gridStartY + i * cellHeight, screenWidth, gridStartY + i * cellHeight, BLACK);
        }
        for (int j = 0; j <= gridCols; j++) {
            DrawLine(j * cellWidth, gridStartY, j * cellWidth, screenHeight, BLACK);
        }
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
