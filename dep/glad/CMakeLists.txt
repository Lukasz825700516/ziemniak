project(glad)

add_library(glad
	${PROJECT_SOURCE_DIR}/src/glad.c
)

target_link_libraries(glad
	dl
)

target_include_directories(glad
	PUBLIC ${PROJECT_SOURCE_DIR}/include
)
