add_executable(day01_part1 part1.c)
set_target_properties(
	day01_part1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part1
)
add_executable(day01_part2 part2.c)
set_target_properties(
	day01_part2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part2
)
