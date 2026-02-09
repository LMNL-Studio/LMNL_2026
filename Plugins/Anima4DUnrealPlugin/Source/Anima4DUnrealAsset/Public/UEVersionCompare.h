#pragma once

#include "Runtime/Launch/Resources/Version.h"

// Check if engine version is equal or newer or equal to
#define ENGINE_VERSION_AT_LEAST(major, minor) \
    ((ENGINE_MAJOR_VERSION > (major)) || \
    (ENGINE_MAJOR_VERSION == (major) && ENGINE_MINOR_VERSION >= (minor)))

// Check if engine version is equal or older or equal to
#define ENGINE_VERSION_AT_MOST(major, minor) \
    ((ENGINE_MAJOR_VERSION < (major)) || \
    (ENGINE_MAJOR_VERSION == (major) && ENGINE_MINOR_VERSION <= (minor)))


#if ENGINE_VERSION_AT_LEAST(5,6)
    #define CHECK_RENDER_THREAD() checkSlow(IsInRenderingThread() || IsInParallelRenderingThread())
#else
    #define CHECK_RENDER_THREAD() check(IsInRenderingThread())
#endif