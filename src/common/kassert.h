#ifndef KASSERT_H_
#define KASSERT_H_

#include <stdio.h> 

#ifndef KASSERT_DEBUG_ON
    #define KASSERT_DEBUG_ON 0
#endif

void print_error(
        const char* message,
        const char* file_name,
        int line_num,
        const char* func,
        const char* expr,
        ...
);

#define KASSERT(expr) \
    do{ \
        if (!(expr)) { \
            print_error("", __FILE__, __LINE__, __func__, #expr);\
            __builtin_trap(); \
        } \
    }while(0)

#define KASSERT_MSG(expr, message, ...) \
    do{ \
        if (!(expr)) { \
            print_error(message, __FILE__, __LINE__, __func__, #expr, ##__VA_ARGS__);\
            __builtin_trap(); \
        } \
    }while(0)

#if KASSERT_DEBUG_ON

    #define KASSERT_DEBUG(expr) \
        do{ \
            if (!(expr)) { \
                print_error("", __FILE__, __LINE__, __func__, #expr);\
                __builtin_trap(); \
            } \
        }while(0)
    
    #define KASSERT_DEBUG_MSG(expr, message, ...) \
        do{ \
            if (!(expr)) { \
                print_error(message, __FILE__, __LINE__, __func__, #expr, ##__VA_ARGS__);\
                __builtin_trap(); \
            } \
        }while(0)

#else

    #define KASSERT_DEBUG(expr)
    #define KASSERT_DEBUG_MSG(expr, message, ...)

#endif

#endif // KASSERT_H_
