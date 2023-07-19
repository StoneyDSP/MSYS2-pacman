/**
 * @file cnf.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-19
 *
 * @copyright Copyright (c) 2023
 *
**/

// /* We are defining __USE_MINGW_ANSI_STDIO as 0 or 1 */
// #if !defined(__USE_MINGW_ANSI_STDIO)
// #define __USE_MINGW_ANSI_STDIO 0      /* was not defined so it should be 0 */
// #elif (__USE_MINGW_ANSI_STDIO + 0) != 0 || (1 - __USE_MINGW_ANSI_STDIO - 1) == 2
// #define __USE_MINGW_ANSI_STDIO 1      /* was defined as nonzero or empty so it should be 1 */
// #else
// #define __USE_MINGW_ANSI_STDIO 0      /* was defined as (int)zero and non-empty so it should be 0 */
// #endif

/**
 * @brief Defined to 1 if you have the "argz_add()" function.
 */
#define HAVE_ARGZ_ADD

/**
 * @brief Defined to 1 if you have the "argz_append()" function.
 */
#define HAVE_ARGZ_APPEND

/**
 * @brief Defined to 1 if you have the "argz_count()" function.
 */
#define HAVE_ARGZ_COUNT

/**
 * @brief Defined to 1 if you have the "argz_create_sep()" function.
 */
#define HAVE_ARGZ_CREATE_SEP

/**
 * @brief Defined to 1 if you have the "<argz.h>" header file.
 */
#define HAVE_ARGZ_H

/**
 * @brief Defined to 1 if you have the "argz_insert()" function.
 */
#define HAVE_ARGZ_INSERT

/**
 * @brief Defined to 1 if you have the "argz_next()" function.
 */
#define HAVE_ARGZ_NEXT

/**
 * @brief Defined to 1 if you have the "argz_stringify()" function.
 */
#define HAVE_ARGZ_STRINGIFY

/**
 * @brief Defined to 1 if you have the "closedir()" function.
 */
#define HAVE_CLOSEDIR

/**
 * @brief Defined to 1 if you have the declaration of "cygwin_conv_path()", and to 0 if you don't.
 */
#define HAVE_DECL_CYGWIN_CONV_PATH

/**
 * @brief Defined to 1 if you have the "<dirent.h>" header file.
 */
#define HAVE_DIRENT_H

/**
 * @brief Defined if you have the GNU dld library.
 */
#define HAVE_DLD

/**
 * @brief Defined to 1 if you have the "<dld.h>" header file.
 */
#define HAVE_DLD_H

/**
 * @brief Defined to 1 if you have the "dlerror()" function.
 * @headerfile <dld.h>
 */
#define HAVE_DLERROR

/**
 * @brief Defined to 1 if you have the "<dlfcn.h>" header file.
 */
#define HAVE_DLFCN_H

/**
 * @brief Defined to 1 if you have the "<dl.h>" header file.
 */
#define HAVE_DL_H

/**
 * @brief Defined if you have the "_dyld_func_lookup()" function.
 */
#define HAVE_DYLD

/**
 * @brief Defined to 1 if the system has the type "error_t"
 */
#define HAVE_ERROR_T

/**
 * @brief  Defined to 1 if you have the "<inttypes.h>"" header file.
 */
#define HAVE_INTTYPES_H

/**
 * @brief Defined if you have the "libdl" library or equivalent.
 */
#define HAVE_LIBDL

/**
 * @brief Defined if "libdlloader" will be built on this platform
 */
#define HAVE_LIBDLLOADER

/* Define to 1 if you have the <mach-o/dyld.h> header file. */
#define HAVE_MACH_O_DYLD_H

/* Define to 1 if you have the `opendir' function. */
#define HAVE_OPENDIR

/* Define if libtool can extract symbol lists from object files. */
#define HAVE_PRELOADED_SYMBOLS

/* Define to 1 if you have the `readdir' function. */
#define HAVE_READDIR

/* Define if you have the shl_load function. */
#define HAVE_SHL_LOAD

/**
 * @brief Defined to 1 if you have the "<stdint.h>" header file.
 * @headerfile "<stdint.h>"
 */
#define HAVE_STDINT_H

/**
 * @brief Defined to 1 if you have the "<stdio.h>" header file.
 * @headerfile "<stdio.h>"
 */
#define HAVE_STDIO_H

