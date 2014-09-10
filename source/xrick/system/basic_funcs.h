/*
 * system/basic_funcs.h
 *
 * The use and distribution terms for this software are contained in the file
 * named README, which can be found in the root of this distribution. By
 * using this software in any fashion, you are agreeing to be bound by the
 * terms of this license.
 *
 * You must not remove this notice, or any other, from this software.
 */

#ifndef _BASIC_FUNCS_H
#define _BASIC_FUNCS_H

#include "xrick/system/basic_types.h"
#include "xrick/system/system.h"

#ifdef __WIN32__
/* Windows is little endian only */
#  define __LITTLE_ENDIAN 1234
#  define __BIG_ENDIAN    4321
#  define __BYTE_ORDER    __LITTLE_ENDIAN
#  define USE_DEFAULT_ENDIANNESS_FUNCTIONS
#  include <stdlib.h> /* _byteswap_XXX */

#elif (defined(__FreeBSD__) && __FreeBSD_version >= 470000) || defined(__OpenBSD__) || defined(__NetBSD__)
/*  *BSD  */
#  include <sys/endian.h>
#  define __BIG_ENDIAN    BIG_ENDIAN
#  define __LITTLE_ENDIAN LITTLE_ENDIAN
#  define __BYTE_ORDER    BYTE_ORDER

#elif (defined(BSD) && (BSD >= 199103)) || defined(__MacOSX__)
/*  more BSD  */
#  include <machine/endian.h>
#  define __BIG_ENDIAN    BIG_ENDIAN
#  define __LITTLE_ENDIAN LITTLE_ENDIAN
#  define __BYTE_ORDER    BYTE_ORDER

#elif defined(__linux__) /*|| defined (__BEOS__)*/
/* Linux, BeOS */
#  include <endian.h>
#  define USE_DEFAULT_ENDIANNESS_FUNCTIONS

#else
/* shall we just '#include <endian.h>'? */
#  define USE_DEFAULT_ENDIANNESS_FUNCTIONS

#endif /* __WIN32__ */

/* provide default endianness functions */
#ifdef USE_DEFAULT_ENDIANNESS_FUNCTIONS

/* define default endianness */
#  ifndef __LITTLE_ENDIAN
#    define __LITTLE_ENDIAN 1234
#  endif

#  ifndef __BIG_ENDIAN
#    define __BIG_ENDIAN 4321
#  endif

#  ifndef __BYTE_ORDER
#    warning "Byte order not defined on your system, assuming little endian!"
#    define __BYTE_ORDER __LITTLE_ENDIAN
#  endif

#  define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)

inline uint32_t swap32(uint32_t x)
{
#  ifdef _MSC_VER
    return _byteswap_ulong(x);
#  elif (GCC_VERSION > 40300) || defined(__clang__)
    return __builtin_bswap32(x);
#  else
    return (x >> 24) |
          ((x >>  8) & 0x0000FF00) |
          ((x <<  8) & 0x00FF0000) |
           (x << 24);
#  endif /* _MSC_VER */
}

inline uint16_t swap16(uint16_t x)
{
#  ifdef _MSC_VER
    return _byteswap_ushort(x);
#  elif (GCC_VERSION > 40800) || defined(__clang__)
    return __builtin_bswap16(x);
#  else
    return (x << 8)|(x >> 8);
#  endif /* _MSC_VER */
}

#  if __BYTE_ORDER == __LITTLE_ENDIAN
inline uint16_t htobe16(uint16_t host) { return swap16(host);  }
inline uint16_t htole16(uint16_t host) { return host; }
inline uint16_t betoh16(uint16_t big_endian) { return swap16(big_endian); }
inline uint16_t letoh16(uint16_t little_endian) { return little_endian; }

inline uint32_t htobe32(uint32_t host) { return swap32(host); }
inline uint32_t htole32(uint32_t host) { return host; }
inline uint32_t betoh32(uint32_t big_endian) { return swap32(big_endian); }
inline uint32_t letoh32(uint32_t little_endian) { return little_endian; }

#  elif __BYTE_ORDER == __BIG_ENDIAN
inline uint16_t htobe16(uint16_t host) { return host;  }
inline uint16_t htole16(uint16_t host) { return swap16(host); }
inline uint16_t betoh16(uint16_t big_endian) { return big_endian; }
inline uint16_t letoh16(uint16_t little_endian) { return swap16(little_endian); }

inline uint32_t htobe32(uint32_t host) { return host; }
inline uint32_t htole32(uint32_t host) { return swap32(host); }
inline uint32_t betoh32(uint32_t big_endian) { return big_endian; }
inline uint32_t letoh32(uint32_t little_endian) { return swap32(little_endian); }

#  else
#  error "Unknown/unsupported byte order!"

#  endif

#endif /* USE_DEFAULT_ENDIANNESS_FUNCTIONS */

#endif /* ndef _BASIC_FUNCS_H */

/* eof */
