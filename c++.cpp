#include "raylib.h"
#include "RAM.h"

#include "BFS.h"
#include "FDS.h"
#include <iostream>
#include <chrono>

size_t medirUsoDeMemoria(RAM& ram) {
    return ram.obtenerUsoDeMemoria();
}

int main(void) {
    RAM ram;
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
    SetTargetFPS(60);
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    while (!WindowShouldClose()) {
        // Update
        
        if (origen[0] != -1 && destino[0] != -1)
        {
            Vector2 pos=GetWindowPosition();
            SetWindowSize(screenWidth, screenHeight);
            SetWindowPosition(pos.x, pos.y);
        }
        
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
                    if(cellStates[i][j] != 1){
                        cellStates[i][j] = 0;
                    }
                }
            }

            block = false;
        }
        

        if (IsKeyPressed(KEY_ENTER)) {
            if (origen[0] != -1 && destino[0] != -1) {
                for (int i = 0; i < gridRows; i++) {
                    for (int j = 0; j < gridCols; j++) {
                        if(cellStates[i][j] == 3){
                            cellStates[i][j] = 0;
                        }
                    }
                }
                size_t memoriaAntes = medirUsoDeMemoria(ram);
                auto start = std::chrono::high_resolution_clock::now();
                std::vector<std::vector<int>> ruta = BFS(origen[0], origen[1], destino[0], destino[1], cellWidth, cellHeight, cellStates);
                
                for (auto punto : ruta) {
                    std::cout << "(" << punto[0] << ", " << punto[1] << ") <- ";
                    std::cout << origen[0]/cellWidth << ", " << (origen[1]-225)/cellHeight << " <- ";
                    std::cout << destino[0]/cellWidth << ", " << (destino[1]-225)/cellHeight << std::endl;
                    if ((punto[1] != origen[0]/cellWidth || punto[0] != (origen[1]-225)/cellHeight) && (punto[1] != destino[0]/cellWidth || punto[0] != (destino[1]-225)/cellHeight)) {
                        std::cout<<punto[1]<<" ";//x
                        std::cout<<punto[0]<<" ";//y
                        cellStates[punto[0]][punto[1]] = 3;
                    }
                std::cout << std::endl;
                }
                size_t memoriaDespues =  medirUsoDeMemoria(ram);
                std::cout << "Memoria utilizada por Algoritmo 1: " << (memoriaDespues - memoriaAntes)  << "Bytes" << std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
            }
            SetWindowSize(screenWidth, screenHeight);
            block = true;
        }
        
        if (IsKeyPressed(KEY_SPACE)) {
            if (origen[0] != -1 && destino[0] != -1) {
                for (int i = 0; i < gridRows; i++) {
                    for (int j = 0; j < gridCols; j++) {
                        if(cellStates[i][j] == 3){
                            cellStates[i][j] = 0;
                        }
                    }
                }
                size_t memoriaAntes =  medirUsoDeMemoria(ram);
                auto start = std::chrono::high_resolution_clock::now();

                std::vector<std::pair<int,int>> rut = FDS((origen[1]-225)/cellHeight , origen[0]/cellWidth, (destino[1]-225)/cellHeight , destino[0]/cellWidth , gridRows-2, gridCols+1, cellStates);
                // Procesar la ruta 
                for (auto punt : rut) {
                    std::cout << "(" << punt.first << ", " << punt.second << ") <- ";
                    std::cout << origen[0]/cellWidth << ", " << (origen[1]-225)/cellHeight << " <- ";
                    std::cout << destino[0]/cellWidth << ", " << (destino[1]-225)/cellHeight << std::endl;
                    
                    if ((punt.second != origen[0]/cellWidth || punt.first != (origen[1]-225)/cellHeight) && (punt.second != destino[0]/cellWidth || punt.first != (destino[1]-225)/cellHeight)) {
                        cellStates[punt.first][punt.second] = 3;
                    }
                std::cout << std::endl;
                }
                size_t memoriaDespues =  medirUsoDeMemoria(ram);
                std::cout << "Memoria utilizada por Algoritmo 1: " << (memoriaDespues - memoriaAntes)  << "Bytes" << std::endl;
                auto end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> elapsed = end - start;
                std::cout << "Tiempo de ejecución: " << elapsed.count() << " segundos" << std::endl;
            }
            SetWindowSize(screenWidth, screenHeight);
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
                            origen[0] = cell.x-100;
                            origen[1] = cell.y ;
                        } else if (destino[0] == -1 && destino[1] == -1 && cellStates[i][j] != 1) {
                            cellStates[i][j] = 2;
                            destino[0] = cell.x-100;
                            destino[1] = cell.y;
                        }
                    }
                }

                if (cellHovered && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) && !block) {
                    if (modo == 0) {
                        if (cell.x == (origen[0]+ 100) && cell.y == origen[1]) {
                            origen[0] = -1;
                            origen[1] = -1;
                        }
                        if (cell.x == (destino[0]+ 100) && cell.y == destino[1]) {
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

        // Dibuja las líneas de la cuadrícula;
        
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
