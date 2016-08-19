/*
 *  File:     NXPlatform.h
 *  Author:   张雄
 *  Date:     2016_08_19
 *  Purpose:  定义平台相关的东西
 */

#pragma once

#if defined(_MSC_VER)
#if defined(WINRT)
#define PLATFORM_WINRT 1
#else
#define PLATFORM_WINDOWS 1
#endif

#if defined(_WIN64)
#define PLATFORM_64 1
#elif defined(_WIN32)
#define PLATFORM_32 1
#endif
#elif defined(__ANDROID__)
#define PLATFORM_ANDROID 1
#if defined(__x86_64__) || defined(__aarch64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#elif defined(__linux__)
#define PLATFORM_LINUX 1
#if defined(__x86_64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#elif defined(__APPLE__)
#if defined(TARGET_IPHONE_SIMULATOR) || defined(TARGET_OS_IOS)
#define PLATFORM_IOS 1
#else
#define PLATFORM_OSX 1
#endif

#if defined(__x86_64__) || defined(__arm64__)
#define PLATFORM_64 1
#else
#define PLATFORM_32 1
#endif
#endif

#endif //!__ZX_NXENGINE_CORE_H__