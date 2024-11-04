cmake_minimum_required(VERSION 1.0)


project(OpenGLTemplate)

set(CMAKE_CXX_STANDARD 17)
set(PROGRAM_NAME main)
set(LIBRARY_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/lib")


include_directories(SYSTEM include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/include)
include_directories(SYSTEM ${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/include/imgui)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "include/*.h")




file(GLOB ASSETS "./Assets")
file(COPY ${ASSETS} DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ${LIBRARY_DIR}/SDL2/SDL2.dll DESTINATION ${CMAKE_BINARY_DIR})


Add_definitions(-DDEBUG)

add_executable(${PROGRAM_NAME} ${SOURCES} "src/Modules/PLYfile.cpp" "include/Color.h" "src/Color.cpp")
# SDL2
target_link_libraries(${PROGRAM_NAME} 
	${LIBRARY_DIR}/SDL2/SDL2.lib
	${LIBRARY_DIR}/SDL2/SDL2main.lib
	${LIBRARY_DIR}/spdlog/spdlog.lib
	${LIBRARY_DIR}/glm/glm.lib
) 