
#include "libcurlWrapper.h"
#include<iostream>

//keep this one in snake case

RequestHandle* generate_handle(){ //seems useless cause its doing the same stuff need to rethink this one 
    RequestHandle *handle =NULL;
     handle =RequestHandleInit(handle);
        return handle;
}



Memory* get_request(GetReqObject * ent, RequestHandle* handle){


Memory *mem =   new(std::nothrow)Memory;
if (mem == nullptr)
        {
            std::cout << "Allocation returned nullptr\n";
            mem->size =-1;
            return mem;
        }
 handle = GetSetter(handle, ent);
 handle = WriteToMemory(handle, (void*)&mem);
 ResponseCode code = SendRequest(handle);
 return mem;

}

void free_allocated_mem(Memory *mem){
    delete mem;
}

void post_request(){

}
