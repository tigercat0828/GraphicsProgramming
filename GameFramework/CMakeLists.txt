# sdl2 glad glm spdlog imgui

cmake_minimum_required(VERSION 3.10)

# 設置專案名稱
project(OpenGLTemplate)

set(EXECUTABLE_NAME main)

# 指定C++標準
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

# 添加頭文件目錄
include_directories(include)
include_directories(include/imgui)


file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c")
add_executable(${EXECUTABLE_NAME} ${SOURCES} "src/Shader.h" "src/stb_image.h" "src/Texture.h" "src/VAO.h" "src/VBO.h" "src/EBO.h")

# config spdlog
set(spdlog_DIR "${CMAKE_SOURCE_DIR}/Library/spdlog")
include_directories(${spdlog_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME} 
	${spdlog_DIR}/lib/spdlog.lib
)

# config glm
set(glm_DIR "${CMAKE_SOURCE_DIR}/Library/glm")
include_directories(${glm_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME}
    ${glm_DIR}/lib/glm.lib
)

# config SDL2
set(SDL2_DIR "${CMAKE_SOURCE_DIR}/Library/SDL2")
include_directories(${SDL2_DIR}/include)
target_link_libraries(${EXECUTABLE_NAME} 
	${SDL2_DIR}/lib/x64/SDL2.lib
    ${SDL2_DIR}/lib/x64/SDL2main.lib
)

# config GLAD
set(GLAD_DIR "${CMAKE_SOURCE_DIR}/Library/glad")
include_directories(${GLAD_DIR}/include)

# ================================================
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin"
)

# 設定輸出目錄
set(OUTPUT_DIR "${CMAKE_SOURCE_DIR}/bin")
# 複製 Assets 資料夾到輸出目錄
file(COPY "${CMAKE_SOURCE_DIR}/Assets" DESTINATION "${OUTPUT_DIR}")
file(COPY "${SDL2_DIR}/lib/x64/SDL2.dll" DESTINATION "${OUTPUT_DIR}")


