#include<raylib.h>
#include<raygui.h>
#include "uiImpl.h"
int main(){
InitWindow(800,800,"Http Status");

Color fav= {51,51,51,0};
Rectangle rect ={0,0,10,10};


    while (!WindowShouldClose())    
    {
        // TODO: Update your variables here

DrawText(TextFormat("Score: %08i"), 400, 400, 50, RED);
            BeginDrawing();

            InsideLoop();
            
            ClearBackground(fav);
             


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}