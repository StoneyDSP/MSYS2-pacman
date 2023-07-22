cmake_minimum_required(VERSION 3.17...3.27 FATAL_ERROR)

project(libalpm C)

set(PROJECT_VERSION_MAJOR 13)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 2)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

##############################################################################
##-- Dependency settings
##############################################################################
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
	set(HAVE_LIBCURL true CACHE STRING "") # Stored as a string for lower-case C syntax
endif()

##############################################################################
##-- Targets settings
##############################################################################

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

# find_package(pacman)
target_link_libraries(alpm_objlib PUBLIC pacman::configuration)





# # libalpm = library(
# #   'alpm',
# #   version : libalpm_version,
# #   objects: libalpm_a.extract_all_objects(recursive: true),
# #   include_directories : includes,
# #   dependencies : alpm_deps,
# #   install : true)

# add_library (alpm)
# add_library (${PROJECT_NAME}::alpm                    ALIAS alpm)

# target_include_directories (alpm

#     PUBLIC

# 		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
# 		$<INSTALL_INTERFACE:include/common>

# 		$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/alpm>
# 		$<INSTALL_INTERFACE:include/alpm>
# )

# target_sources(alpm
# 	PRIVATE

# 	# src/alpm/add.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/add.c>
# 	$<INSTALL_INTERFACE:src/alpm/add.c>
# 	# src/alpm/alpm.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm.c>
# 	$<INSTALL_INTERFACE:src/alpm/alpm.c>
# 	# src/alpm/alpm_list.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/alpm_list.c>
# 	$<INSTALL_INTERFACE:src/alpm/alpm_list.c>
# 	# src/alpm/backup.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/backup.c>
# 	$<INSTALL_INTERFACE:src/alpm/backup.c>
# 	# src/alpm/base64.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/base64.c>
# 	$<INSTALL_INTERFACE:src/alpm/base64.c>
# 	# src/alpm/be_local.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_local.c>
# 	$<INSTALL_INTERFACE:src/alpm/be_local.c>
# 	# src/alpm/be_package.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_package.c>
# 	$<INSTALL_INTERFACE:src/alpm/be_package.c>
# 	# src/alpm/be_sync.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/be_sync.c>
# 	$<INSTALL_INTERFACE:src/alpm/be_sync.c>
# 	# src/alpm/conflict.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/conflict.c>
# 	$<INSTALL_INTERFACE:src/alpm/conflict.c>
# 	# src/alpm/db.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/db.c>
# 	$<INSTALL_INTERFACE:src/alpm/db.c>
# 	# src/alpm/deps.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/deps.c>
# 	$<INSTALL_INTERFACE:src/alpm/deps.c>
# 	# src/alpm/diskspace.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/diskspace.c>
# 	$<INSTALL_INTERFACE:src/alpm/diskspace.c>
# 	# src/alpm/dload.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/dload.c>
# 	$<INSTALL_INTERFACE:src/alpm/dload.c>
# 	# src/alpm/error.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/error.c>
# 	$<INSTALL_INTERFACE:src/alpm/error.c>
# 	# src/alpm/filelist.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/filelist.c>
# 	$<INSTALL_INTERFACE:src/alpm/filelist.c>
# 	# src/alpm/graph.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/graph.c>
# 	$<INSTALL_INTERFACE:src/alpm/graph.c>
# 	# src/alpm/group.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/group.c>
# 	$<INSTALL_INTERFACE:src/alpm/group.c>
# 	# src/alpm/handle.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/handle.c>
# 	$<INSTALL_INTERFACE:src/alpm/handle.c>
# 	# src/alpm/hook.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/hook.c>
# 	$<INSTALL_INTERFACE:src/alpm/hook.c>
# 	# src/alpm/log.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/log.c>
# 	$<INSTALL_INTERFACE:src/alpm/log.c>
# 	# src/alpm/package.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/package.c>
# 	$<INSTALL_INTERFACE:src/alpm/package.c>
# 	# src/alpm/pkghash.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/pkghash.c>
# 	$<INSTALL_INTERFACE:src/alpm/pkghash.c>
# 	# src/alpm/rawstr.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/rawstr.c>
# 	$<INSTALL_INTERFACE:src/alpm/rawstr.c>
# 	# src/alpm/remove.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/remove.c>
# 	$<INSTALL_INTERFACE:src/alpm/remove.c>
# 	# src/alpm/signing.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/signing.c>
# 	$<INSTALL_INTERFACE:src/alpm/signing.c>
# 	# src/alpm/sync.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/sync.c>
# 	$<INSTALL_INTERFACE:src/alpm/sync.c>
# 	# src/alpm/trans.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/trans.c>
# 	$<INSTALL_INTERFACE:src/alpm/trans.c>
# 	# src/alpm/util.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/util.c>
# 	$<INSTALL_INTERFACE:src/alpm/util.c>
# 	# src/alpm/version.c
# 	$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/src/alpm/version.c>
# 	$<INSTALL_INTERFACE:src/alpm/version.c>
# )


# set_target_properties (alpm

#     PROPERTIES
#         RUNTIME_OUTPUT_DIRECTORY bin
#         LIBRARY_OUTPUT_DIRECTORY lib
#         ARCHIVE_OUTPUT_DIRECTORY lib
#         PDB_OUTPUT_DIRECTORY     bin

# 		VERSION "${libalpm_version}"

# 		IMPORTED_OBJECTS ${PROJECT_BINARY_DIR}/lib/${CMAKE_BUILD_TYPE}/libalpm_objlib.a

# 		C_STANDARD 99
# 		C_STANDARD_REQUIRED TRUE
# 		VISIBILITY_INLINES_HIDDEN TRUE
# 		HAS_CXX FALSE
# 		#COMPILE_WARNING_AS_ERROR FALSE
# )
# foreach(_dep IN LISTS ALPM_DEPS)
# 	add_dependencies(alpm "${_dep}")
# endforeach()
# unset(_dep)

# target_compile_features(alpm PUBLIC c_std_99)

# target_link_libraries(alpm PUBLIC configuration)
