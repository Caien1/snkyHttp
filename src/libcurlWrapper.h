#include <curl/curl.h>
#include <string.h>
#include <cstdlib>



typedef CURL RequestHandle;
typedef CURLcode ResponseCode;
typedef long HttpStatusCode;
typedef curl_slist HeaderList;
typedef enum{GET,POST,PUT,DELETE}HttpMethod;



typedef struct {
    HttpMethod HttpMethod;
    char *url;
    char *body;
    long  redirect;
    char* fields;
    HeaderList *headers;
}HttpRequest;

typedef struct{
    char *url;
    char *body;
    long  redirect;
    char* fields;
}PostObject;

typedef struct{
    char *url;
    char *body;
    char *fields;
}DeleteObject;




typedef struct{
    char *url;
    char *query;
    long  redirect;
}GetObject;

typedef struct{
    char* response;
    size_t size;
}memory,Memory;

//////////////////////////////////////////////////////////////////////////////////////////////

// Curl Specific Initialisers 
void CurlIntialiseGlobal();
void CurlDestroyGlobal();

RequestHandle* RequestHandleInit(RequestHandle*);
void RequestHandleCleaner(RequestHandle*);

void ClearHeaderList(HeaderList *);

//debugging
void VerboseOutput(RequestHandle*);

    
//Request Wrappers

RequestHandle* GetSetter(RequestHandle*, GetObject*);
RequestHandle* PostSetter(RequestHandle*, PostObject*);
RequestHandle* DeleteSetter(RequestHandle*,DeleteObject*);
ResponseCode SendRequest(RequestHandle*);
RequestHandle* SetCustomHeaders(RequestHandle*,HeaderList*);
//HttpHeaderSetters
HeaderList* AddHeader(HeaderList*,char * );  






//Todo:Make a function(Write call back)
//Memory Stuff
static size_t MemoryCallbackWrite(char *, size_t, size_t, void *);
RequestHandle* WriteToMemory(RequestHandle* ,void* );

                      
////////////////////////////////////////////////////////////////////////////////////////////

void CurlIntialiseGlobal(){
    curl_global_init(CURL_GLOBAL_ALL);
}

void CurlDestroyGlobal(){
    curl_global_cleanup();
}

RequestHandle* GetSetter(RequestHandle* Handle,GetObject* getHandle){

    curl_easy_setopt(Handle, CURLOPT_URL, getHandle->url);
    curl_easy_setopt(Handle, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(Handle,CURLOPT_FOLLOWLOCATION,getHandle->redirect);
    curl_easy_setopt(Handle, CURLOPT_SSL_VERIFYPEER, 0L);
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
   Memory *mem = ( Memory *)clientp;
 
  char *ptr = (char*)realloc(mem->response, mem->size + realsize + 1);
  if(!ptr)
    return 0; 
 
  mem->response = ptr;
  memcpy(&(mem->response[mem->size]), data, realsize);
  mem->size += realsize;
  mem->response[mem->size] = 0;
 
  return realsize;
}

RequestHandle* WriteToMemory(RequestHandle* Handle,void* WritePtr ){
    curl_easy_setopt(Handle, CURLOPT_WRITEFUNCTION, MemoryCallbackWrite);
    curl_easy_setopt(Handle, CURLOPT_WRITEDATA, WritePtr);
    return Handle;
}

HeaderList* AddHeader(HeaderList* headerList, char* header ){
     headerList=curl_slist_append(headerList,header);
     return headerList;
}  

RequestHandle* SetCustomHeaders(RequestHandle* Handle, HeaderList* headerList ){
   curl_easy_setopt(Handle, CURLOPT_HTTPHEADER, headerList);
   return Handle;
}
 
void ClearHeaderList(HeaderList * headerList){
        curl_slist_free_all(headerList);
};

void VerboseOutput(RequestHandle* Handle){

    curl_easy_setopt(Handle,CURLOPT_VERBOSE,1L);

}
