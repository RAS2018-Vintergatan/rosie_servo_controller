cmake_minimum_required(VERSION 2.8.3)
project(rosie_servo_controller)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  phidgets
  geometry_msgs
  message_generation)

add_message_files(
  FILES
  control_gates.msg
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

#add_executable(rosie_servo_controller src/rosie_servo_controller_node.cpp)
#add_dependencies(rosie_servo_controller std_msgs phidgets geometry_msgs ${catkin_EXPORTED_TARGETS})
#target_link_libraries(rosie_servo_controller ${catkin_LIBRARIES})
add_executable(rosie_servo_controller_new src/rosie_servo_controller_node_new.cpp)
add_dependencies(rosie_servo_controller_new ${catkin_EXPORTED_TARGETS})
target_link_libraries(rosie_servo_controller_new ${catkin_LIBRARIES})
