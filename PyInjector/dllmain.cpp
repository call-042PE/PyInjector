#include "SDK.h"

SDK sdk;

DWORD WINAPI MainThread(HMODULE hModule)
{
    sdk.InitCPython();
    Py_SetProgramName(sdk.random_string(10).c_str()); // IDK IF YOU CAN FLAG THE OLD NAME PYINJECTOR BUT CHANGED ANYWAY
    PyEval_InitThreads();

    PyGILState_STATE s = PyGILState_Ensure();
    PyRun_SimpleString(sdk.ReadFile("code.py").c_str());
    //PyRun_SimpleString("import os, inspect\nwith open(\"code.py\",\"r\") as file:\n   data = file.read()\nexec(data)"); // OLD METHOD EASILY "BYPASSABLE" BY CREATING A JUNK METHOD NAMED EXEC
    PyGILState_Release(s);
    FreeLibraryAndExitThread(hModule, 0);
    CloseHandle(hModule);
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, 0));
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

