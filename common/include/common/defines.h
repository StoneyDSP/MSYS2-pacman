/**
 * @file defines.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-07-20
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifdef __cplusplus
extern "C" {
#endif

#cmakedefine _GNU_SOURCE
#cmakedefine PACKAGE "@CMAKE_PROJECT_NAME@"
#cmakedefine PACKAGE_VERSION "@PACKAGE_VERSION@"
#cmakedefine LOCALEDIR "@LOCALEDIR@"
#cmakedefine SCRIPTLET_SHELL "@SCRIPTLET_SHELL@"
#cmakedefine LDCONFIG "@LDCONFIG@"
#cmakedefine LIB_VERSION "@libalpm_version@"
#cmakedefine SYSHOOKDIR "@DATAROOTDIR@/libalpm/hooks/"
#cmakedefine CONFFILE "@SYSCONFDIR@/pacman.conf"
#cmakedefine DBPATH "@LOCALSTATEDIR@/lib/pacman/"
#cmakedefine GPGDIR "@SYSCONFDIR@/pacman.d/gnupg/"
#cmakedefine LOGFILE "@LOCALSTATEDIR@/log/pacman.log"
#cmakedefine CACHEDIR "@LOCALSTATEDIR@/cache/pacman/pkg/"
#cmakedefine HOOKDIR "@SYSCONFDIR@/pacman.d/hooks/"
/** The location of the root operating directory (ROOTDIR). */
#cmakedefine ROOTDIR "@ROOTDIR@"


/** Read-only architecture-independent data (DATAROOTDIR) */
#cmakedefine DATAROOTDIR "@DATAROOTDIR@"
/** Read-only architecture-independent data (DATAROOTDIR) */
#cmakedefine DATADIR "@DATADIR@"
/** Info documentation (DATAROOTDIR/info) */
#cmakedefine INFODIR "@INFODIR@"
/** Documentation root (DATAROOTDIR/doc/PROJECT_NAME) */
#cmakedefine DOCDIR "@DOCDIR@"
/** Run-time variable data (LOCALSTATEDIR/run) */
#cmakedefine RUNSTATEDIR "@RUNSTATEDIR@"


#cmakedefine01 HAVE_GETMNTENT
#cmakedefine01 HAVE_GETMNTINFO
#cmakedefine01 HAVE_STRNDUP
#cmakedefine01 HAVE_STRNLEN
#cmakedefine01 HAVE_STRSEP
#cmakedefine01 HAVE_SWPRINTF
#cmakedefine01 HAVE_TCFLUSH

#cmakedefine FSSTATSTYPE @FSSTATSTYPE@

#ifdef __cplusplus
};
#endif
