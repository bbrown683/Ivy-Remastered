#ifndef IVYAPI_H
#define IVYAPI_H

#ifndef IVY_STATIC_BUILD
    #ifdef IVY_EXPORT_SYMBOLS
        #define IVY_API __declspec(dllexport)
    #else
        #define IVY_API __declspec(dllimport)
    #endif // IVY_EXPORT_SYMBOLS
#else
    #define IVY_API
#endif  // IVY_STATIC_BUILD

#endif // IVYAPI_H