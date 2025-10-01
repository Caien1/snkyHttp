#include<raylib.h>
#include "uiImpl.h"
#define RAYGUI_IMPLEMENTATION

#include"../include/raygui.h"

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


        InsideLoop();
        //  if(IsKeyPressed(KEY_F)) ToggleFullScreenWindow();
        bool test = true;
            if(GuiTextInputBox((Rectangle){200,200,200, 200},"None","test" ,"try","sdfs",15,&test)){test = !test;}
    //        GuiButton((Rectangle){200,200,200, 15},"send");
            ClearBackground(fav);


        


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}