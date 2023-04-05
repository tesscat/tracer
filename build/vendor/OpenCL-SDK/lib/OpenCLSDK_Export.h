
#ifndef SDK_EXPORT_H
#define SDK_EXPORT_H

#ifdef OPENCLSDK_STATIC_DEFINE
#  define SDK_EXPORT
#  define OPENCLSDK_NO_EXPORT
#else
#  ifndef SDK_EXPORT
#    ifdef OpenCLSDK_EXPORTS
        /* We are building this library */
#      define SDK_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SDK_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef OPENCLSDK_NO_EXPORT
#    define OPENCLSDK_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef OPENCLSDK_DEPRECATED
#  define OPENCLSDK_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef OPENCLSDK_DEPRECATED_EXPORT
#  define OPENCLSDK_DEPRECATED_EXPORT SDK_EXPORT OPENCLSDK_DEPRECATED
#endif

#ifndef OPENCLSDK_DEPRECATED_NO_EXPORT
#  define OPENCLSDK_DEPRECATED_NO_EXPORT OPENCLSDK_NO_EXPORT OPENCLSDK_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENCLSDK_NO_DEPRECATED
#    define OPENCLSDK_NO_DEPRECATED
#  endif
#endif

#endif /* SDK_EXPORT_H */
