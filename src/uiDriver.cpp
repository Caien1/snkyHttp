#include<raylib.h>
#include<raygui.h>
int main(){
InitWindow(800,800,"Http Status");

Color fav= {51,51,51,0};
Rectangle rect ={0,0,10,10};


    while (!WindowShouldClose())    
    {
        // TODO: Update your variables here


        BeginDrawing();

            ClearBackground(fav);
            DrawFPS(400,0);
             


        EndDrawing();
    }

    CloseWindow();        // Close window and OpenGL context


    return 0;
}