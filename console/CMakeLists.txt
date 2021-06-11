cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(console LANGUAGES C)

# Add library with the target sources
add_library(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC ansi.c ansi.h)

# Include current directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC board)
# Install the targets
install(TARGETS ${PROJECT_NAME})
install(FILES ansi.h DESTINATION include)