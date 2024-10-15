cmake_minimum_required(VERSION 3.10)

# 設置專案名稱
project(TestCMake)

set(EXECUTABLE_NAME demo)

# 指定C++標準
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 添加頭文件目錄
include_directories(include)

# 添加可執行文件
add_executable(${EXECUTABLE_NAME} src/main.cpp)

# config SDL2
# find_package(SDL2 REQUIRED)
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/Library/SDL2")
set(SDL2_LIB_DIR "${SDL2_DIR}/lib/x64")
include_directories(${SDL2_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME} 
	${SDL2_LIB_DIR}/SDL2.lib
	${SDL2_LIB_DIR}/SDL2main.lib
)
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    "${SDL2_LIB_DIR}/SDL2.dll"
    $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
)


