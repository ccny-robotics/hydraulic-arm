#include "electrical_interface.h"

/* Public Methods */
ElectricalInterface::ElectricalInterface() :
    position(0)
{
    if(rc_initialize()) throw std::runtime_error("[electrical_io] ERROR: failed to run rc_initialize(), are you root?\n");
}

ElectricalInterface::~ElectricalInterface() {
    rc_pwm_close(0);
	rc_cleanup();
}

void ElectricalInterface::setPinMux() {
    if(rc_set_pinmux_mode(GPS_HEADER_PIN_3, PINMUX_PWM) || rc_set_pinmux_mode(GPS_HEADER_PIN_4, PINMUX_PWM))
        ROS_ERROR("[electrical_io] ERROR: Pin Muxing failed");
}

void ElectricalInterface::initializePWM(int freq = 25000) {
    if(rc_pwm_init(0, freq)) throw std::runtime_error("[electrical_io] ERROR: failed to initialize PWM\n");
}

bool ElectricalInterface::getEncoderPosition(encoder_req_t &req, encoder_res_t &res) {
    res.value = this->position;
    ROS_INFO("[electrical_io] Sent encoder value [%ld]", (long) res.value);

    return true;
}

void ElectricalInterface::setPWMDutyCycle(const duty_cycle_t& msg) {
	if(rc_pwm_set_duty_mmap(0, 'A', msg->data))
        ROS_ERROR("[electrical_io] ERROR: failed to set PWM Duty Cycle");
    else
        ROS_INFO("[electrical_io] Set PWM Duty Cycle to [%f] percent", msg->data * 100);
}

void ElectricalInterface::setPWMFrequency(const frequency_t& msg) {
	if(rc_pwm_init(0, msg->data))
        ROS_ERROR("[electrical_io] ERROR: failed to set PWM Frequency");
    else
        ROS_INFO("[electrical_io] Set PWM Frequency to [%d] Hz", msg->data);
}

void ElectricalInterface::updateEncoderPosition(const timer_event_t&) {
    this->position = rc_get_encoder_pos(1);
}