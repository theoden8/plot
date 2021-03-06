cmake_minimum_required(VERSION 2.8)

project(plot)
add_compile_options(-Wno-deprecated)
add_compile_options(-std=c++0x)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

include_directories(. core graphics fractals)

file(GLOB SRC_GRAPHICS graphics/*.cpp)
file(GLOB SRC_FRACTALS fractals/*.cpp)
set(SRC_MATH core/Functions.cpp)
set(SRC_DATA core/Data.cpp)

add_executable(illustrator src/illustrator.cpp ${SRC_GRAPHICS} ${SRC_DATA})
add_executable(complex_in src/complex_in.cpp ${SRC_GRAPHICS} ${SRC_DATA})
add_executable(graph src/graph.cpp ${SRC_GRAPHICS} ${SRC_MATH})
add_executable(graph_i src/graph_i.cpp ${SRC_GRAPHICS} ${SRC_MATH})
add_executable(plot_fractal src/plot_fractal.cpp ${SRC_GRAPHICS} ${SRC_FRACTALS} ${SRC_MATH})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
target_link_libraries( illustrator ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( complex_in ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( graph_i ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
target_link_libraries( plot_fractal ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
