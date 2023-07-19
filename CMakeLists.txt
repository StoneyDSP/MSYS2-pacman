cmake_minimum_required(VERSION 3.17...3.26 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/scripts/cmake/Modules")

if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Specifies the build type on single-configuration generators" FORCE)
endif()

project(pacman C)
enable_language(CXX)

include(GNUInstallDirs)
#set(PREFIX "usr" CACHE PATH "")
#set(EXEC_PREFIX "${PREFIX}/bin" CACHE PATH "")

set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")

# pacman project defaults
# set(prefix "/usr")
# set(sysconfdir "/etc")
# set(localstatedir "/var")

set(libalpm_version "13.0.2")

# meson-options.txt
set(pkg_ext ".pkg.tar.gz" CACHE PATH "Set the file extension used by packages.")
set(src_ext ".src.tar.gz" CACHE PATH "Set the file extension used by source packages.")
set(makepkg_template_dir "/usr/share/makepkg-template" CACHE PATH "Template dir used by makepkg-template.")
set(debug_suffix "debug") # you know what to do with this...

# set(PREFIX "/usr")
set(PREFIX "${CMAKE_BINARY_DIR}" CACHE PATH "")
set(ROOTDIR "/" CACHE PATH "Set the location of the root operating directory.")

# required join_paths() operations for the section after...
cmake_path(APPEND LIBDIR "${PREFIX}" "/lib")
cmake_path(APPEND SBINDIR "${PREFIX}" "/sbin")
cmake_path(APPEND LIBEXECDIR "${PREFIX}" "/libexec")
cmake_path(APPEND SHAREDSTATEDIR "${PREFIX}" "/com")
cmake_path(APPEND INCLUDEDIR "${PREFIX}" "/include")

cmake_path(APPEND DATAROOTDIR "${PREFIX}" "/share")
cmake_path(APPEND SYSCONFDIR "${PREFIX}" "/etc")
cmake_path(APPEND LOCALSTATEDIR "${PREFIX}" "/var")
cmake_path(APPEND LOCALEDIR "${PREFIX}" "/${DATAROOTDIR}/locale")
cmake_path(APPEND BINDIR "${PREFIX}" "/bin")
cmake_path(APPEND MANDIR "${PREFIX}" "/${DATAROOTDIR}/man")
cmake_path(APPEND LIBMAKEPKGDIR "${PREFIX}" "/makepkg")
cmake_path(APPEND PKGDATADIR "${PREFIX}" "${PROJECT_NAME}")

cmake_path(APPEND SYSHOOKDIR "${DATAROOTDIR}" "/libalpm/hooks/")
cmake_path(APPEND CONFFILE "${SYSCONFDIR}" "/pacman.conf")
cmake_path(APPEND DBPATH "${LOCALSTATEDIR}" "lib/pacman/")
cmake_path(APPEND GPGDIR "${SYSCONFDIR}" "/pacman.d/gnupg/")
cmake_path(APPEND LOGFILE "${LOCALSTATEDIR}" "/log/pacman.log")
cmake_path(APPEND CACHEDIR "${LOCALSTATEDIR}" "/cache/pacman/pkg/")
cmake_path(APPEND HOOKDIR "${SYSCONFDIR}" "/pacman.d/hooks/")

# commandline options
set(LIBDIR "${LIBDIR}" CACHE PATH "Object code libraries (lib)")
set(SBINDIR "${SBINDIR}" CACHE PATH "System admin executables (sbin)")
set(LIBEXECDIR "${LIBEXECDIR}" CACHE PATH "Program executables (libexec)")
set(SHAREDSTATEDIR "${SHAREDSTATEDIR}" CACHE PATH "Modifiable architecture-independent data (com)")
set(INCLUDEDIR "${INCLUDEDIR}" CACHE PATH "C header files (include)")

set(DATAROOTDIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data root (share)" FORCE)
set(SYSCONFDIR "${SYSCONFDIR}" CACHE PATH "Read-only single-machine data (etc)" FORCE)
set(LOCALSTATEDIR "${LOCALSTATEDIR}" CACHE PATH "Modifiable single-machine data (var)" FORCE)
set(LOCALEDIR "${LOCALEDIR}" CACHE PATH "Locale-dependent data (DATAROOTDIR/locale)" FORCE)
set(ROOTDIR "${ROOTDIR}" CACHE PATH "" FORCE)
set(BINDIR "${BINDIR}" CACHE PATH "User executables (bin)" FORCE)
set(MANDIR "${MANDIR}" CACHE PATH "Man documentation (DATAROOTDIR/man)" FORCE)

set(DATADIR "${DATAROOTDIR}" CACHE PATH "Read-only architecture-independent data (DATAROOTDIR)")
set(INFODIR "${DATAROOTDIR}/info" CACHE PATH "Info documentation (DATAROOTDIR/info)")
set(DOCDIR "${DATAROOTDIR}/doc/${PROJECT_NAME}" CACHE PATH "Documentation root (DATAROOTDIR/doc/PROJECT_NAME)")
set(RUNSTATEDIR "${LOCALSTATEDIR}/run" CACHE PATH "Run-time variable data (LOCALSTATEDIR/run)")

set(SYSHOOKDIR "${SYSHOOKDIR}" CACHE PATH "")
set(CONFFILE "${CONFFILE}" CACHE PATH "")
set(DBPATH "${DBPATH}" CACHE PATH "")
set(GPGDIR "${GPGDIR}" CACHE PATH "")
set(LOGFILE "${LOGFILE}" CACHE FILEPATH "")
set(CACHEDIR "${CACHEDIR}" CACHE FILEPATH "")
set(HOOKDIR "${HOOKDIR}" CACHE FILEPATH "")
set(LIBMAKEPKGDIR "${LIBMAKEPKGDIR}" CACHE PATH "" FORCE)
set(PKGDATADIR "${PKGDATADIR}" CACHE PATH "" FORCE)

set(SCRIPTLET_SHELL "/bin/sh" CACHE FILEPATH "The full path of the shell used to run install scriptlets.")
set(LDCONFIG "/sbin/ldconfig" CACHE FILEPATH "Set the full path to ldconfig.")
set(LIB_VERSION "${libalpm_version}" CACHE STRING "")
set(BUILDSCRIPT "PKGBUILD" CACHE STRING "Set the build script name used by makepkg." FORCE)

set(PROJECT_VERSION_MAJOR 6 CACHE STRING "First version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set(PROJECT_VERSION_MINOR 0 CACHE STRING "Second version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set(PROJECT_VERSION_PATCH 2 CACHE STRING "Third version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
include(GetSourceInfo)
get_source_info()
set(PROJECT_VERSION_TWEAK "${git_revision}")
#set(PROJECT_VERSION_TWEAK "-cmake-build" CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)

set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}" CACHE STRING "Value given to the ``VERSION`` option of the most recent call to the ``project()`` command, if any." FORCE)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)


set(_GNU_SOURCE TRUE CACHE BOOL "")
set(PACKAGE "${PROJECT_NAME}" CACHE STRING "")
set(PACKAGE_VERSION "${PROJECT_VERSION}" CACHE STRING "")


include(CheckCXXCompilerFlag)




include(CheckIncludeFile)
set(PACMAN_REQUIRED_SYSTEM_HEADERS)
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "mntent.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/mnttab.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/mount.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/param.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/statvfs.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/types.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "sys/ucred.h")
list(APPEND PACMAN_REQUIRED_SYSTEM_HEADERS "termios.h")
foreach (_header IN LISTS PACMAN_REQUIRED_SYSTEM_HEADERS)
	set(_header_string ${_header})
	# underscorify(${_header})
	string(REPLACE [[/]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[\]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[.]] [[_]] _header_string "${_header_string}")
	string(REPLACE [[-]] [[_]] _header_string "${_header_string}")
	CHECK_INCLUDE_FILE("${_header}" has_${_header_string})
	if(has_${_header_string})
		string(TOUPPER ${_header_string} _header_string)
		##-- These shall print C-syntaxed booleans
		set(HAVE_${_header_string} true CACHE BOOL "Found required header file: ${_header}" FORCE)
	endif()
	unset(has_${_header_string})
endforeach()
unset(_header)
unset(_header_string)

include(CheckFunctionExists)
set(PACMAN_REQUIRED_SYSTEM_FUNCTIONS)
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "getmntent")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "getmntinfo")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strndup")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strnlen")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "strsep")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "swprintf")
list(APPEND PACMAN_REQUIRED_SYSTEM_FUNCTIONS "tcflush")
foreach (_symbol IN LISTS PACMAN_REQUIRED_SYSTEM_FUNCTIONS)
	set(CMAKE_REQUIRED_DEFINITIONS "-D_GNU_SOURCE")
	check_function_exists("${_symbol}" has_${_symbol})
	if(has_${_symbol})
		##-- These shall print integer 0's or 1's
		string(TOUPPER ${_symbol} _symbol)
		set(HAVE_${_symbol} 1 CACHE BOOL "" FORCE)
	endif()
	unset(has_${_symbol})
