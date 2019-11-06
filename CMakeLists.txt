cmake_minimum_required(VERSION 3.14)
project(lab6_maybe)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(freeglut-3.2.1)

add_definitions(-DSOURCE_DIR="${PROJECT_SOURCE_DIR}" -D_CRT_SECURE_NO_WARNINGS)

add_executable(lab6 main.cpp)
#find_package(OpenGL REQUIRED)
#find_package(GLUT REQUIRED)
include_directories( "${PROJECT_SOURCE_DIR}/include"
        ${OPENGL_INCLUDE_DIRS}
        "${PROJECT_SOURCE_DIR}/freeglut-3.2.1/include" )
link_directories("${PROJECT_SOURCE_DIR}/freeglut-3.2.1/lib")
target_link_libraries(lab6 ${OPENGL_LIBRARIES} freeglut_static )