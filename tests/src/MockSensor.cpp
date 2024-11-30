//
// Created by marin on 13.08.2024.
//

#include "MockSensor.h"

#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "sensors.h"

using ::testing::Return;

class MockSensorTest : public ::testing::Test {
public:
    MockSensor ms;
};

TEST_F(MockSensorTest, Update) {
    EXPECT_CALL(ms, update()).WillOnce(Return(true));
    EXPECT_TRUE(ms.update());
}

TEST_F(MockSensorTest, Calibrate) {
    EXPECT_CALL(ms, calibrate());
    ms.calibrate();
}

TEST_F(MockSensorTest, UpdateStatus) {
    EXPECT_CALL(ms, update_status());
    ms.update_status();
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}