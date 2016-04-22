cmake_minimum_required(VERSION 2.8)

project(_CPP_GLUT)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories(.)

add_executable(_illustrator illustrator.cpp)
add_executable(_graph graph.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries( _illustrator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( _graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
