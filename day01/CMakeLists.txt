add_executable(day01_part1 part1.c)
target_link_libraries(day01_part1 PRIVATE slh)
set_target_properties(
	day01_part1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part1
)
add_executable(day01_part2 part2.c)
target_link_libraries(day01_part2 PRIVATE slh)
set_target_properties(
	day01_part2 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part2
)
