# Setup DB tests
add_executable(shell shell.c)

target_link_libraries(shell PUBLIC utils)
target_include_directories(shell INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
