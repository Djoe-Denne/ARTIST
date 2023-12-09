cmake_minimum_required (VERSION 3.16)

# Add your test files
file(GLOB_RECURSE game_files ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${PROJECT_NAME}_game_tests ${game_files})

target_link_libraries(${PROJECT_NAME}_game_tests PRIVATE ${PROJECT_NAME} ${SYSLIBS})

# Include directories for GLFW and GLEW
target_include_directories(${PROJECT_NAME}_game_tests PRIVATE ${GLFW_SOURCE_DIR}/include ${GLEW_SOURCE_DIR}/include ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Additional settings for Windows
if (WIN32)
    target_link_libraries(${PROJECT_NAME}_game_tests PRIVATE opengl32)
endif()
