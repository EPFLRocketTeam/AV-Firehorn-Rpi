//
// Created by marin on 13.08.2024.
//

#ifndef FLIGHT_COMPUTER_MOCKSENSOR_H
#define FLIGHT_COMPUTER_MOCKSENSOR_H

#endif //FLIGHT_COMPUTER_MOCKSENSOR_H

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "sensors.h"

class MockSensor : public SensorInterface {
public:
    MOCK_METHOD(bool,update,(),(override) );
    MOCK_METHOD(void,calibrate,(),(override) );
    MOCK_METHOD(void,update_status,(),(override) );
};
