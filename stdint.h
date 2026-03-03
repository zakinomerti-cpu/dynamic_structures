#ifndef _STDINT_H_
#define _STDINT_H_

#ifdef _MSC_VER

typedef signed __int8       int8_t;
typedef unsigned __int8     uint8_t;

typedef signed __int16      int16_t;
typedef unsigned __int16    uint16_t;

typedef signed __int32      int32_t;
typedef unsigned __int32    uint32_t;

typedef signed __int64      int64_t;
typedef unsigned __int64    uint64_t;

/* pointer-sized */
#ifdef _WIN64
typedef signed __int64      intptr_t;
typedef unsigned __int64    uintptr_t;
#else
typedef signed __int32      intptr_t;
typedef unsigned __int32    uintptr_t;
#endif

#endif

#endif