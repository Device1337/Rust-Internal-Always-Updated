#include <Windows.h>
#include "includes.hpp"
#include "game/il2cpp.hpp"
#include "game/hooks.hpp"

void CreateConsole()
{

    if (!AllocConsole()) {
        //Add some error handling here.
        //You can call GetLastError() to get more info about the error.
        return;
    }

    //std::cout, std::clog, std::cerr, std::cin
    FILE* fDummy;
    freopen_s(&fDummy, "CONOUT$", "w", stdout);
    freopen_s(&fDummy, "CONOUT$", "w", stderr);
    freopen_s(&fDummy, "CONIN$", "r", stdin);
    std::cout.clear();
    std::clog.clear();
    std::cerr.clear();
    std::cin.clear();

    //std::wcout, std::wclog, std::wcerr, std::wcin
    HANDLE hConOut = CreateFile(("CONOUT$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    HANDLE hConIn = CreateFile(("CONIN$"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    SetStdHandle(STD_OUTPUT_HANDLE, hConOut);
    SetStdHandle(STD_ERROR_HANDLE, hConOut);
    SetStdHandle(STD_INPUT_HANDLE, hConIn);
    std::wcout.clear();
    std::wclog.clear();
    std::wcerr.clear();
    std::wcin.clear();
}

extern "C" __declspec(dllexport) int NextHook(int code, WPARAM wParam, LPARAM lParam) { return CallNextHookEx(NULL, code, wParam, lParam); }

BOOL APIENTRY DllMain(HMODULE hModule, DWORD callReason, LPVOID lpReserved)
{
    if (callReason == DLL_PROCESS_ATTACH)
    {
        CreateConsole();
       
        
            // convert now to string form
            //char* dt = ctime_s(&now);
            il2cpp::init();
            hooks::init();
           // std::cout << "DLL has been injected at: " << std::put_time(std::localtime(&t_c), "%F %T.\n") << std::endl;
        
    }
    return TRUE;
}


