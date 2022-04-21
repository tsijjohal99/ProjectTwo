cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

# Set project name and version
project(ProjectTwo VERSION 0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug 
    CACHE STRING 
      "Choose the type of build (Debug or Release)" 
      FORCE
    )
endif()

include_directories(include)

# Generate config.h
configure_file(config.h.in config.h)

# Find SFML shared libraries
find_package(SFML 2.5 
  COMPONENTS 
    system window graphics network audio REQUIRED
  )
  
file(COPY resources DESTINATION ${CMAKE_SOURCE_DIR}/build)

set(SRC_FILES src/main2.cpp src/board.cpp src/chessPiece.cpp src/queen.cpp src/king.cpp src/bishop.cpp src/knight.cpp src/rook.cpp src/pawn.cpp)

# Compile executable
add_executable(${PROJECT_NAME} ${SRC_FILES})

# Set include directory search paths
target_include_directories(ProjectTwo 
  PRIVATE
  "${PROJECT_BINARY_DIR}"
  )

# Link executable to required SFML libraries
target_link_libraries(ProjectTwo sfml-graphics)

# Install target
install(TARGETS ProjectTwo DESTINATION bin)