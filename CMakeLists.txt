cmake_minimum_required(VERSION 2.8)

project(plot)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3 -Wno-deprecated")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

include_directories(. graphics fractals)

file(GLOB SRC_GRAPHICS graphics/*.cpp)
file(GLOB SRC_FRACTALS fractals/*.cpp)

add_executable(illustrator illustrator.cpp ${SRC_GRAPHICS})
add_executable(complex_in complex_in.cpp ${SRC_GRAPHICS})
add_executable(graph graph.cpp ${SRC_GRAPHICS})
add_executable(graph_i graph_i.cpp ${SRC_GRAPHICS})
add_executable(plot_fractal plot_fractal.cpp ${SRC_GRAPHICS} ${SRC_FRACTALS})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries( illustrator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( complex_in ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph_i ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( plot_fractal ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
