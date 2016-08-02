cmake_minimum_required(VERSION 2.8)

project(plot)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wno-deprecated")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

include_directories(.)

add_executable(illustrator illustrator.cpp GraphicsDisplay.cpp GraphicsFuncs.cpp)
add_executable(complex_in complex_in.cpp GraphicsDisplay.cpp GraphicsFuncs.cpp)
add_executable(graph graph.cpp GraphicsDisplay.cpp GraphicsFuncs.cpp)
add_executable(graph_i graph_i.cpp GraphicsDisplay.cpp GraphicsFuncs.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries( illustrator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( complex_in ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph_i ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
