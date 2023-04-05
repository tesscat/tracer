
#ifndef UTILSCPP_EXPORT_H
#define UTILSCPP_EXPORT_H

#ifdef OPENCLUTILSCPP_STATIC_DEFINE
#  define UTILSCPP_EXPORT
#  define OPENCLUTILSCPP_NO_EXPORT
#else
#  ifndef UTILSCPP_EXPORT
#    ifdef OpenCLUtilsCpp_EXPORTS
        /* We are building this library */
#      define UTILSCPP_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define UTILSCPP_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef OPENCLUTILSCPP_NO_EXPORT
#    define OPENCLUTILSCPP_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef OPENCLUTILSCPP_DEPRECATED
#  define OPENCLUTILSCPP_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef OPENCLUTILSCPP_DEPRECATED_EXPORT
#  define OPENCLUTILSCPP_DEPRECATED_EXPORT UTILSCPP_EXPORT OPENCLUTILSCPP_DEPRECATED
#endif

#ifndef OPENCLUTILSCPP_DEPRECATED_NO_EXPORT
#  define OPENCLUTILSCPP_DEPRECATED_NO_EXPORT OPENCLUTILSCPP_NO_EXPORT OPENCLUTILSCPP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENCLUTILSCPP_NO_DEPRECATED
#    define OPENCLUTILSCPP_NO_DEPRECATED
#  endif
#endif

#endif /* UTILSCPP_EXPORT_H */
