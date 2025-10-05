#include <raylib.h>


#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"
#include <stdio.h>
#define BACKGROUND_COLOR  (Color){59,59,59,255}
#define SIDE_VIEW_COLOR (Color){23,23,23,255}
#define SCALING_FACTOR 1.4
#define URL_BUFFER 256

void draw_history_section(){
  Rectangle  history_view = {0,0,GetScreenWidth()*0.3,GetScreenHeight()};
  DrawRectangleRec(history_view,SIDE_VIEW_COLOR);
}

void draw_request_maker(bool *drop_down_active, int *current_drop_down_active,char *buffer){
 
  
  int x = int(GetScreenWidth()*0.5) ;
  int y = 20;
  int height = 60;
  int width = 60;
  

  Rectangle drop_down = {x,y,width*1.5,height};
  Rectangle input_box = {x+drop_down.width,y,width*10,height};
  Rectangle btn = {input_box.width+input_box.x,y,width*2,height};

  GuiButton(btn,"SEND");
  GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x0492c7ff);
  GuiSetStyle(DEFAULT, BASE_COLOR_PRESSED, 0X33333333);
  GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0x000000ff);
  
  GuiSetStyle(DEFAULT, BASE_COLOR_FOCUSED, 0xffffffff);
  GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000ff);

 if (GuiDropdownBox(drop_down,"GET\nPOST\nDEL",current_drop_down_active,*drop_down_active)){
  *drop_down_active = !*drop_down_active;
 }

    
  GuiSetStyle(DEFAULT, BORDER_COLOR_PRESSED, 0x0492c7ff);
  GuiSetStyle(DEFAULT, TEXT_COLOR_PRESSED, 0xffffffffff);
  DrawRectangleRec(input_box,SIDE_VIEW_COLOR);
   
  GuiTextBox(input_box,buffer,250,true);


}

int main(void) {

  /*_____________________________________________Curl Init_____________________________________________*/


/*_____________________________________________Curl_____________________________________________*/

/*__________________________________________SORT OF WI________________________________________________________*/

const int screenHeight  = 720;
const int screenWidth = 1080;

  SetConfigFlags(FLAG_WINDOW_RESIZABLE);    
  InitWindow(screenWidth, screenHeight, "SneakyHttp");
  SetTargetFPS(60);

  bool is_active = false;
  int  current_drop_down_active=0;
  char buffer[URL_BUFFER];

    Font font = LoadFontEx("C:\\Users\\pulwa\\OneDrive\\Desktop\\discoe\\RequestMaker\\snkyHttp\\src\\ubuntu.ttf",50,NULL,0);
    GuiSetFont(font);
 
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {
    int currentWidth = GetScreenWidth();
    int currentHeight = GetScreenHeight();
     BeginDrawing();

    GuiSetStyle(DEFAULT, TEXT_SIZE, 20);                // DEFAULT, shared by all controls

    GuiSetStyle(DEFAULT, BORDER_WIDTH, 0);
     draw_history_section();
   draw_request_maker(&is_active,&current_drop_down_active, buffer);
    
     
      

      EndDrawing();
      ClearBackground(BACKGROUND_COLOR);

  }

  //--------------------------------------------------------------------------------------
   CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

