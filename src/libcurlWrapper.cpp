#include <stdio.h>
#include <curl/curl.h>
#include "libcurlWrapper.h"
 

int main(void)
{

Memory mem={0};
RequestHandle *Handle;
HeaderList *list;
CurlIntialiseGlobal();


  GetObject Obj;
  Obj.url="https://www.purgomalum.com/service/json?text=this";
  Obj.redirect=0;


Handle = RequestHandleInit(Handle);
Handle = GetSetter(Handle,&Obj);
Handle = WriteToMemory(Handle, (void*)&mem);
VerboseOutput(Handle);
ResponseCode response = SendRequest(Handle);



RequestHandleCleaner(Handle);
CurlDestroyGlobal();

printf("%s", mem.response);

  return 0;
}