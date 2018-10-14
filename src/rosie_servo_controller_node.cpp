#include "ros/ros.h"
#include "arduino_servo_control/SetServoAngles.h"
#include "rosie_servo_controller/GateAngles.h"
#include <cstdlib>

int saveright = 0;
int saveleft = 0;
int saveright2 = 0;
int saveleft2 = 0;

void GateCallback(const rosie_servo_controller::GateAngles& msg){

    int leftgate = msg.leftgate;
    int rightgate = msg.rightgate;

    if(rightgate != saveright)
    {
	arduino_servo_control::SetServoAngles srv;

	if(saveright != saveright2)
  	{
	  arduino_servo_control::SetServoAngles srv;
	  srv.request.angle_servo_0 = saveright;
	  srv.request.angle_servo_1 = saveleft;

		if (ros::service::call("SetServoAngles", srv))
		{
		  ROS_INFO("Gates actuated to: LEFT: %d     RIGHT: %d", saveleft,saveright);
  		  ROS_INFO("Previous values  : LEFT: %d     RIGHT: %d", saveleft2,saveright2);
		}
		else
		{
		  ROS_ERROR("Failed to call service SetServoAngles");
		}
	  saveright2 = saveright;
	  saveleft2 = saveleft;
        } 
	saveleft = leftgate;
        saveright = rightgate;
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
