#include "SDK.h"

_Py_SetProgramName Py_SetProgramName;
_PyEval_InitThreads PyEval_InitThreads;
_PyGILState_Ensure PyGILState_Ensure;
_PyGILState_Release PyGILState_Release;
_PyRun_SimpleStringFlags PyRun_SimpleStringFlags;

void SDK::InitCPython()
{
    HMODULE hPython = 0x0;
    const char* pythonVersions[] = { "37", "38", "39", "310", "311", "312" };
    const int numVersions = sizeof(pythonVersions) / sizeof(pythonVersions[0]);

    for (int i = 0; i < numVersions; ++i) {
        char pythonDllName[15];
        snprintf(pythonDllName, sizeof(pythonDllName), "Python%s.dll", pythonVersions[i]);

        hPython = GetModuleHandleA(pythonDllName);
        
        if (hPython)
            break;
    }

    Py_SetProgramName = (_Py_SetProgramName)(GetProcAddress(hPython, "Py_SetProgramName"));
    PyEval_InitThreads = (_PyEval_InitThreads)(GetProcAddress(hPython, "PyEval_InitThreads"));
    PyGILState_Ensure = (_PyGILState_Ensure)(GetProcAddress(hPython, "PyGILState_Ensure"));
    PyGILState_Release = (_PyGILState_Release)(GetProcAddress(hPython, "PyGILState_Release"));
    PyRun_SimpleStringFlags = (_PyRun_SimpleStringFlags)(GetProcAddress(hPython, "PyRun_SimpleStringFlags"));
}
