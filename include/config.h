/**
 * @file config.h
 * @brief This file is passed through the C preprocessor
 * before pacman is configured for building. A configured
 * copy will appear in the project build tree.
 * Do not alter this file directly, instead see
 * 'CMakeLists.txt' for all variable definitions
 *
 */

#cmakedefine _GNU_SOURCE @_GNU_SOURCE@
#cmakedefine PACKAGE "@PACKAGE@"
#cmakedefine PACKAGE_VERSION "@PACKAGE_VERSION@"
#cmakedefine LOCALEDIR "@LOCALEDIR@"
/** The full path of the shell used to run install scriptlets. */
#cmakedefine SCRIPTLET_SHELL "@SCRIPTLET_SHELL@"
#cmakedefine LDCONFIG "@LDCONFIG@"
#cmakedefine LIB_VERSION "@LIB_VERSION@"
#cmakedefine SYSHOOKDIR "@SYSHOOKDIR@"
#cmakedefine CONFFILE "@CONFFILE@"
#cmakedefine DBPATH "@DBPATH@"
#cmakedefine GPGDIR "@GPGDIR@"
#cmakedefine LOGFILE "@LOGFILE@"
#cmakedefine CACHEDIR "@CACHEDIR@"
#cmakedefine HOOKDIR "@HOOKDIR@"
#cmakedefine ROOTDIR "@ROOTDIR@"

/** Read-only architecture-independent data (DATAROOTDIR) */
#cmakedefine DATADIR "@DATADIR@"
/** Info documentation (DATAROOTDIR/info) */
#cmakedefine INFODIR "@INFODIR@"
/** Documentation root (DATAROOTDIR/doc/PROJECT_NAME) */
#cmakedefine DOCDIR "@DOCDIR@"
/** Run-time variable data (LOCALSTATEDIR/run) */
#cmakedefine RUNSTATEDIR "@RUNSTATEDIR@"
ç
#cmakedefine HAVE_LIBCURL @HAVE_LIBCURL@

#cmakedefine HAVE_MNTENT_H @HAVE_MNTENT_H@
#cmakedefine HAVE_SYS_MNTTAB_H @HAVE_SYS_MNTTAB_H@
#cmakedefine HAVE_SYS_MOUNT_H @HAVE_SYS_MOUNT_H@
#cmakedefine HAVE_SYS_PARAM_H @HAVE_SYS_PARAM_H@
#cmakedefine HAVE_SYS_STATVFS_H @HAVE_SYS_STATVFS_H@
#cmakedefine HAVE_SYS_TYPES_H @HAVE_SYS_TYPES_H@
#cmakedefine HAVE_SYS_UCRED_H @HAVE_SYS_UCRED_H@
#cmakedefine HAVE_TERMIOS_H @HAVE_TERMIOS_H@

#cmakedefine HAVE_GETMNTENT @HAVE_GETMNTENT@
#cmakedefine HAVE_GETMNTINFO @HAVE_GETMNTINFO@
#cmakedefine HAVE_STRNDUP @HAVE_STRNDUP@
#cmakedefine HAVE_STRNLEN @HAVE_STRNLEN@
#cmakedefine HAVE_STRSEP @HAVE_STRSEP@
#cmakedefine HAVE_SWPRINTF @HAVE_SWPRINTF@
#cmakedefine HAVE_TCFLUSH @HAVE_TCFLUSH@

#cmakedefine FSSTATSTYPE @FSSTATSTYPE@
