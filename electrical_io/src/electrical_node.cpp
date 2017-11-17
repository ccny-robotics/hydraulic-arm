#include <array>
#include <cstdint>

#include "electrical_interface.h"
#include "electrical_interface.cpp"

int main(int argc, char **argv){
	ElectricalInterface interface = ElectricalInterface();
	interface.setPinMux();
	interface.initializePWM(25000);

	ros::init(argc, argv, "electrical_interface");
	
	ros::NodeHandle node;
	ros::ServiceServer get_encoder_value =	node.advertiseService("get_position",	&ElectricalInterface::getEncoderPosition,		&interface);

	ros::Subscriber set_duty_cycle =		node.subscribe("set_duty_cycle",	10,	&ElectricalInterface::setPWMDutyCycle,			&interface);
	ros::Subscriber set_frequency =			node.subscribe("set_frequency",		10,	&ElectricalInterface::setPWMFrequency,			&interface);	

	ros::Timer update_encoders =			node.createTimer(ros::Duration(0.01),	&ElectricalInterface::updateEncoderPosition,	&interface);

	ros::spin();	// Blocking call.
	return 0;
}