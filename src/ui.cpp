#include<raylib.h>

int main(){
InitWindow(800,800,"Http Status");


    while (!WindowShouldClose())    
    {
        // TODO: Update your variables here

        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}