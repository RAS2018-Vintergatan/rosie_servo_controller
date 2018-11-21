#include "ros/ros.h"
#include "arduino_servo_control/SetServoAngles.h"
#include "rosie_servo_controller/ControlGates.h"
#include "rosie_servo_controller/GateAngles.h"
#include <cstdlib>

int leftgate_open = 45;
int leftgate_close = 0;
int rightgate_open = 135;
int rightgate_close = 185;

int saveleft = leftgate_open;
int saveright = rightgate_close;
int isInitialized = 0;

bool callback( rosie_servo_controller::ControlGates::Request & req, rosie_servo_controller::ControlGates::Response & res){
	ROS_INFO("Callback");
	if(req.control == 0){
		saveleft = leftgate_close;
		saveright = rightgate_close;
		//res.result = 0;
	}else if(req.control == 1){
		saveleft = leftgate_open;
		saveright = rightgate_open;
		//res.result = 1;
	}else{
		ROS_INFO("This is an unvalid operation. Requested: %d", req.control);
	}

	arduino_servo_control::SetServoAngles srv;
	srv.request.angle_servo_1 = saveright;
	srv.request.angle_servo_0 = saveleft;

  	if(!isInitialized){
		srv.request.angle_servo_1 = rightgate_open;
		srv.request.angle_servo_0 = leftgate_open;
	    isInitialized = 1;
  	}

	if (ros::service::call("/arduino_servo_control/set_servo_angles", srv))
	{
			res.result = 1;
			ROS_INFO("Gates actuated to: LEFT: %d     RIGHT: %d", saveleft,saveright);
	}
	else
	{
		  res.result = 0;
			ROS_ERROR("Failed to call service SetServoAngles");
	}
	return true;
}

bool calCallback(rosie_servo_controller::GateAngles::Request & msg, rosie_servo_controller::GateAngles::Response & res){
	leftgate_open = msg.leftgate_open;
	leftgate_close = msg.leftgate_close;
	rightgate_open = msg.rightgate_open;
	rightgate_close = msg.rightgate_close;
	res.res = true;
	return true;
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "rosie_servo_server");

  ros::NodeHandle n;

  //ros::ServiceClient client = n.serviceClient<arduino_servo_control::SetServoAngles>("SetServoAngles");
  ros::ServiceServer service = n.advertiseService<rosie_servo_controller::ControlGates::Request, rosie_servo_controller::ControlGates::Response>("rosie_servo_service", callback);
  ros::ServiceServer setAngles = n.advertiseService<rosie_servo_controller::GateAngles::Request,rosie_servo_controller::GateAngles::Response>("calibrateGates", calCallback);
  ROS_INFO("Ready to move the grippers.");


  ros::spin();

  return 0;
}
