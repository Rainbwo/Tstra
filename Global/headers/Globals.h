/**
 * @file Globals.h
 * @author zhang tao (zhang_tao123@foxmail.com)
 * @brief
 * @version 0.1
 * @date 2023-11-30
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef _INC_TSTRA_GLOBALS
#define _INC_TSTRA_GLOBALS

#ifdef _MSC_VER
/// disable warning: 'fopen' was declared deprecated
#pragma warning(disable : 4996) //< 禁用编号为4996的警告('fopen'已被声明为不推荐使用)
/// disable warning: C++ exception handler used, but unwind semantics are not enables
#pragma warning(disable : 4530) //< 禁用编号为4530的警告(使用了C++异常处理程序，但未启用异常处理语义)
/// disable warning: no suitable definition provided for explict template instantiation request
#pragma warning(disable : 4661) //< 禁用编号为4661的警告(未提供适合的显式模板实例化请求的定义)

#endif

#include <cassert>
#include <iostream>
#include <fstream>
#include <math.h>

#define TSTRA_TOOLBOXVERSION_MAJOR 1
#define TSTRA_TOOLBOXVERSION_MINOR 0
#define TSTRA_TOOLBOXVERSION ((TSTRA_TOOLBOXVERSION_MAJOR) * 100 + (TSTRA_TOOLBOXVERSION_MINOR))
#define TSTRA_TOOLBOXVERSION_STRING "1.0.0"

#define TSTRA_ASSERT(a) assert(a)

#define TSTRA_CONFIG_CHECK(value, type, msg)                                       \
    if (!(value))                                                                  \
    {                                                                              \
        std::cout << "Configuration Error in" << type << ": " << msg << std::endl; \
        return false;                                                              \
    }

#define TSTRA_CONFIG_WARNING(type, msg)                                 \
    {                                                                   \
        std::cout << "Warning in " << type << ": " << msg << std::endl; \
    }

#define TSTRA_DELETE(a) \
    if (a)              \
    {                   \
        delete a;       \
        a = NULL;       \
    }
#define TSTRA_DELETE(a) \
    if (a)              \
    {                   \
        delete[] a;     \
        a = NULL;       \
    }

#ifdef _MSC_VER

#ifdef DLL_EXPORTS
#define _TstraExport __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define _TstraExport __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif

#else

#define _TstraExport

#endif

namespace tstra
{
    typedef float float32;
    typedef double float64;
    typedef unsigned short int uint16;
    typedef unsigned short int sint16;
    typedef unsigned char uchar8;
    typedef signed char schar8;

    typedef int int32;
    typedef short int int16;
}

namespace tstra
{
    const float32 PI = 3.1415926535897932384f;
    const float32 PI32 = 3.1415926535897932384f;
    const float32 PIdiv2 = PI / 2;
    const float32 PIdiv4 = PI / 4;
    const float32 eps = 1e-6f;

    extern _TstraExport bool running_in_matlab;
}

namespace tstra
{
    /**
     * @brief
     * Struct for storing pixel weights
     */
    struct SPixelWeight
    {
        int m_iIndex;
        float32 m_fWeight;
    };

    /**
     * @brief
     * Struct combining properties of a detector in 1D detector row
     */
    struct SDetector2D
    {
        int m_iIndex;
        int m_iAngleIndex;
        int m_iDetectorIndex;
    };

    /**
     * @brief
     * Struct combining some properties of a detector in 2D detector array
     */
    struct SDetector3D
    {
        int m_iIndex;
        int m_iAngleIndex;
        int m_iDetectorIndex;
        int m_iSliceIndex;
    };
}

namespace tstra
{
    _TstraExport void setShouldAbortHook(bool (*pShouldAbortHook)(void));

    _TstraExport bool shouldAbort();
}

namespace tstra
{
    _TstraExport inline int getVersion() { return TSTRA_TOOLBOXVERSION; }
    _TstraExport inline const char *getVersionString() { return TSTRA_TOOLBOXVERSION_STRING; }
    _TstraExport bool cudaAvailable();
#ifdef TSTRA_CUDA
    _TstraExport inline bool cudaEnabled() { return true; }
#else
    _TstraExport inline bool cudaEnabled() { return false; }
#endif // TSTRA_CUDA
};

// #ifndef _MSC_VER
// #define EXPIMP_TEMPLATE

// #if !define(FORCEINLINE) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 1))
// #define FORCEINLINE inline __attribute__((__always_inline__))
// #else
// #define FORCEINLINE inline
// #endif
// #else
#define FORCEINLINE __forceinline
// #endif

#if defined(__linux__) || defined(__MACH__)
#define USE_PTHREADS
#endif

#endif