#ifndef CAROTID_PLATFORM_H
#define CAROTID_PLATFORM_H

#ifndef CAROTID_NO_EXPORTS
#define CAROTID_EXPORTS
#endif
#if defined _WIN32 || defined __CYGWIN__
#ifdef CAROTID_EXPORTS
#ifdef _CAROTID_LIB_NO_EXPORTS_
#define CAROTID_LINKAGE __declspec(dllimport)
#else
#define CAROTID_LINKAGE __declspec(dllexport)
#endif
#endif
#elif defined(CAROTID_EXPORTS) && defined(__GNUC__)
#define CAROTID_LINKAGE __attribute__((visibility("default")))
#endif

#ifndef CAROTID_LINKAGE
#define CAROTID_LINKAGE
#endif

#ifdef __GNUC__
#define CAROTID_DEPRECATED __attribute__((deprecated))
#else
#ifdef _MSC_VER
#define CAROTID_DEPRECATED __declspec(deprecated)
#else
#define CAROTID_DEPRECATED
#endif
#endif

#endif