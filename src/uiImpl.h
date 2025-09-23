#include<raylib.h>
void InsideLoop();
void ToggleFullScreenWindow();

void InsideLoop(){
    
    DrawFPS(500,500);
    
}

void ToggleFullScreenWindow(){

    if(!IsWindowFullscreen()){
    int display = GetCurrentMonitor();

        SetWindowSize(GetMonitorWidth(display),GetMonitorHeight(display));
        ToggleFullscreen();

    }else{

                SetWindowSize(800,800);
                ToggleFullscreen();
    }

}

void DrawTextOnScreen(){
     DrawRectangle(400, 400, 40, 5, RAYWHITE);
     
}