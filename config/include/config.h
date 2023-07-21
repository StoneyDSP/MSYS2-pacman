/**
 *	@file cnf.h
 *	@author your name (you@domain.com)
 *	@brief
 *	@version 0.1
 *	@date 2023-07-19
 *
 *	@copyright Copyright (c) 2023
 *
 */

#ifndef PM_CONFIG_H
#define PM_CONFIG_H

#include "defines.h"

#ifdef __cplusplus
# warning "A C++ compiler has been selected for C."
extern "C" {
#endif

#if !defined(ROOTDIR)
/**
 * @name ROOTDIR
 * @brief The location of the root operating directory.
 *
 */
#define ROOTDIR STRINGIFY(/)
#endif

#if !defined(PREFIX)
/**
 * @name PREFIX
 * @brief The location of the project build tree.
 *
 *
 */
#define PREFIX STRINGIFY(/usr)
#endif


#if !defined(SYSCONFDIR)
/**
 * @name SYSCONFDIR
 * @brief
 *
 */
#define SYSCONFDIR STRINGIFY(/etc)
#endif


#if !defined(LOCALSTATEDIR)
/**
 * @name LOCALSTATEDIR
 * @brief
 *
 */
#define LOCALSTATEDIR STRINGIFY(/var)
#endif


#if !defined(BINDIR)
/**
 * @name BINDIR
 * @brief
 *
 */
#define BINDIR STRINGIFY(/usr/bin)
#endif


#if !defined(LIBDIR)
/**
 * @name LIBDIR
 * @brief
 *
 */
#define LIBDIR STRINGIFY(/usr/lib)
#endif


#if !defined(SBINDIR)
/**
 * @name SBINDIR
 * @brief
 *
 */
#define SBINDIR STRINGIFY(/usr/sbin)
#endif


#if !defined(LIBEXECDIR)
/**
 * @name LIBEXECDIR
 * @brief
 *
 */
#define LIBEXECDIR STRINGIFY(/usr/libexec)
#endif


#if !defined(INCLUDEDIR)
/**
 * @name INCLUDEDIR
 * @brief
 *
 */
#define INCLUDEDIR STRINGIFY(/usr/include)
#endif


#if !defined(SHAREDSTATEDIR)
/**
 * @name SHAREDSTATEDIR
 * @brief
 *
 */
#define SHAREDSTATEDIR STRINGIFY(/usr/com)
#endif


/** Construct the string literal in pieces to prevent the source from getting
 * matched. Store it in a pointer rather than an array because some compilers
 * will just produce instructions to fill the array rather than assigning a
 * pointer to a static array.
 */
char const* prefix = PREFIX;
char const* sysconfdir = SYSCONFDIR;
char const* localstatedir = LOCALSTATEDIR;
// char const* sharedstatedir = SHAREDSTATEDIR;


/** HAVE_LIBCURL */
#if !defined(HAVE_LIBCURL)
# 	define HAVE_LIBCURL false
#elif (HAVE_LIBCURL + 0) != 0 || (1 - HAVE_LIBCURL - 1) == 2
#	undef HAVE_LIBCURL
#  	define HAVE_LIBCURL true
#else
#	undef HAVE_LIBCURL
#	define HAVE_LIBCURL false
#endif

/** HAVE_LIBGPGME */
#if !defined(HAVE_LIBGPGME)
# 	define HAVE_LIBGPGME false
#elif (HAVE_LIBGPGME + 0) != 0 || (1 - HAVE_LIBGPGME - 1) == 2
#	undef HAVE_LIBGPGME
# 	define HAVE_LIBGPGME true
#else
#	undef HAVE_LIBGPGME
# 	define HAVE_LIBGPGME false
#endif

/** HAVE_LIBSSL */
#if !defined(HAVE_LIBSSL)
#	define HAVE_LIBSSL 0
#elif (HAVE_LIBSSL + 0) != 0 || (1 - HAVE_LIBSSL - 1) == 2
#	define HAVE_LIBSSL 1
#else
#	define HAVE_LIBSSL 0
#endif

/** HAVE_LIBNETTLE */
#if !defined(HAVE_LIBNETTLE)
#	define HAVE_LIBNETTLE 0
#elif (HAVE_LIBNETTLE + 0) != 0 || (1 - HAVE_LIBNETTLE - 1) == 2
#	define HAVE_LIBNETTLE 1
#else
#	define HAVE_LIBNETTLE 0
#endif


/** HAVE_MNTENT_H */
#if !defined(HAVE_MNTENT_H)
#	undef HAVE_MNTENT_H
#elif (HAVE_MNTENT_H + 0) != 0 || (1 - HAVE_MNTENT_H - 1) == 2
#	undef HAVE_MNTENT_H
#	define HAVE_MNTENT_H true
#else
#	undef HAVE_MNTENT_H
#endif

/** HAVE_SYS_MNTTAB_H */
#if !defined(HAVE_SYS_MNTTAB_H)
#	undef HAVE_SYS_MNTTAB_H
#elif (HAVE_SYS_MNTTAB_H + 0) != 0 || (1 - HAVE_SYS_MNTTAB_H - 1) == 2
#	undef HAVE_SYS_MNTTAB_H
#	define HAVE_SYS_MNTTAB_H true
#else
#	undef HAVE_SYS_MNTTAB_H
#endif

/** HAVE_SYS_MOUNT_H */
#if !defined(HAVE_SYS_MOUNT_H)
#	undef HAVE_SYS_MOUNT_H
#elif (HAVE_SYS_MOUNT_H + 0) != 0 || (1 - HAVE_SYS_MOUNT_H - 1) == 2
#	undef HAVE_SYS_MOUNT_H
#	define HAVE_SYS_MOUNT_H true
#else
#	undef HAVE_SYS_MOUNT_H
#endif

/** HAVE_SYS_PARAM_H */
#if !defined(HAVE_SYS_PARAM_H)
#	undef HAVE_SYS_PARAM_H
#elif (HAVE_SYS_PARAM_H + 0) != 0 || (1 - HAVE_SYS_PARAM_H - 1) == 2
#	undef HAVE_SYS_PARAM_H
#	define HAVE_SYS_PARAM_H true
#else
#	undef HAVE_SYS_PARAM_H
#endif

/** HAVE_SYS_STATVFS_H */
#if !defined(HAVE_SYS_STATVFS_H)
#	undef HAVE_SYS_STATVFS_H
#elif (HAVE_SYS_STATVFS_H + 0) != 0 || (1 - HAVE_SYS_STATVFS_H - 1) == 2
#	undef HAVE_SYS_STATVFS_H
#	define HAVE_SYS_STATVFS_H true
#else
#	undef HAVE_SYS_STATVFS_H
#endif

/** HAVE_SYS_TYPES_H */
#if !defined(HAVE_SYS_TYPES_H)
#	undef HAVE_SYS_TYPES_H
#elif (HAVE_SYS_TYPES_H + 0) != 0 || (1 - HAVE_SYS_TYPES_H - 1) == 2
#	undef HAVE_SYS_TYPES_H
#	define HAVE_SYS_TYPES_H true
#else
#	undef HAVE_SYS_TYPES_H
#endif

/** HAVE_SYS_UCRED_H */
#if !defined(HAVE_SYS_UCRED_H)
#	undef HAVE_SYS_UCRED_H
#elif (HAVE_SYS_UCRED_H + 0) != 0 || (1 - HAVE_SYS_UCRED_H - 1) == 2
#	undef HAVE_SYS_UCRED_H
#	define HAVE_SYS_UCRED_H true
#else
#	undef HAVE_SYS_UCRED_H
#endif

/** HAVE_TERMIOS_H */
#if !defined(HAVE_TERMIOS_H)
#	undef HAVE_TERMIOS_H
#elif (HAVE_TERMIOS_H + 0) != 0 || (1 - HAVE_TERMIOS_H - 1) == 2
#	undef HAVE_TERMIOS_H
#	define HAVE_TERMIOS_H true
#else
#	undef HAVE_TERMIOS_H
#endif


/**
 *	@brief We are defining as 0 or 1
 *	getmntent,
 *	getmntinfo,
 *	strndup,
 *	strnlen,
 *	strsep,
 *	swprintf,
 *	tcflush,
 *
 */

/** HAVE_GETMNTENT */
#if !defined(HAVE_GETMNTENT)
#	define HAVE_GETMNTENT 0
#elif (HAVE_GETMNTENT + 0) != 0 || (1 - HAVE_GETMNTENT - 1) == 2
#	define HAVE_GETMNTENT 1
#else
#	define HAVE_GETMNTENT 0
#endif

/** HAVE_GETMNTINFO */
#if !defined(HAVE_GETMNTINFO)
#	define HAVE_GETMNTINFO 0
#elif (HAVE_GETMNTINFO + 0) != 0 || (1 - HAVE_GETMNTINFO - 1) == 2
#	define HAVE_GETMNTINFO 1
#else
#	define HAVE_GETMNTINFO 0
#endif

/** HAVE_STRNDUP */
#if !defined(HAVE_STRNDUP)
#	define HAVE_STRNDUP 0
#elif (HAVE_STRNDUP + 0) != 0 || (1 - HAVE_STRNDUP - 1) == 2
#	define HAVE_STRNDUP 1
#else
#	define HAVE_STRNDUP 0
#endif

/** HAVE_STRLEN */
#if !defined(HAVE_STRNLEN)
#	define HAVE_STRNLEN 0
#elif (HAVE_STRNLEN + 0) != 0 || (1 - HAVE_STRNLEN - 1) == 2
#	define HAVE_STRNLEN 1
#else
#	define HAVE_STRNLEN 0
#endif

/** HAVE_STRSEP */
#if !defined(HAVE_STRSEP)
#	define HAVE_STRSEP 0
#elif (HAVE_STRSEP + 0) != 0 || (1 - HAVE_STRSEP - 1) == 2
#	define HAVE_STRSEP 1
#else
#	define HAVE_STRSEP 0
#endif

/** HAVE_SWPRINTF */
#if !defined(HAVE_SWPRINTF)
#	define HAVE_SWPRINTF 0
#elif (HAVE_SWPRINTF + 0) != 0 || (1 - HAVE_SWPRINTF - 1) == 2
#	define HAVE_SWPRINTF 1
#else
#	define HAVE_SWPRINTF 0
#endif

/** HAVE_TCFLUSH */
#if !defined(HAVE_TCFLUSH)
#	define HAVE_TCFLUSH 0
#elif (HAVE_TCFLUSH + 0) != 0 || (1 - HAVE_TCFLUSH - 1) == 2
#	define HAVE_TCFLUSH 1
#else
#	define HAVE_TCFLUSH 0
#endif

#ifdef __cplusplus
};
#endif

#endif /** PM_CONFIG_H */
