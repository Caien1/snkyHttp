    // optional: only if you don’t draw shapes
#include <raylib.h>

#define RAYGUI_IMPLEMENTATION

#include "../include/raygui.h"

#define URL_SIZE 256

namespace curl{
#include "libcurlWrapper.h"
}
#define _WIN32 1

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 1024;
  const int screenHeight = 720;

  /*_____________________________________________Curl Init_____________________________________________*/
curl::Memory mem={0};
curl::RequestHandle *Handle=NULL;
curl::HeaderList *list=NULL;
curl::CurlInitialiseGlobal();

/*_____________________________________________Curl Init_____________________________________________*/

  InitWindow(screenWidth, screenHeight, "sneakyHttp");

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

    char buffer[URL_SIZE+1]="https://";
    Rectangle textBox = {10,10,screenWidth/2,35};

    Rectangle btn = {textBox.x+textBox.width, textBox.y,50,35 };
    Rectangle messageBox = {10,50,screenWidth/2+50,screenHeight/2};

    curl::GetReqObject ent;
  // Main game loop
  while (!WindowShouldClose()) // Detect window close button or ESC key
  {

     BeginDrawing();

      GuiTextBox(textBox,buffer,URL_SIZE+1,true);
      if(GuiButton(btn,"Send")){
        mem.size=0;
        ent.url = buffer;
        printf("%s",ent.url);

        Handle = curl::RequestHandleInit(Handle);
        Handle = curl::GetSetter(Handle,&ent);
        curl::WriteToMemory(Handle,(void*)&mem);
        curl::ResponseCode response = curl::SendRequest(Handle);
        if(response==curl::CURLE_OK){
}



      }
      GuiMessageBox(messageBox,"data",mem.response,"");

       ClearBackground( GRAY);
    


     EndDrawing();
  }

  //--------------------------------------------------------------------------------------
   CloseWindow(); // Close window and OpenGL context
  //--------------------------------------------------------------------------------------

  return 0;
}

