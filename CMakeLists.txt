cmake_minimum_required(VERSION 2.8.3)
project(rosie_servo_controller)

find_package(catkin REQUIRED COMPONENTS roscpp std_msgs phidgets geometry_msgs message_generation)

add_message_files(
  FILES
  SetServoAngles.msg
)

generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  DEPENDS
  CATKIN_DEPENDS roscpp std_msgs phidgets geometry_msgs message_runtime
  LIBRARIES
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

add_executable(rosie_servo_controller src/rosie_servo_controller_node.cpp)
target_link_libraries(rosie_servo_controller ${catkin_LIBRARIES})
add_dependencies(rosie_servo_controller std_msgs phidgets geometry_msgs)
