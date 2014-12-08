#
#
#
#

cmake_minimum_required(VERSION 2.8)
project(MORSE)

enable_testing()

set(MORSE_EXE "morse")
set(MORSE_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include")
set(MORSE_SRC "${PROJECT_SOURCE_DIR}/src")
set(MORSE_TEST "${PROJECT_SOURCE_DIR}/test")
# Uncomment to make makefiles verbose
# set(CMAKE_VERBOSE_MAKEFILE ON)

# gcc flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -D_GNU_SOURCE")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g -DDEBUG")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -DNDEBUG -O3")

# Source Code
add_subdirectory(${MORSE_SRC})
include_directories(${MORSE_INCLUDE_DIR})

set(MORSE_SOURCE_FILES ${SOURCE_FILES})

add_subdirectory(${MORSE_TEST})

add_executable(${MORSE_EXE} ${SOURCE_FILES})
