#include "ros/ros.h"
#include "std_msgs/Int64.h"

#include <iostream>

#include <roboticscape.hpp>

int main(int argc, char **argv){
	// initialize hardware first
	if(rc_initialize()){
		fprintf(stderr,"ERROR: failed to run rc_initialize(), are you root?\n");
		return -1;
	}

	ros::init(argc, argv, "roboticscape");

	ros::NodeHandle n;
	ros::Publisher encoder_position = n.advertise<std_msgs::Int64>("encoder", 1000);

	ros::Timer encoder_poll = n.createTimer(ros::Duration(0.01),
						[encoder_position](const ros::TimerEvent&) {
		std_msgs::Int64 value;
		value.data = rc_get_encoder_pos(1);
		ROS_INFO("%ld", (long) value.data);

		encoder_position.publish(value);
	});

	ros::spin();
	rc_cleanup();
	return 0;
}
