# Build local libraries
add_library(field_lib STATIC field.c)
add_library(block_lib STATIC block.c)
add_library(timer_lib STATIC timer.c)
add_library(gui_lib STATIC gui.c)
# Build executables
add_executable(TetrisC main.c)
# Link local libraries
target_link_libraries (TetrisC field_lib)
target_link_libraries (TetrisC block_lib)
target_link_libraries (TetrisC timer_lib)
target_link_libraries (TetrisC gui_lib)
# Link public libraries
target_link_libraries(TetrisC m)
target_link_libraries(TetrisC rt)
target_link_libraries(TetrisC ${CURSES_LIBRARIES})
