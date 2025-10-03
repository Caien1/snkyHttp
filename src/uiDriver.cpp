
#include "uiImpl.h"
#define RAYGUI_IMPLEMENTATION

#include"../include/raygui.h"


#define URL_BUFFER 1024


int main(){

char buffer[URL_BUFFER +1] ="\0";
InitWindow(800,800,"Http Status");

Color fav= {51,51,51,0};

    SetTargetFPS(60);

    while (!WindowShouldClose())    
    {
        
        // TODO: Update your variables here

            BeginDrawing();




            EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}