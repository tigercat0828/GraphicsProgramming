cmake_minimum_required(VERSION 3.10)


project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 17)
set(PROGRAM_NAME main)


include_directories(SYSTEM include)


file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "include/*.h")


file(GLOB ASSETS "./Assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})

Add_definitions(-DDEBUG)

add_executable(${PROGRAM_NAME} ${SOURCES})

