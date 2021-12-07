#pragma once

#if defined(_MSC_VER)
    #define EXPORT __declspec(dllexport)
    #define IMPORT __declspec(dllimport)
#elif defined(__GNUC__)
    #define EXPORT __attribute__((visibility("default")))
    #define IMPORT
#elif defiend(__APPLE__)
    #define EXPORT
    #define IMPORT
    #pragma warning Unknown dynamic link import/export semantics.
#endif

#if STLR_BUILD_DLL
    #define STLR_API EXPORT
#else
    #define STLR_API IMPORT
#endif

#define BIT(x) (1 << x)