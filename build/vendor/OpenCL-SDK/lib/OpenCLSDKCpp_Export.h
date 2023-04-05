
#ifndef SDKCPP_EXPORT_H
#define SDKCPP_EXPORT_H

#ifdef OPENCLSDKCPP_STATIC_DEFINE
#  define SDKCPP_EXPORT
#  define OPENCLSDKCPP_NO_EXPORT
#else
#  ifndef SDKCPP_EXPORT
#    ifdef OpenCLSDKCpp_EXPORTS
        /* We are building this library */
#      define SDKCPP_EXPORT __attribute__((visibility("default")))
#    else
        /* We are using this library */
#      define SDKCPP_EXPORT __attribute__((visibility("default")))
#    endif
#  endif

#  ifndef OPENCLSDKCPP_NO_EXPORT
#    define OPENCLSDKCPP_NO_EXPORT __attribute__((visibility("hidden")))
#  endif
#endif

#ifndef OPENCLSDKCPP_DEPRECATED
#  define OPENCLSDKCPP_DEPRECATED __attribute__ ((__deprecated__))
#endif

#ifndef OPENCLSDKCPP_DEPRECATED_EXPORT
#  define OPENCLSDKCPP_DEPRECATED_EXPORT SDKCPP_EXPORT OPENCLSDKCPP_DEPRECATED
#endif

#ifndef OPENCLSDKCPP_DEPRECATED_NO_EXPORT
#  define OPENCLSDKCPP_DEPRECATED_NO_EXPORT OPENCLSDKCPP_NO_EXPORT OPENCLSDKCPP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef OPENCLSDKCPP_NO_DEPRECATED
#    define OPENCLSDKCPP_NO_DEPRECATED
#  endif
#endif

#endif /* SDKCPP_EXPORT_H */
