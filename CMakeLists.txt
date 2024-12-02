cmake_minimum_required(VERSION 3.21)
get_filename_component(SOURCE_DIR_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
project(${SOURCE_DIR_NAME} VERSION 0.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(GET_SLH_DIR "python" "-m" "slh_c.get_slh_dir")
execute_process(
	COMMAND ${GET_SLH_DIR}
	RESULT_VARIABLE GET_SLH_DIR_RESULT
	OUTPUT_VARIABLE SLH_DIR
	OUTPUT_STRIP_TRAILING_WHITESPACE
	ERROR_VARIABLE GET_SLH_DIR_ERROR
)
if(NOT GET_SLH_DIR_RESULT EQUAL 0)
	message(FATAL_ERROR "Failed to get SLH directory: ${GET_SLH_DIR_ERROR}")
endif()

include_directories(${SLH_DIR}/include)
file(
	GLOB SLH_LIBS RELATIVE
	${SLH_DIR}/lib
	${SLH_DIR}/lib/*
)
foreach(SLH_LIB ${SLH_LIBS})
	link_libraries(${SLH_DIR}/lib/${SLH_LIB})
endforeach()

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
