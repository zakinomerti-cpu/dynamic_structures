#ifndef _STDINT_H_
#define _STDINT_H_

typedef signed char        int8_t;
typedef unsigned char      uint8_t;
typedef short              int16_t;
typedef unsigned short     uint16_t;

#if defined(_MSC_VER)
typedef __int32            int32_t;
typedef unsigned __int32   uint32_t;
typedef __int64            int64_t;
typedef unsigned __int64   uint64_t;
#else
    /* Для обычного ANSI C (где int может быть 16 или 32 бита) */
    /* Обычно long гарантированно >= 32 бит */
typedef long               int32_t;
typedef unsigned long      uint32_t;
typedef long long          int64_t;
typedef unsigned long long uint64_t;
#endif

#endif
