
#ifndef UTILS_EXPORT_H
#define UTILS_EXPORT_H

#ifdef OPENCLUTILS_STATIC_DEFINE
#  define UTILS_EXPORT
#  define OPENCLUTILS_NO_EXPORT
#else
#  ifndef UTILS_EXPORT
#    ifdef OpenCLUtils_EXPORTS
        /* We are building this library */
#      define UTILS_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define UTILS_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef OPENCLUTILS_NO_EXPORT
#    define OPENCLUTILS_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef OPENCLUTILS_DEPRECATED
#  define OPENCLUTILS_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef OPENCLUTILS_DEPRECATED_EXPORT
#  define OPENCLUTILS_DEPRECATED_EXPORT UTILS_EXPORT OPENCLUTILS_DEPRECATED
#endif

#ifndef OPENCLUTILS_DEPRECATED_NO_EXPORT
#  define OPENCLUTILS_DEPRECATED_NO_EXPORT OPENCLUTILS_NO_EXPORT OPENCLUTILS_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENCLUTILS_NO_DEPRECATED
#    define OPENCLUTILS_NO_DEPRECATED
#  endif
#endif

#endif /* UTILS_EXPORT_H */
