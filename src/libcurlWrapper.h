#include <curl/curl.h>
#include <string.h>
#include <cstdlib>



typedef CURL RequestHandle;
typedef CURLcode ResponseCode;
typedef long HttpStatusCode;


typedef struct{
    char *url;
    char *body;
    long  redirect;
    char* fields;
}PostObject;


typedef struct{
    char *url;
    char *query;
    long  redirect;
}GetObject;

typedef struct{
    char* response;
    size_t size;
}memory;

//////////////////////////////////////////////////////////////////////////////////////////////

void CurlIntialiseGlobal();
void CurlDestroyGlobal();


RequestHandle* RequestHandleInit(RequestHandle*);
void RequestHandleCleaner(RequestHandle*);

//Request Wrappers
RequestHandle* GetSetter(RequestHandle*,GetObject*);
ResponseCode SendRequest(RequestHandle* Handle);




//Todo:Make a function(Write call back)

static size_t MemoryCallbackWrite(char *data, size_t size, size_t nmemb, void *clientp);

                      
////////////////////////////////////////////////////////////////////////////////////////////

void CurlIntialiseGlobal(){
    curl_global_init(CURL_GLOBAL_ALL);
}


void CurlDestroyGlobal(){
    curl_global_cleanup();
}




RequestHandle* GetSetter(RequestHandle* Handle,GetObject* getHandle){

    curl_easy_setopt(Handle, CURLOPT_URL, getHandle->url);
    curl_easy_setopt(Handle,CURLOPT_FOLLOWLOCATION,getHandle->redirect);
    curl_easy_setopt(Handle, CURLOPT_SSL_VERIFYPEER, 0L);
   // curl_easy_setopt(Handle, CURLOPT_WRITEFUNCTION, MemoryCallbackWrite);

    return Handle;

}

RequestHandle* PostSetter(RequestHandle* Handle,PostObject* postHandle){

    curl_easy_setopt(Handle, CURLOPT_URL, postHandle->url);
    curl_easy_setopt(Handle,CURLOPT_FOLLOWLOCATION,postHandle->redirect);
    curl_easy_setopt(Handle, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(Handle,CURLOPT_POST,1L);

    curl_easy_setopt(Handle,CURLOPT_POSTFIELDS,postHandle->fields);
    
    curl_easy_setopt(Handle, CURLOPT_WRITEFUNCTION, MemoryCallbackWrite);

    return Handle;

}




RequestHandle* RequestHandleInit(RequestHandle* Handle){
    Handle = curl_easy_init();
    return Handle;
}


void RequestHandleCleaner(RequestHandle* Handle){
    curl_easy_cleanup(Handle);
}

ResponseCode SendRequest(RequestHandle* Handle){
    ResponseCode response = curl_easy_perform(Handle);
    if(response != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n",
        curl_easy_strerror(response));
  }
  return response;
}

static size_t MemoryCallbackWrite(char *data, size_t size, size_t nmemb, void *clientp)
{
  size_t realsize = size * nmemb;
   memory *mem = ( memory *)clientp;
 
  char *ptr = (char*)realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0; 
 
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
 
  return realsize;
}