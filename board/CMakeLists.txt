cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(board LANGUAGES C)

# Add library with the target sources
add_library(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC board.c board.h)

# Include current directory and other needed libraries
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} console)

# Install the targets
install(TARGETS ${PROJECT_NAME})
install(FILES board.h DESTINATION include)