#ifndef DEFS_HPP
#define DEFS_HPP

#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <stdexcept>

#include <string>
#include <set>
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>
#include <stack>

#include <filesystem>

#include <ctime>
#include <time.h>

#include <clocale>

#include <limits.h>

#include <omp.h>

namespace fs = std::filesystem;

using uint = unsigned int;
using wchar = wchar_t;

using std::set;
using std::queue;
using std::stack;
using std::pair;
#define dict std::unordered_map
using std::map;

using fs::path;

using std::string;
using std::wstring;

using std::vector;

#define fseek _fseeki64

#define RED FOREGROUND_RED
#define GREEN FOREGROUND_GREEN
#define BLUE FOREGROUND_BLUE

#define wprintfc(color, format, ...)                               \
{                                                                  \
    SetConsoleTextAttribute(hConsole, color);                      \
    wprintf(format, __VA_ARGS__);                                  \
    SetConsoleTextAttribute(hConsole, RED | GREEN | BLUE);         \
}

#define ERROR_HANDLE(call, action, message, ...)                              \
do                                                                            \
{                                                                             \
    if(!(call))                                                               \
    {                                                                         \
        fwprintf(stdout, L"[ERROR] " message L"\n", __VA_ARGS__);             \
        action;                                                               \
    }                                                                         \
}                                                                             \
while(0);

#define WARNING_HANDLE(call, action, message, ...)                            \
do                                                                            \
{                                                                             \
    if(!(call))                                                               \
    {                                                                         \
        fwprintf(stdout, L"[WARNING] " message L"\n", __VA_ARGS__);           \
        action;                                                               \
    }                                                                         \
}                                                                             \
while(0);

#define INFO_HANDLE(message, ...)                                   \
do                                                                  \
{                                                                   \
     fwprintf(stdout, L"[INFO] " message L"\n", __VA_ARGS__);       \
}                                                                   \
while(0);

#define NOTIFY(current_sec, delay, message, ...)   \
{                                                  \
    current_time = time(NULL);                     \
                                                   \
    if (current_time - current_sec > delay)        \
    {                                              \
        wprintf(message, __VA_ARGS__);             \
        current_sec = current_time;                \
    }                                              \
}

#define foreach(ptr, container) for(auto ptr = (container).begin(); ptr != (container).end(); ptr++)

void wsystem(const wchar *com)
{
    wchar buffer[256];
    FILE *pipe = _wpopen(com, L"rt");
    if (!pipe) throw std::runtime_error("popen() failed!");

    try 
    {
        while (fgetws(buffer, 256, pipe))
        {
            wprintf(L"%s", buffer);
        }
    }
    catch (...) 
    {
        _pclose(pipe);
        throw;
    }
    _pclose(pipe);
}

struct item
{
    uint offset;
    int df;
};

#endif