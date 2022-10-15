cmake_minimum_required(VERSION 3.0.2)
project(EWAP_display)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
)

catkin_package(


)


include_directories(
 include
  ${catkin_INCLUDE_DIRS}
)

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIRS})
link_directories(${GLUT_LIBRARY_DIRS})
add_definitions(${GLUT_DEFINITIONS})
if(NOT GLUT_FOUND)
    message(ERROR " GLUT not found!")
endif(NOT GLUT_FOUND)

find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

find_package(glfw3 REQUIRED)

add_executable(EWAP_display src/EWAP_display.cpp)
target_link_libraries(EWAP_display ${catkin_LIBRARIES})
target_link_libraries(EWAP_display ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} glfw)