endforeach()
unset(_symbol)


include(CheckStructHasMember)
## CHECK_STRUCT_HAS_MEMBER ("_STRUCT" _MEMBER "_HEADER" _RESULT)
## CHECK_STRUCT_HAS_MEMBER("struct timeval" tv_sec sys/select.h HAVE_TIMEVAL_TV_SEC LANGUAGE C)
CHECK_STRUCT_HAS_MEMBER("struct stat" st_blksize "sys/stat.h" has_struct_stat_st_blksize LANGUAGE C)
if(has_struct_stat_st_blksize)
	set(HAVE_STRUCT_STAT_ST_BLKSIZE true CACHE BOOL "" FORCE)
endif()

CHECK_STRUCT_HAS_MEMBER("struct statvfs" f_flag "sys/statvfs.h" has_struct_statvfs_f_flag LANGUAGE C)
if(has_struct_statvfs_f_flag)
	set(HAVE_STRUCT_STATVFS_F_FLAG true CACHE BOOL "" FORCE)
endif()

CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/param.h" has_struct_statfs_f_flags LANGUAGE C)
if(has_struct_statfs_f_flags)
	set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE BOOL "" FORCE)
else()
	CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/mount.h" has_struct_statfs_f_flags_sys_mount LANGUAGE C)
	if(has_struct_statfs_f_flags_sys_mount)
		set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE BOOL "" FORCE)
	endif()
