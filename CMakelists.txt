cmake_minimum_required(VERSION 3.10)
project(philosophers C)

set(CMAKE_C_STANDARD 99)

# Add libft as a subdirectory
add_subdirectory(external/libft)

# Explicitly tell the compiler where to find headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/libft/include)

# Add source files
file(GLOB SOURCES "src/*.c")

# Create executable
add_executable(philosophers ${SOURCES})

# Link libft to your executable
target_link_libraries(philosophers PRIVATE ft)
