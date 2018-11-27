cmake_minimum_required(VERSION 2.8.3)
project(rosie_servo_controller)

find_package(catkin REQUIRED
  roscpp
  std_msgs
  phidgets
  geometry_msgs
  message_generation)

add_message_files(
  FILES
  control_gates.msg
  gate_angles.msg
)
add_service_files(
  FILES
  ControlGates.srv
  GateAngles.srv
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
add_dependencies(rosie_servo_controller ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosie_servo_controller ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_LIBRARIES})
