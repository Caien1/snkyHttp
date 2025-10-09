#define RAYGUI_IMPLEMENTATION
#include "../include/raygui.h"

#include <stdio.h>

typedef struct drop_down{
    Rectangle coords;
    char * items;
    int active;
    bool edit;
}DropDown;
void drop_down_widget(DropDown* dropDown){
if(GuiDropdownBox(dropDown->coords,dropDown->items,&dropDown->active,dropDown->edit)){
    dropDown->edit= !dropDown->edit;
    }

}

typedef struct text_box{
    Rectangle coords;
    char* url;
    int size;
    bool edit;
}TextBox;
void text_box_widget(TextBox * textBox,bool *flag){
textBox->edit = true;
if(GuiTextBox(textBox->coords,textBox->url,textBox->size,textBox->edit)){
  *flag = true;
}
}


void scroll_response(){
    


    
}