endif()

include(CheckTypeSize)
CHECK_TYPE_SIZE("unsigned int" "mode_t" LANGUAGE C)
CHECK_TYPE_SIZE("unsigned int" "uid_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "off_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "pid_t" LANGUAGE C)
CHECK_TYPE_SIZE("unsigned int" "size_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int" "ssize_t" LANGUAGE C)
CHECK_TYPE_SIZE("signed int long" "int64_t" BUILTIN_TYPES_ONLY LANGUAGE C)

if (HAVE_STRUCT_STATVFS_F_FLAG)
  	set(FSSTATSTYPE "struct statvfs")
elseif (HAVE_STRUCT_STATFS_F_FLAGS)
  	set(FSSTATSTYPE "struct statfs")
endif ()

if(CMAKE_BUILD_STYPE STREQUAL "Debug")
	include(CheckCCompilerFlag)
	check_c_compiler_flag(-Wcast-align HAS_CAST_ALIGN)
	check_c_compiler_flag(-Wclobbered HAS_CLOBBERED)
	check_c_compiler_flag(-Wempty-body HAS_EMPTY_BODY)
	check_c_compiler_flag(-Wfloat-equal HAS_FLOAT_EQUAL)
	check_c_compiler_flag(-Wformat-nonliteral HAS_FORMAT_NONLITERAL)
	check_c_compiler_flag(-Wformat-security HAS_FORMAT_SECURITY)
	check_c_compiler_flag(-Wignored-qualifiers HAS_IGNORED_QUALIFIERS)
	check_c_compiler_flag(-Wimplicit-fallthrough HAS_IMPLICIT_FALLTHROUGHS)
	check_c_compiler_flag(-Winit-self HAS_INIT_SELF)
	check_c_compiler_flag(-Wlogical-op HAS_LOGICAL_OP)
	check_c_compiler_flag(-Wmissing-declarations HAS_MISSING_DECLARATIONS)
	check_c_compiler_flag(-Wmissing-field-initializers HAS_MISSING_FIELD_INITIALIZERS)
	check_c_compiler_flag(-Wmissing-parameter-type HAS_MISSING_PARAMETER_TYPE)
	check_c_compiler_flag(-Wmissing-prototypes HAS_MISSING_PROTOTYPES)
	check_c_compiler_flag(-Wold-style-declaration HAS_OLD_STYLE_DECLARATION)
	check_c_compiler_flag(-Woverride-init HAS_OVERRIDE_INIT)
	check_c_compiler_flag(-Wpointer-arith HAS_POINTER_ARITH)
	check_c_compiler_flag(-Wredundant-decls HAS_REDUNDANT_DECLS)
	check_c_compiler_flag(-Wshadow HAS_SHADOW)
	check_c_compiler_flag(-Wsign-compare HAS_SIGN_COMPARE)
	check_c_compiler_flag(-Wstrict-aliasing HAS_STRICT_ALIASING)
	check_c_compiler_flag(-Wstrict-overflow=5 HAS_STRICT_OVERFLOW_EQ_5)
	check_c_compiler_flag(-Wstrict-prototypes HAS_STRICT_PROTOTYPES)
	check_c_compiler_flag(-Wtype-limits HAS_TYPE_LIMITS)
	check_c_compiler_flag(-Wuninitialized HAS_UNINITIALIZED)
	check_c_compiler_flag(-Wunused-but-set-parameter HAS_UNUSED_BUT_DET_PARAMETER)
	check_c_compiler_flag(-Wunused-parameter HAS_UNUSED_PARAMETER)
	check_c_compiler_flag(-Wwrite-strings HAS_WRITE_STRINGS)
	set(PACMAN_DEBUG 1)
