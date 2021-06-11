cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(gui LANGUAGES C)

# Add library with the target sources
add_library(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC gui.c gui.h)

# Include current directory
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# add target link libraries
target_link_libraries(${PROJECT_NAME} PUBLIC SDL2 SDL2main board)
# Install the targets
install(TARGETS ${PROJECT_NAME})
install(FILES gui.h DESTINATION include)
