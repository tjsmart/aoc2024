add_executable(day03_part1 part1.c)
set_target_properties(
	day03_part1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part1
)
add_executable(day03_part2 part2.c)
set_target_properties(
	day03_part2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part2
)
