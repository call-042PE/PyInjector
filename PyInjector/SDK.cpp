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

std::string SDK::ReadFile(std::string filename) {
    std::ifstream t(filename);
    std::string str((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    return str;
}

std::wstring SDK::random_string(std::size_t length)
{
    const std::wstring CHARACTERS = L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

    std::random_device random_device;
    std::mt19937 generator(random_device());
    std::uniform_int_distribution<> distribution(0, CHARACTERS.size() - 1);

    std::wstring random_string;

    for (std::size_t i = 0; i < length; ++i)
    {
        random_string += CHARACTERS[distribution(generator)];
    }

    return random_string;
}