endif()


find_program(PYTHON python3)
include(FindCURL)
include(FindLibArchive)
include(FindIntl)
include(FindOpenSSL) # crypto provider
set(ALPM_DEPS)
list(APPEND ALPM_DEPS "OpenSSL::Crypto")
list(APPEND ALPM_DEPS "LibArchive::LibArchive")
list(APPEND ALPM_DEPS "CURL::libcurl")
list(APPEND ALPM_DEPS "Intl::Intl")
set(ALPM_DEPS "${ALPM_DEPS}" CACHE STRING "")

# set(HAVE_LIBCURL false)
if(CURL_FOUND)
	set(HAVE_LIBCURL true)
endif()


configure_file("include/config.h" "include/config.h" @ONLY)

add_library (configuration                                      INTERFACE)
add_library (${PROJECT_NAME}::configuration                     ALIAS configuration)

target_include_directories (configuration

    INTERFACE

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_sources (configuration

    PUBLIC

        FILE_SET configuration_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include>
            $<INSTALL_INTERFACE:include>
        FILES
            # include/application/configuration.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/config.h>
            $<INSTALL_INTERFACE:include/config.h>
)

set_target_properties (configuration

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin
)


add_library (common 									STATIC)
add_library (${PROJECT_NAME}::common                    ALIAS common)

if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

    configure_file ("include/common/ini.h"       				"include/common/ini.h")
	configure_file ("src/common/ini.c"          				"src/common/ini.c")

    configure_file ("include/common/util-common.h"        		"include/common/util-common.h")
    configure_file ("src/common/util-common.c"             		"src/common/util-common.c")

endif ()

target_include_directories (common

    PUBLIC

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
        $<INSTALL_INTERFACE:include/common>

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm>
        $<INSTALL_INTERFACE:include/alpm>
)

target_sources (common

    PUBLIC

        FILE_SET static_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
            $<INSTALL_INTERFACE:include/common>
        FILES
            # include/common/ini.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/ini.h>
            $<INSTALL_INTERFACE:include/common/ini.h>
			# include/common/util-common.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/util-common.h>
            $<INSTALL_INTERFACE:include/common/util-common.h>
)

target_sources (common

    PRIVATE

		# src/common/ini.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/common/ini.c>
		$<INSTALL_INTERFACE:src/common/ini.c>
		# src/common/util-common.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/common/util-common.c>
		$<INSTALL_INTERFACE:src/common/util-common.c>
)

set_target_properties (common

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin

		C_STANDARD 99
		C_STANDARD_REQUIRED TRUE
		VISIBILITY_INLINES_HIDDEN TRUE
		HAS_CXX FALSE
		#COMPILE_WARNING_AS_ERROR FALSE
)

target_compile_features(common PUBLIC c_std_99)

target_link_libraries(common PUBLIC configuration)

# libalpm_a = static_library(
#   'alpm_objlib',
#   libalpm_sources,
#   # https://github.com/mesonbuild/meson/issues/3937
#   objects : libcommon.extract_all_objects(),
#   include_directories : includes,
#   gnu_symbol_visibility : 'hidden',
#   dependencies : alpm_deps)



add_library (alpm_objlib 									STATIC)
add_library (${PROJECT_NAME}::alpm_objlib                    ALIAS alpm_objlib)

if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

	configure_file("include/alpm/add.h" 	"include/alpm/add.h")
	configure_file("include/alpm/alpm.h" 	"include/alpm/alpm.h")
	configure_file("include/alpm/alpm_list.h" 	"include/alpm/alpm_list.h")
	configure_file("include/alpm/backup.h" 	"include/alpm/backup.h")
	configure_file("include/alpm/base64.h" 	"include/alpm/base64.h")
	configure_file("include/alpm/conflict.h" 	"include/alpm/conflict.h")
	configure_file("include/alpm/db.h" 	"include/alpm/db.h")
	configure_file("include/alpm/deps.h" 	"include/alpm/deps.h")
	configure_file("include/alpm/diskspace.h" 	"include/alpm/diskspace.h")
	configure_file("include/alpm/dload.h" 	"include/alpm/dload.h")
	configure_file("include/alpm/filelist.h" 	"include/alpm/filelist.h")
	configure_file("include/alpm/graph.h" 	"include/alpm/graph.h")
	configure_file("include/alpm/group.h" 	"include/alpm/group.h")
	configure_file("include/alpm/handle.h" 	"include/alpm/handle.h")
	configure_file("include/alpm/hook.h" 	"include/alpm/hook.h")
	configure_file("include/alpm/libarchive-compat.h" 	"include/alpm/libarchive-compat.h")
	configure_file("include/alpm/log.h" 	"include/alpm/log.h")
	configure_file("include/alpm/package.h" 	"include/alpm/package.h")
	configure_file("include/alpm/pkghash.h" 	"include/alpm/pkghash.h")
	configure_file("include/alpm/remove.h" 	"include/alpm/remove.h")
	configure_file("include/alpm/signing.h" 	"include/alpm/signing.h")
	configure_file("include/alpm/sync.h" 	"include/alpm/sync.h")
	configure_file("include/alpm/trans.h" 	"include/alpm/trans.h")
	configure_file("include/alpm/util.h" 	"include/alpm/util.h")

	configure_file("src/alpm/add.c" 		"src/alpm/add.c")
	configure_file("src/alpm/alpm.c" 		"src/alpm/alpm.c")
	configure_file("src/alpm/alpm_list.c" 		"src/alpm/alpm_list.c")
	configure_file("src/alpm/backup.c" 		"src/alpm/backup.c")
	configure_file("src/alpm/base64.c" 		"src/alpm/base64.c")
	configure_file("src/alpm/be_local.c" 		"src/alpm/be_local.c")
	configure_file("src/alpm/be_package.c" 		"src/alpm/be_package.c")
	configure_file("src/alpm/be_sync.c" 		"src/alpm/be_sync.c")
	configure_file("src/alpm/conflict.c" 		"src/alpm/conflict.c")
	configure_file("src/alpm/db.c" 		"src/alpm/db.c")
	configure_file("src/alpm/deps.c" 		"src/alpm/deps.c")
	configure_file("src/alpm/diskspace.c" 		"src/alpm/diskspace.c")
	configure_file("src/alpm/dload.c" 		"src/alpm/dload.c")
	configure_file("src/alpm/error.c" 		"src/alpm/error.c")
	configure_file("src/alpm/filelist.c" 		"src/alpm/filelist.c")
	configure_file("src/alpm/graph.c" 		"src/alpm/graph.c")
	configure_file("src/alpm/group.c" 		"src/alpm/group.c")
	configure_file("src/alpm/handle.c" 		"src/alpm/handle.c")
	configure_file("src/alpm/hook.c" 		"src/alpm/hook.c")
	configure_file("src/alpm/log.c" 		"src/alpm/log.c")
	configure_file("src/alpm/package.c" 		"src/alpm/package.c")
	configure_file("src/alpm/pkghash.c" 		"src/alpm/pkghash.c")
	configure_file("src/alpm/rawstr.c" 		"src/alpm/rawstr.c")
	configure_file("src/alpm/remove.c" 		"src/alpm/remove.c")
	configure_file("src/alpm/signing.c" 		"src/alpm/signing.c")
	configure_file("src/alpm/sync.c" 		"src/alpm/sync.c")
	configure_file("src/alpm/trans.c" 		"src/alpm/trans.c")
	configure_file("src/alpm/util.c" 		"src/alpm/util.c")
	configure_file("src/alpm/version.c" 		"src/alpm/version.c")

endif ()

target_include_directories (alpm_objlib

    PUBLIC

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
		$<INSTALL_INTERFACE:include/common>

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm>
		$<INSTALL_INTERFACE:include/alpm>
)

target_sources (alpm_objlib

    PUBLIC

        FILE_SET alpm_objlib_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm>
            $<INSTALL_INTERFACE:include/alpm>
        FILES
            # include/alpm/add.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/add.h>
            $<INSTALL_INTERFACE:include/alpm/add.h>
			# include/alpm/alpm.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/alpm.h>
            $<INSTALL_INTERFACE:include/alpm/alpm.h>
			# include/alpm/alpm_list.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/alpm_list.h>
			$<INSTALL_INTERFACE:include/alpm/alpm_list.h>
			# include/alpm/backup.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/backup.h>
			$<INSTALL_INTERFACE:include/alpm/backup.h>
			# include/alpm/base64.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/base64.h>
			$<INSTALL_INTERFACE:include/alpm/base64.h>
			# include/alpm/conflict.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/conflict.h>
			$<INSTALL_INTERFACE:include/alpm/conflict.h>
			# include/alpm/db.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/db.h>
			$<INSTALL_INTERFACE:include/alpm/db.h>
			# include/alpm/deps.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/deps.h>
			$<INSTALL_INTERFACE:include/alpm/deps.h>
			# include/alpm/diskspace.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/diskspace.h>
			$<INSTALL_INTERFACE:include/alpm/diskspace.h>
			# include/alpm/dload.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/dload.h>
			$<INSTALL_INTERFACE:include/alpm/dload.h>
			# include/alpm/filelist.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/filelist.h>
			$<INSTALL_INTERFACE:include/alpm/filelist.h>
			# include/alpm/graph.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/graph.h>
			$<INSTALL_INTERFACE:include/alpm/graph.h>
			# include/alpm/group.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/group.h>
			$<INSTALL_INTERFACE:include/alpm/group.h>
			# include/alpm/handle.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/handle.h>
			$<INSTALL_INTERFACE:include/alpm/handle.h>
			# include/alpm/hook.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/hook.h>
			$<INSTALL_INTERFACE:include/alpm/hook.h>
			# include/alpm/libarchive-compat.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/libarchive-compat.h>
			$<INSTALL_INTERFACE:include/alpm/libarchive-compat.h>
			# include/alpm/log.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/log.h>
			$<INSTALL_INTERFACE:include/alpm/log.h>
			# include/alpm/package.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/package.h>
			$<INSTALL_INTERFACE:include/alpm/package.h>
			# include/alpm/pkghash.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/pkghash.h>
			$<INSTALL_INTERFACE:include/alpm/pkghash.h>
			# include/alpm/remove.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/remove.h>
			$<INSTALL_INTERFACE:include/alpm/remove.h>
			# include/alpm/signing.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/signing.h>
			$<INSTALL_INTERFACE:include/alpm/signing.h>
			# include/alpm/sync.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/sync.h>
			$<INSTALL_INTERFACE:include/alpm/sync.h>
			# include/alpm/trans.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/trans.h>
			$<INSTALL_INTERFACE:include/alpm/trans.h>
			# include/alpm/util.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/util.h>
			$<INSTALL_INTERFACE:include/alpm/util.h>
)

target_sources (alpm_objlib

    PRIVATE

		# src/alpm/add.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/add.c>
		$<INSTALL_INTERFACE:src/alpm/add.c>
		# src/alpm/alpm.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm.c>
		$<INSTALL_INTERFACE:src/alpm/alpm.c>
		# src/alpm/alpm_list.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm_list.c>
		$<INSTALL_INTERFACE:src/alpm/alpm_list.c>
		# src/alpm/backup.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/backup.c>
		$<INSTALL_INTERFACE:src/alpm/backup.c>
		# src/alpm/base64.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/base64.c>
		$<INSTALL_INTERFACE:src/alpm/base64.c>
		# src/alpm/be_local.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_local.c>
		$<INSTALL_INTERFACE:src/alpm/be_local.c>
		# src/alpm/be_package.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_package.c>
		$<INSTALL_INTERFACE:src/alpm/be_package.c>
		# src/alpm/be_sync.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_sync.c>
		$<INSTALL_INTERFACE:src/alpm/be_sync.c>
		# src/alpm/conflict.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/conflict.c>
		$<INSTALL_INTERFACE:src/alpm/conflict.c>
		# src/alpm/db.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/db.c>
		$<INSTALL_INTERFACE:src/alpm/db.c>
		# src/alpm/deps.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/deps.c>
		$<INSTALL_INTERFACE:src/alpm/deps.c>
		# src/alpm/diskspace.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/diskspace.c>
		$<INSTALL_INTERFACE:src/alpm/diskspace.c>
		# src/alpm/dload.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/dload.c>
		$<INSTALL_INTERFACE:src/alpm/dload.c>
		# src/alpm/error.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/error.c>
		$<INSTALL_INTERFACE:src/alpm/error.c>
		# src/alpm/filelist.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/filelist.c>
		$<INSTALL_INTERFACE:src/alpm/filelist.c>
		# src/alpm/graph.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/graph.c>
		$<INSTALL_INTERFACE:src/alpm/graph.c>
		# src/alpm/group.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/group.c>
		$<INSTALL_INTERFACE:src/alpm/group.c>
		# src/alpm/handle.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/handle.c>
		$<INSTALL_INTERFACE:src/alpm/handle.c>
		# src/alpm/hook.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/hook.c>
		$<INSTALL_INTERFACE:src/alpm/hook.c>
		# src/alpm/log.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/log.c>
		$<INSTALL_INTERFACE:src/alpm/log.c>
		# src/alpm/package.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/package.c>
		$<INSTALL_INTERFACE:src/alpm/package.c>
		# src/alpm/pkghash.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/pkghash.c>
		$<INSTALL_INTERFACE:src/alpm/pkghash.c>
		# src/alpm/rawstr.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/rawstr.c>
		$<INSTALL_INTERFACE:src/alpm/rawstr.c>
		# src/alpm/remove.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/remove.c>
		$<INSTALL_INTERFACE:src/alpm/remove.c>
		# src/alpm/signing.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/signing.c>
		$<INSTALL_INTERFACE:src/alpm/signing.c>
		# src/alpm/sync.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/sync.c>
		$<INSTALL_INTERFACE:src/alpm/sync.c>
		# src/alpm/trans.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/trans.c>
		$<INSTALL_INTERFACE:src/alpm/trans.c>
		# src/alpm/util.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/util.c>
		$<INSTALL_INTERFACE:src/alpm/util.c>
		# src/alpm/version.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/version.c>
		$<INSTALL_INTERFACE:src/alpm/version.c>
)

set_target_properties (alpm_objlib

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin

		C_STANDARD 99
		C_STANDARD_REQUIRED TRUE
		VISIBILITY_INLINES_HIDDEN TRUE
		HAS_CXX FALSE
		#COMPILE_WARNING_AS_ERROR FALSE
)
foreach(_dep IN LISTS ALPM_DEPS)
	add_dependencies(alpm_objlib "${_dep}")
endforeach()
unset(_dep)

target_compile_features(alpm_objlib PUBLIC c_std_99)

target_link_libraries(alpm_objlib PUBLIC configuration)

# libalpm = library(
#   'alpm',
#   version : libalpm_version,
#   objects: libalpm_a.extract_all_objects(recursive: true),
#   include_directories : includes,
#   dependencies : alpm_deps,
#   install : true)

add_library (alpm)
add_library (${PROJECT_NAME}::alpm                    ALIAS alpm)

target_include_directories (alpm

    PUBLIC

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
		$<INSTALL_INTERFACE:include/common>

		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm>
		$<INSTALL_INTERFACE:include/alpm>
)

target_sources(alpm
	PRIVATE

	# src/alpm/add.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/add.c>
	$<INSTALL_INTERFACE:src/alpm/add.c>
	# src/alpm/alpm.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm.c>
	$<INSTALL_INTERFACE:src/alpm/alpm.c>
	# src/alpm/alpm_list.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm_list.c>
	$<INSTALL_INTERFACE:src/alpm/alpm_list.c>
	# src/alpm/backup.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/backup.c>
	$<INSTALL_INTERFACE:src/alpm/backup.c>
	# src/alpm/base64.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/base64.c>
	$<INSTALL_INTERFACE:src/alpm/base64.c>
	# src/alpm/be_local.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_local.c>
	$<INSTALL_INTERFACE:src/alpm/be_local.c>
	# src/alpm/be_package.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_package.c>
	$<INSTALL_INTERFACE:src/alpm/be_package.c>
	# src/alpm/be_sync.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_sync.c>
	$<INSTALL_INTERFACE:src/alpm/be_sync.c>
	# src/alpm/conflict.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/conflict.c>
	$<INSTALL_INTERFACE:src/alpm/conflict.c>
	# src/alpm/db.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/db.c>
	$<INSTALL_INTERFACE:src/alpm/db.c>
	# src/alpm/deps.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/deps.c>
	$<INSTALL_INTERFACE:src/alpm/deps.c>
	# src/alpm/diskspace.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/diskspace.c>
	$<INSTALL_INTERFACE:src/alpm/diskspace.c>
	# src/alpm/dload.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/dload.c>
	$<INSTALL_INTERFACE:src/alpm/dload.c>
	# src/alpm/error.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/error.c>
	$<INSTALL_INTERFACE:src/alpm/error.c>
	# src/alpm/filelist.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/filelist.c>
	$<INSTALL_INTERFACE:src/alpm/filelist.c>
	# src/alpm/graph.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/graph.c>
	$<INSTALL_INTERFACE:src/alpm/graph.c>
	# src/alpm/group.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/group.c>
	$<INSTALL_INTERFACE:src/alpm/group.c>
	# src/alpm/handle.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/handle.c>
	$<INSTALL_INTERFACE:src/alpm/handle.c>
	# src/alpm/hook.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/hook.c>
	$<INSTALL_INTERFACE:src/alpm/hook.c>
	# src/alpm/log.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/log.c>
	$<INSTALL_INTERFACE:src/alpm/log.c>
	# src/alpm/package.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/package.c>
	$<INSTALL_INTERFACE:src/alpm/package.c>
	# src/alpm/pkghash.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/pkghash.c>
	$<INSTALL_INTERFACE:src/alpm/pkghash.c>
	# src/alpm/rawstr.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/rawstr.c>
	$<INSTALL_INTERFACE:src/alpm/rawstr.c>
	# src/alpm/remove.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/remove.c>
	$<INSTALL_INTERFACE:src/alpm/remove.c>
	# src/alpm/signing.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/signing.c>
	$<INSTALL_INTERFACE:src/alpm/signing.c>
	# src/alpm/sync.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/sync.c>
	$<INSTALL_INTERFACE:src/alpm/sync.c>
	# src/alpm/trans.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/trans.c>
	$<INSTALL_INTERFACE:src/alpm/trans.c>
	# src/alpm/util.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/util.c>
	$<INSTALL_INTERFACE:src/alpm/util.c>
	# src/alpm/version.c
	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/version.c>
	$<INSTALL_INTERFACE:src/alpm/version.c>
)


set_target_properties (alpm

    PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY bin
        LIBRARY_OUTPUT_DIRECTORY lib
        ARCHIVE_OUTPUT_DIRECTORY lib
        PDB_OUTPUT_DIRECTORY     bin

		VERSION "${libalpm_version}"

		IMPORTED_OBJECTS ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libalpm_objlib.a

		C_STANDARD 99
		C_STANDARD_REQUIRED TRUE
		VISIBILITY_INLINES_HIDDEN TRUE
		HAS_CXX FALSE
		#COMPILE_WARNING_AS_ERROR FALSE
)
foreach(_dep IN LISTS ALPM_DEPS)
	add_dependencies(alpm "${_dep}")
endforeach()
unset(_dep)

target_compile_features(alpm PUBLIC c_std_99)

target_link_libraries(alpm PUBLIC configuration)


# add_executable(pacman)

# add_executable(pacman-conf)

# add_executable(test-pkg)

# add_executable(vercmp)



## configuration : substs,
## install_dir : SYSCONFDIR
configure_file("etc/makepkg.conf.in" "etc/makepkg.conf")

configure_file("etc/pacman.conf.in" "etc/pacman.conf")
