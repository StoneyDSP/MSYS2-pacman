cmake_minimum_required(VERSION 3.17...3.26 FATAL_ERROR)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/scripts/cmake/Modules")

if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Specifies the build type on single-configuration generators" FORCE)
endif()

project(pacman C)
enable_language(CXX)

# include(GNUInstallDirs)

##############################################################################
##-- Project Options
##############################################################################
option(USE_GIT_VERSION "take version information from git" ON)
option(BUILD_SHARED_LIBS "if false, build statically linked binaries" ON)
option(USE_I18N "" ON)

##############################################################################
##-- Project settings
##############################################################################
set(PROJECT_VERSION_MAJOR 6 CACHE STRING "First version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set(PROJECT_VERSION_MINOR 0 CACHE STRING "Second version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
set(PROJECT_VERSION_PATCH 2 CACHE STRING "Third version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
if(USE_GIT_VERSION)
	include(GetSourceInfo)
	get_source_info()
	set(PROJECT_VERSION_TWEAK "${git_revision}")
else()
	set(PROJECT_VERSION_TWEAK "-cmake-build" CACHE STRING "Fourth version number component of the ``PROJECT_VERSION`` variable as set by the ``project()`` command." FORCE)
endif()
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}.${PROJECT_VERSION_TWEAK}" CACHE STRING "Value given to the ``VERSION`` option of the most recent call to the ``project()`` command, if any." FORCE)

set(PACKAGE "${PROJECT_NAME}" CACHE STRING "")
set(PACKAGE_VERSION "${PROJECT_VERSION}" CACHE STRING "")

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

##############################################################################
##-- Targets settings
##############################################################################

add_subdirectory(common)
set(LibCommon_DIR "${CMAKE_CURRENT_LIST_DIR}/common")

add_subdirectory(libalpm)

add_subdirectory(config)

# add_executable(pacman)

# add_executable(pacman-conf)

# add_executable(test-pkg)

# add_executable(vercmp)

add_subdirectory(libmakepkg)

## configuration : substs,
## install_dir : SYSCONFDIR
configure_file("etc/makepkg.conf.in" "etc/makepkg.conf")

configure_file("etc/pacman.conf.in" "etc/pacman.conf")