/**
 * @brief Defined to 1 if you have the "<stdlib.h>" header file.
 * @headerfile "<stdlib.h>"
 */
#define HAVE_STDLIB_H

/**
 * @brief Defined to 1 if you have the "<strings.h>" header file.
 * @headerfile "<strings.h>"
 */
#define HAVE_STRINGS_H

/**
 * @brief Defined to 1 if you have the "<string.h>" header file.
 * @headerfile "<string.h>"
 */
#define HAVE_STRING_H

/**
 * @brief Defined to 1 if you have the "strlcat()" function.
 */
#define HAVE_STRLCAT

/**
 * @brief Defined to 1 if you have the "strlcpy()" function.
 */
#define HAVE_STRLCPY

/**
 * @brief Defined to 1 if you have the "<sys/dl.h>" header file.
 * @headerfile "<sys/dl.h>"
 */
#define HAVE_SYS_DL_H

/**
 * @brief Defined to 1 if you have the "<sys/stat.h>" header file.
 * @headerfile "<sys/stat.h>"
 */
#define HAVE_SYS_STAT_H

/**
 * @brief Defined to 1 if you have the "<sys/types.h>" header file.
 * @headerfile "<sys/types.h>"
 */
#define HAVE_SYS_TYPES_H

/**
 * @name HAVE_UNISTD_H
 * @brief Defined to 1 if you have the "<unistd.h>" header file.
 * @headerfile "<unistd.h>"
 */
#define HAVE_UNISTD_H

/**
 * @name HAVE_WORKING_ARGZ
 * @brief This value is set to 1 to indicate that the system "argz" facility works
 * @headerfile "<argz.h>"
 */
#define HAVE_WORKING_ARGZ

/**
 * @name `LTDL_DLOPEN_DEPLIBS'
 * @brief Defined if the OS needs help to load dependent libraries for "dlopen()"".
 */
#define LTDL_DLOPEN_DEPLIBS

/**
 * @name `LT_DLSEARCH_PATH'
 * @brief Define to the system default library search path.
 */
#define LT_DLSEARCH_PATH

/**
 * @name `LT_LIBEXT'
 * @brief The archive extension.
 */
#define LT_LIBEXT

/**
 * @name `LT_LIBPREFIX'
 * @brief The archive prefix.
 */
#define LT_LIBPREFIX

/**
 * @name `LT_MODULE_EXT'
 * @brief Defined to the extension used for runtime loadable modules, say, ".so".
 */
#define LT_MODULE_EXT

/* Define to the name of the environment variable that determines the run-time module search path. */
#define LT_MODULE_PATH_VAR

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR

/* Define to the shared library suffix, say, ".dylib". */
#define LT_SHARED_EXT

/* Define to the shared archive member specification, say "(shr.o)". */
#define LT_SHARED_LIB_MEMBER

/**
 * @brief Define if "dlsym()"" requires a leading underscore in symbol names.
 */
#define NEED_USCORE

/**
 * @brief Name of package.
 */
#define PACKAGE

/**
 * @brief The address where bug reports for this package should be sent.
 */
#define PACKAGE_BUGREPORT

/**
 * @brief The full name of this package.
 */
#define PACKAGE_NAME

/**
 * @name `PACKAGE_STRING'
 * @brief The full name and version of this package.
 */
#define PACKAGE_STRING

/**
 * @name `PACKAGE_TARNAME'
 * @brief The one-symbol short name of this package.
 */
#define PACKAGE_TARNAME

/**
 * @name `PACKAGE_URL'
 * @brief The home page for this package.
 */
#define PACKAGE_URL

/**
 * @name `PACKAGE_VERSION'
 * @brief The version of this package.
 */
#define PACKAGE_VERSION

/**
 * @name `STDC_HEADERS'
 * @brief Defined to 1 if all of the C90 standard headers exist (not just the ones
 * required in a freestanding environment).
 *
 * This macro is provided for backward compatibility; new code need not use it.
 */
#define STDC_HEADERS

/**
 * @name `VERSION'
 * @brief Version number of package
 */
#define VERSION

/**
 * @brief Defined so that glibc/gnulib "argp.h" does not typedef error_t.
 * @headerfile "config.h"
 */
#define __error_t_defined

/**
 * @brief Defined to a type to use for 'error_t' if it is not otherwise available.
 * @headerfile "config.h"
 */
#ifndef error_t
#  define error_t unsigned int
#endif // error_t
