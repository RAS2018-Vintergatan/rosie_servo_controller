#include "ros/ros.h"
#include "arduino_servo_control/SetServoAngles.h"
#include "rosie_servo_controller/GateAngles.h"
#include <cstdlib>

int saveright = -1;
int saveleft = -1;

void GateCallback(const rosie_servo_controller::GateAngles& msg){
	ROS_INFO("Callback");
    int leftgate = msg.leftgate;
    int rightgate = msg.rightgate;

    if(rightgate != saveright || leftgate != saveleft)
    {
		saveleft = leftgate;
    	saveright = rightgate;

	 	arduino_servo_control::SetServoAngles srv;
	 	srv.request.angle_servo_1 = saveright;
	 	srv.request.angle_servo_0 = saveleft;

		if (ros::service::call("/arduino_servo_control/set_servo_angles", srv))
		{
		  	ROS_INFO("Gates actuated to: LEFT: %d     RIGHT: %d", saveleft,saveright);
		}
		else
		{
		  	ROS_ERROR("Failed to call service SetServoAngles");
		}
	}
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rosie_servo_controller");

  ros::NodeHandle n;

  //ros::ServiceClient client = n.serviceClient<arduino_servo_control::SetServoAngles>("SetServoAngles");

  ros::Subscriber sub = n.subscribe("MoveGates", 1000, GateCallback);

  ros::spin();

  return 0;
}
