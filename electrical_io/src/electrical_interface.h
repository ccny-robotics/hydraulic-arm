#ifndef ELECTRICAL_INTERFACE_H
#define ELECTRICAL_INTERFACE_H

#include <cstdint>

#include <roboticscape.hpp>

#include "ros/ros.h"

#include "ccny_srvs/GetInt64.h"
#include "std_msgs/Float32.h"
#include "std_msgs/String.h"
#include "std_msgs/UInt16.h"

class ElectricalInterface {
    public:
    typedef ccny_srvs::GetInt64::Request	encoder_req_t;
    typedef ccny_srvs::GetInt64::Response	encoder_res_t;
    typedef std_msgs::Float32::ConstPtr         duty_cycle_t;
    typedef std_msgs::UInt16::ConstPtr          frequency_t;
    typedef ros::TimerEvent                     timer_event_t;

    ElectricalInterface();
    ~ElectricalInterface();
    void setPinMux();
    void initializePWM(int);

    bool getEncoderPosition(encoder_req_t&, encoder_res_t&);
    void setPWMDutyCycle(const duty_cycle_t&);
    void setPWMFrequency(const frequency_t&);
    void updateEncoderPosition(const timer_event_t&); 

    private:
    int64_t position;
};

#endif
