#include <windows.h>
#include<iostream>



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    PSTR lpCmdLine, int nCmdShow)
{

    HANDLE dirHandle = CreateFileA("./src/", FILE_LIST_DIRECTORY,
             FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
             NULL,OPEN_EXISTING,FILE_FLAG_BACKUP_SEMANTICS,0);
    
             if(dirHandle==INVALID_HANDLE_VALUE){
        std::cerr<<"Cant open this directory";
        return 1;
    }

     char buffer[1024];
    DWORD bytesReturned;

    while (true) {
        std::cout<<"FileWatcher is listening to the changes"<<std::endl;
        BOOL success = ReadDirectoryChangesW(
            dirHandle,
            &buffer,
            sizeof(buffer),
            TRUE, 
            FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
            &bytesReturned,
            NULL,
            NULL);

        if (!success) {
            std::cerr << "ReadDirectoryChangesW failed\n";
            break;
        }

        FILE_NOTIFY_INFORMATION* fni = (FILE_NOTIFY_INFORMATION*)buffer;

        std::wcout << L"Change detected: "
                   << std::wstring(fni->FileName, fni->FileNameLength / sizeof(WCHAR))
                   << std::endl;

        //RUN THEM BUILD SCRIPTs
        system("pwd");
        system("build.bat");
       system("run.bat");
    }

    CloseHandle(dirHandle);
    return 0;
}

 