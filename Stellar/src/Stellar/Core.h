#pragma once

#if defined(_MSC_VER)
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
    #define DEBUG_BREAK __debugbreak()
#elif defined(__GNUC__)
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
    #define DEBUG_BREAK raise(SIGTRAP)
#elif defiend(__APPLE__)
    #define EXPORT
    #define IMPORT
    #include <signal.h>
    #define DEBUG_BREAK rais(SIGTRAP)
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if STLR_BUILD_DLL
    #define STLR_API EXPORT
#else
    #define STLR_API IMPORT
#endif

#define BIT(x) (1 << x)