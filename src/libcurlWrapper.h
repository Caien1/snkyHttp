#include <curl/curl.h>
#include <string.h>
#include <cstdlib>


#ifndef LIBCURL_WRAPPER
#define  LIBCURL_WRAPPER
typedef CURL RequestHandle;
typedef CURLcode ResponseCode;
typedef long HttpStatusCode;
typedef curl_slist HeaderList;
typedef enum{GET,POST,PUT,DEL}HttpMethod;

typedef struct 
{
    char* url;
    HttpStatusCode response_code;
    double elapsed;
}RequestInfo;


typedef struct { //standard  thinking of using this instead of instead of seprate GET POST AND other reqs 
    HttpMethod HttpMethod;
   const char *url;
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
}DeleteReqObject;

typedef struct{
    const char *url;
    char *query;
    long  redirect;
}GetReqObject;

typedef struct{
    char* response;
    size_t size;
}memory,Memory;

/*_________________________________FUNCTIONS____________________________________*/


/*_____INITLISERS________*/
void CurlInitialiseGlobal();
void CurlDestroyGlobal();

RequestHandle* RequestHandleInit(RequestHandle*);
void RequestHandleCleaner(RequestHandle*);

void ClearHeaderList(HeaderList *);

/*___________DEBUGGER/ANALYSER____________*/
void VerboseOutput(RequestHandle*);
void RequestInformation(RequestInfo *);



    
/*____________REQUEST WRAPPERS_________*/
RequestHandle* GetSetter(RequestHandle*, GetReqObject*);
RequestHandle* PostSetter(RequestHandle*, PostObject*);
RequestHandle* DeleteSetter(RequestHandle*,DeleteReqObject*);
ResponseCode SendRequest(RequestHandle*);



/*__________________HEADER SETTERS___________*/
HeaderList* AddHeader(HeaderList*,const char * );  
RequestHandle* SetCustomHeaders(RequestHandle*,HeaderList*);





/*_____________MEMORY_WRITE___________*/
static size_t MemoryCallbackWrite(char *, size_t, size_t, void *);
RequestHandle* WriteToMemory(RequestHandle* ,void* );

#endif                      
/*_________________________________IMPLEMENTATION_________________*/

void CurlInitialiseGlobal(){
    curl_global_init(CURL_GLOBAL_ALL);
}

void CurlDestroyGlobal(){
    curl_global_cleanup();
}

RequestHandle* GetSetter(RequestHandle* Handle,GetReqObject* getHandle){

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

HeaderList* AddHeader(HeaderList* headerList,const char* header ){
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

void RequestInformation(RequestHandle* Handle,RequestInfo *info){

         curl_easy_getinfo(Handle, CURLINFO_RESPONSE_CODE, info->response_code);
        curl_easy_getinfo(Handle, CURLINFO_TOTAL_TIME, info->elapsed);
        curl_easy_getinfo(Handle, CURLINFO_EFFECTIVE_URL, info->url);

}
