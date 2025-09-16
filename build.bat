mkdir bin
g++ .\src\libcurlWrapper.cpp -o .\bin\test.exe -I.\src -lcurl -Wall -lssl -lcrypto -lz -lws2_32 -lcrypt32 -lwldap32  -DCURL_STATICLIB