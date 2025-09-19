#include <stdio.h>
#include <curl/curl.h>
#include "libcurlWrapper.h"

 

int main(void)
{

Memory mem={0};
RequestHandle *Handle=NULL;
HeaderList *list=NULL;

CurlInitialiseGlobal();

  GetReqObject Obj;
  Obj.url="https://google.com/";
  Obj.redirect=0;


Handle = RequestHandleInit(Handle);

Handle = GetSetter(Handle,&Obj);
list = AddHeader(list,"Hello: Test");
list = AddHeader(list,"Param2: Test");
list = AddHeader(list,"Param3: Test");
Handle = SetCustomHeaders(Handle,list);


Handle = SetCustomHeaders(Handle, list);

ResponseCode response = SendRequest(Handle);

if(response==CURLE_OK){
  printf("Okay\n");
}


    
       
       


RequestHandleCleaner(Handle);
CurlDestroyGlobal();


  return 0;
}