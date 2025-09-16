#include <stdio.h>
#include <curl/curl.h>
#include "libcurlWrapper.h"
typedef CURL RequestHandle;
 

int main(void)
{
  RequestHandle *Handle;
  CurlIntialiseGlobal();

  GetObject Obj;
  Obj.url="https://google.com/";
  Obj.redirect=1;

  Handle = RequestHandleInit(Handle);
  Handle = GetSetter(Handle,&Obj);

  ResponseCode response = curl_easy_perform(Handle);

    if(response != CURLE_OK){
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(response));
  }
  HttpStatusCode statusCode =0;
  curl_easy_getinfo(Handle,CURLINFO_RESPONSE_CODE,&statusCode);
  
  printf("%ln",statusCode);




  curl_easy_cleanup(Handle);


  CurlDestroyGlobal();
 
  return 0;
}