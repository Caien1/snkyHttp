#include<raylib.h>
#include<raygui.h>
#include "uiImpl.h"
#define URL_BUFFER 1024


int main(){

char buffer[URL_BUFFER +1] ="\0";
InitWindow(800,800,"Http Status");

Color fav= {51,51,51,0};
// Rectangle rect ={0,0,10,10};

    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        // TODO: Update your variables here

            BeginDrawing();

        //  InsideLoop();
        //  if(IsKeyPressed(KEY_F)) ToggleFullScreenWindow();
            
            ClearBackground(fav);
            DrawTextOnScreen();


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}