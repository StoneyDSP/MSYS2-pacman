set(common_SOURCES)
list(APPEND common_SOURCES

	"ini.c"
	"util-common.c"
)
set(common_SOURCES "${common_SOURCES}" CACHE STRING "")

set(PACMAN_INI_SOURCE)
set(PACMAN_UTIL_COMMON_SOURCE)

file(READ "${CMAKE_CURRENT_LIST_DIR}/ini.c" PM_INI_C)
file(READ "${CMAKE_CURRENT_LIST_DIR}/util-common.c" PM_UTIL_COMMON_C)
