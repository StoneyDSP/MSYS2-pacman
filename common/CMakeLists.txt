cmake_minimum_required(VERSION 3.17...3.27 FATAL_ERROR)

project(libcommon)
enable_language(C)

if (NOT ${PROJECT_SOURCE_DIR} EQUAL ${PROJECT_BINARY_DIR})

    configure_file ("include/common/ini.h"       								"include/common/ini.h")
	configure_file ("include/common/util-common.h"        						"include/common/util-common.h")

	configure_file ("src/common/ini.c"          								"src/common/ini.c")
    configure_file ("src/common/util-common.c"             						"src/common/util-common.c")

endif ()

add_library (common 															STATIC)
add_library (${CMAKE_PROJECT_NAME}::common                    					ALIAS common)

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
            # include/common/ini.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/ini.h>
            $<INSTALL_INTERFACE:include/common/ini.h>
			# include/common/util-common.h
            $<BUILD_INTERFACE:${PROJECT_BINARY_DIR}/include/common/util-common.h>
            $<INSTALL_INTERFACE:include/common/util-common.h>
)

# include("./src/common/CMakeLists.txt")

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
)

target_compile_features(common PUBLIC c_std_99)

# find_package(pacman)
target_link_libraries(common PUBLIC ${CMAKE_PROJECT_NAME}::configuration)
