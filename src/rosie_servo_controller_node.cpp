#include "ros/ros.h"
#include "arduino_servo_control/SetServoAngles.h"
#include "rosie_servo_controller/GateAngles.h"
#include <cstdlib>

int saveright = 0;
int saveleft = 0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rosie_servo_controller");

  ros::NodeHandle n;

  ros::ServiceClient gateclient = n.serviceClient<arduino_servo_control::SetServoAngles>("SetServoAngles");

  ros::Subscriber sub = n.subscribe("Gates", 1000, GateCallback);

  ros::spin();

  return 0;
}

void Gatecallback(const rosie_servo_contoller::GateAngles& msg){

    int leftgate = msg->angle_left;
    int rightgate = msg->angle_right;

    if(rightgate != saveright)
    {
        arduino_servo_control::SetServoAngles srv;
        srv.request.angle_servo_0 = x;
        srv.request.angle_servo_1 = y;

        if (client.call(srv))
        {
          ROS_INFO("Gates actuated to: LEFT: %d     RIGHT: %d", saveleft,saveright);
        }
        else
        {
          ROS_ERROR("Failed to call service SetServoAngles");
          return 1;
        }
        saveleft = leftgate;
        saveright = rightgate;
    }
}
