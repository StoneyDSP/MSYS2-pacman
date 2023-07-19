cmake_minimum_required(VERSION 3.17...3.27 FATAL_ERROR)

project(libalpm C)

enable_language(CXX)

set(PROJECT_VERSION_MAJOR 13)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

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
	set(HAVE_LIBCURL true CACHE BOOL "")
endif()

set(PACKAGE "${PROJECT_NAME}" CACHE STRING "")
set(PACKAGE_VERSION "${PROJECT_VERSION}" CACHE STRING "")


include(CheckIncludeFile)
set(LIBALPM_REQUIRED_SYSTEM_HEADERS)
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "mntent.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/mnttab.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/mount.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/param.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/statvfs.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/types.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "sys/ucred.h")
list(APPEND LIBALPM_REQUIRED_SYSTEM_HEADERS "termios.h")
foreach (_header IN LISTS LIBALPM_REQUIRED_SYSTEM_HEADERS)
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
set(LIBALPM_REQUIRED_SYSTEM_FUNCTIONS)
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "getmntent")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "getmntinfo")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "strndup")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "strnlen")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "strsep")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "swprintf")
list(APPEND LIBALPM_REQUIRED_SYSTEM_FUNCTIONS "tcflush")
foreach (_symbol IN LISTS LIBALPM_REQUIRED_SYSTEM_FUNCTIONS)
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
CHECK_STRUCT_HAS_MEMBER("struct stat" st_blksize "sys/stat.h" HAVE_STRUCT_STAT_ST_BLKSIZE LANGUAGE C)
CHECK_STRUCT_HAS_MEMBER("struct statvfs" f_flag "sys/statvfs.h" HAVE_STRUCT_STATVFS_F_FLAG LANGUAGE C)
CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/param.h" LANGUAGE C)
if(HAVE_STRUCT_STATFS_F_FLAGS_SYS_PARAM_H)
	set(HAVE_STRUCT_STATFS_F_FLAGS true CACHE BOOL "" FORCE)
else()
	CHECK_STRUCT_HAS_MEMBER("struct statfs" f_flags "sys/mount.h" HAVE_STRUCT_STATFS_F_FLAGS_SYS_MOUNT_H LANGUAGE C)
	if(HAVE_STRUCT_STATFS_F_FLAGS_SYS_MOUNT_H)
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
  	set(FSSTATSTYPE "struct statvfs" CACHE STRING "")
elseif (HAVE_STRUCT_STATFS_F_FLAGS)
  	set(FSSTATSTYPE "struct statfs" CACHE STRING "")
endif ()

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
	configure_file("include/alpm/ini.h" 	"include/alpm/ini.h")
	configure_file("include/alpm/libarchive-compat.h" 	"include/alpm/libarchive-compat.h")
	configure_file("include/alpm/log.h" 	"include/alpm/log.h")
	configure_file("include/alpm/package.h" 	"include/alpm/package.h")
	configure_file("include/alpm/pkghash.h" 	"include/alpm/pkghash.h")
	configure_file("include/alpm/remove.h" 	"include/alpm/remove.h")
	configure_file("include/alpm/signing.h" 	"include/alpm/signing.h")
	configure_file("include/alpm/sync.h" 	"include/alpm/sync.h")
	configure_file("include/alpm/trans.h" 	"include/alpm/trans.h")
	configure_file("include/alpm/util-common.h" 	"include/alpm/util-common.h")
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
	configure_file("src/alpm/ini.c" 	"src/alpm/ini.c")
	configure_file("src/alpm/log.c" 		"src/alpm/log.c")
	configure_file("src/alpm/package.c" 		"src/alpm/package.c")
	configure_file("src/alpm/pkghash.c" 		"src/alpm/pkghash.c")
	configure_file("src/alpm/rawstr.c" 		"src/alpm/rawstr.c")
	configure_file("src/alpm/remove.c" 		"src/alpm/remove.c")
	configure_file("src/alpm/signing.c" 		"src/alpm/signing.c")
	configure_file("src/alpm/sync.c" 		"src/alpm/sync.c")
	configure_file("src/alpm/trans.c" 		"src/alpm/trans.c")
	configure_file("src/alpm/util-common.c" 		"src/alpm/util-common.c")
	configure_file("src/alpm/util.c" 		"src/alpm/util.c")
	configure_file("src/alpm/version.c" 		"src/alpm/version.c")

endif ()

target_include_directories (alpm_objlib

    PUBLIC

		# $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
		# $<INSTALL_INTERFACE:include/common>

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
			# include/alpm/ini.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/ini.h>
			$<INSTALL_INTERFACE:include/alpm/ini.h>
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
			# include/alpm/util-common.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm/util-common.h>
			$<INSTALL_INTERFACE:include/alpm/util-common.h>
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
		# src/alpm/ini.c -- ################################################
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/ini.c>
		$<INSTALL_INTERFACE:src/alpm/ini.c>
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
		# src/alpm/util-common.c
		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/util-common.c>
		$<INSTALL_INTERFACE:src/alpm/util-common.c>
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

		#IMPORTED_OBJECTS ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libcommon.a

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

# target_link_libraries(alpm_objlib PUBLIC configuration)
