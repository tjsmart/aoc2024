cmake_minimum_required(VERSION 3.21)
get_filename_component(SOURCE_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${SOURCE_DIR_NAME} VERSION 0.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(slh)

file(
	GLOB DAY_DIRS RELATIVE
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/day??
)

foreach(DAY_DIR ${DAY_DIRS})
	if (DAY_DIR MATCHES "^day[0-9][0-9]$")
		add_subdirectory(${DAY_DIR})
	endif()
endforeach()
