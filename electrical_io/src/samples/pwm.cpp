#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/UInt16.h"


#include <iostream>

#include <roboticscape.hpp>

void frequencyCallback(const std_msgs::UInt16::ConstPtr& msg) {
	ROS_INFO("Setting PWM to [%d] Hz", msg->data);
	rc_pwm_init(0, msg->data);
}

void dutyCycleCallback(const std_msgs::Float32::ConstPtr& msg) {
	ROS_INFO("Setting Duty Cycle to [%f] %", msg->data);
	rc_pwm_set_duty_mmap(0, 'A', msg->data);
}

int main(int argc, char **argv){
	// initialize hardware first
	if(rc_initialize()){
		fprintf(stderr, "ERROR: failed to run rc_initialize(), are you root?\n");
		return -1;
	}
	
	rc_set_pinmux_mode(GPS_HEADER_PIN_3, PINMUX_PWM);
	rc_set_pinmux_mode(GPS_HEADER_PIN_4, PINMUX_PWM);

	if(rc_pwm_init(0, 25000)){
		fprintf(stderr, "ERROR: failed to initialize PWM\n");
	}

	ros::init(argc, argv, "roboticscape");

	ros::NodeHandle n;
	ros::Subscriber set_frequency = n.subscribe("frequency", 10, frequencyCallback);
	ros::Subscriber set_pulse_width = n.subscribe("pulse_width", 10, dutyCycleCallback);

	ros::spin();
	rc_pwm_close(0);
	rc_cleanup();
	return 0;
}
