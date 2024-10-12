#include "raylib.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1600;
    const int screenHeight = 900;
    const int gridRows= 6;
    const int gridCols = 12;
    const int cellWidth = (screenWidth / gridCols) + 1;
    const int cellHeight = (screenHeight - (screenHeight / 4)) / gridRows;
    const int gridStartY = screenHeight / 4;
    int cellstates[gridRows][gridCols] = {0};
    int origen=0;

    InitWindow(screenWidth, screenHeight, "Grupo 5 - Pathfinding");

    SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        // Draw a button
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

        if (IsKeyPressed(KEY_Q)){
            origen=0;
            for (int i = 0; i < gridRows; i++)
            {
                for (int j = 0; j < gridCols; j++)
                {
                    cellstates[i][j] = 0;
                }
            }
        }
        
        static int modo = 0;
        if (IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_RIGHT_CONTROL)) {
            modo = !modo;
        }

        if (modo == 0) {
            DrawText("Modo Edicion", screenWidth / 2 + 587, screenHeight / 8 - 10, 20, BLACK);
        } else {
            DrawText("Modo Juego", screenWidth / 2 + 587, screenHeight / 8 - 10, 20, BLACK);
        }
        ////////////////////////////////////////////////////////////////////// Dibujar grid///////////////////////////////////////////////////////////////////////////////
        for (int i = 0; i < gridRows; i++)
        {
            for (int j = 0; j < gridCols; j++)
            {
                Rectangle cell = { j * cellWidth, gridStartY + i * cellHeight, cellWidth, cellHeight };
                bool cellHovered = CheckCollisionPointRec(GetMousePosition(), cell);
                if (cellHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {

                    if(modo==0){
                        cellstates[i][j] = 1;
                    }
                    if(modo==1){
                        cellstates[i][j] = 2;
                    }
                }
                if (cellHovered && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON) )
                {
                    cellstates[i][j] = 0;
                }
            }
        }
    

        // Draw cells
        

        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

        for (int i = 0; i < gridRows; i++)
        {
            for (int j = 0; j < gridCols; j++)
            {
                Rectangle cell = { j * cellWidth, gridStartY + i * cellHeight, cellWidth, cellHeight };
                bool cellHovered = CheckCollisionPointRec(GetMousePosition(), cell);
                if (cellstates[i][j] >= 1)
                {
                    if (modo==0 && cellstates[i][j] == 1)
                    {   
                        DrawRectangleRec(cell, RED);
                    }else if(modo==1 && cellstates[i][j] == 2){
                        if (origen==0)
                        {
                            DrawRectangleRec(cell, (Color){ 4, 255, 0, 255 }); //verde
                            origen=+1;
                        }else if (origen==1){
                            DrawRectangleRec(cell, (Color){ 255, 234, 0, 255 }); //amarillo
                            origen=+1;
                        }
                    }
                }
                else
                {
                    // Inactive cell (blue or darker if hovered)
                    DrawRectangleRec(cell, cellHovered ? (Color){ 92, 118, 127, 255 } : (Color){ 184, 237, 255, 255 });
                }
            }
        }

        ////////////////////////////// DIBUJAR LINEAS (NO TOCAR)///////////////////////////////
        for (int i = 0; i <= gridRows; i++)
        {
            DrawLine(0, gridStartY + i * cellHeight, screenWidth, gridStartY + i * cellHeight, BLACK);
        }

        for (int j = 0; j <= gridCols; j++)
        {
            DrawLine(j * cellWidth, gridStartY, j * cellWidth, screenHeight, BLACK);
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}