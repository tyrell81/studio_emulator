/* Copyright Prosoft-Biometrics */


#ifndef PB_PROTOCOL_SHAREDLIB_H_
#define PB_PROTOCOL_SHAREDLIB_H_


#if defined(__linux__) || defined(__linux)
#  define OS_LINUX
#elif !defined(SAG_COM) && (!defined(WINAPI_FAMILY) || WINAPI_FAMILY==WINAPI_FAMILY_DESKTOP_APP) && (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))
#  define OS_WIN
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__))
#  define OS_WIN
#endif


#ifdef OS_LINUX
#  define PB_EXPORT     __attribute__((visibility("default")))
#  define PB_IMPORT     __attribute__((visibility("default")))
#elif defined(OS_WIN)
#  define PB_EXPORT     __declspec(dllexport)
#  define PB_IMPORT     __declspec(dllimport)
#else
#  error "Compiler not support(see sharedlib.h)"
#endif


#if defined(PB_PROTOCOL_SHAREDLIB_LIBRARY)
#  define PB_PROTOCOL_EXPORT PB_EXPORT
#else
#  define PB_PROTOCOL_EXPORT PB_IMPORT
#endif


#endif  // PB_SHAREDLIB_H_
