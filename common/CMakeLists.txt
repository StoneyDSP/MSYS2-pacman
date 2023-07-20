cmake_minimum_required(VERSION 3.17...3.27 FATAL_ERROR)

project(libcommon C)

enable_language(CXX)

include(CheckFunctionExists)
set(COMMON_REQUIRED_SYSTEM_FUNCTIONS)
list(APPEND COMMON_REQUIRED_SYSTEM_FUNCTIONS "strndup")
list(APPEND COMMON_REQUIRED_SYSTEM_FUNCTIONS "strnlen")
foreach (_symbol IN LISTS COMMON_REQUIRED_SYSTEM_FUNCTIONS)
	set(CMAKE_REQUIRED_DEFINITIONS "_GNU_SOURCE")
	check_function_exists("${_symbol}" has_${_symbol})
	if(has_${_symbol})
		##-- These shall print integer 0's or 1's
		string(TOUPPER ${_symbol} _symbol)
		set(HAVE_${_symbol} 1 CACHE BOOL "" FORCE)
	endif()
	unset(has_${_symbol})
endforeach()
unset(_symbol)

add_library (common 									STATIC)
add_library (pacman::common                    			ALIAS common)


if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

	configure_file ("include/common/defines.h"       			"include/common/defines.h")
	configure_file ("include/common/config.h"       			"include/common/config.h")

    configure_file ("include/common/ini.h"       				"include/common/ini.h")
	configure_file ("src/common/ini.c"          				"src/common/ini.c")

    configure_file ("include/common/util-common.h"        		"include/common/util-common.h")
    configure_file ("src/common/util-common.c"             		"src/common/util-common.c")

endif ()

target_include_directories (common

    PUBLIC

        $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
        $<INSTALL_INTERFACE:include/common>
)

# include("./include/common/CMakeLists.txt")

target_sources (common

    PUBLIC

        FILE_SET common_PUBLIC_HEADERS
        TYPE HEADERS
        BASE_DIRS
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common>
            $<INSTALL_INTERFACE:include/common>
        FILES
			# include/common/config.h
			$<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/config.h>
			$<INSTALL_INTERFACE:include/common/config.h>
            # include/common/ini.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/ini.h>
            $<INSTALL_INTERFACE:include/common/ini.h>
			# include/common/util-common.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/util-common.h>
            $<INSTALL_INTERFACE:include/common/util-common.h>
)

include("./src/common/CMakeLists.txt")

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
