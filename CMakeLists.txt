project(ziemniak)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


find_package(glfw3 3.3 REQUIRED)
find_package(OpenGL REQUIRED)

add_subdirectory(${PROJECT_SOURCE_DIR}/dep/glad)

add_executable(ziemniak
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/backends/imgui_impl_opengl3.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/backends/imgui_impl_glfw.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/imgui.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/imgui_draw.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/imgui_tables.cpp
	${PROJECT_SOURCE_DIR}/dep/imgui/imgui_widgets.cpp
	${PROJECT_SOURCE_DIR}/dep/imnodes/imnodes.cpp
)

target_link_libraries(ziemniak
	glfw
	OpenGL::GL
	glad
)

target_include_directories(ziemniak
	PUBLIC ${PROJECT_SOURCE_DIR}/dep/glad/include
	PUBLIC ${PROJECT_SOURCE_DIR}/dep/imgui
	PUBLIC ${PROJECT_SOURCE_DIR}/dep/imnodes
)

target_compile_definitions(ziemniak PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)
