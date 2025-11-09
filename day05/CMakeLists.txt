add_executable(day05_part1 part1.c)
target_link_libraries(day05_part1 PRIVATE slh)
set_target_properties(
	day05_part1 PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
	OUTPUT_NAME part1
)
