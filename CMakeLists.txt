cmake_minimum_required(VERSION 3.0)
cmake_policy(SET CMP0076 NEW)

project(gol LANGUAGES C)

# Add target sources and set the executables
set (SRC main.c)
add_executable(${PROJECT_NAME} "")
target_sources(${PROJECT_NAME} PUBLIC ${SRC})

# Add subdirectories
add_subdirectory(console)
add_subdirectory(board)
add_subdirectory(gui)

# Specify libraries to use
target_link_libraries(${PROJECT_NAME} console board gui)

# Install the targets
install(TARGETS ${PROJECT_NAME})

# Look for Doxygen package
find_package(Doxygen)

if (DOXYGEN_FOUND)
  # Set input and output files
  set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)
  set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.out)

  # Request to configure the file
  configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)
  message("Doxygen build started")

  # Add 'doc' target
  add_custom_target(doc
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating API documentation with Doxygen..."
    VERBATIM
  )
else (DOXYGEN_FOUND)
  message("Doxygen needs to be installed to generate the doxygen documentation!")
endif (DOXYGEN_FOUND)

# Add 'dist' target
add_custom_target(dist
  COMMAND mkdir -p dist 
  COMMAND tar cvzf dist/life-1.0.tar.gz --exclude-from=.gitignore --exclude=.git .
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Creating a distribution tar file..."
  VERBATIM
)

# Add 'clear' target
add_custom_target(clear
  COMMAND rm -f *.o game -r doc dist
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Cleaning the build files..."
  VERBATIM
)

set(TEST tests)
add_executable(${TEST})
target_sources(${TEST} PUBLIC test.c)
target_link_libraries(${TEST} PUBLIC cunit board)

enable_testing()
add_test(test ${TEST})
