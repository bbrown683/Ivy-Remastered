#ifndef IVY_SYMBOLS_H
#define IVY_SYMBOLS_H

#ifndef IVY_STATIC_BUILD
    #ifdef IVY_EXPORT_SYMBOLS
        #define IVY_API __declspec(dllexport)
    #else
        #define IVY_API __declspec(dllimport)
    #endif // IVY_EXPORT_SYMBOLS
#else
    #define IVY_API
#endif  // IVY_STATIC_BUILD

#endif // IVY_SYMBOLS_H