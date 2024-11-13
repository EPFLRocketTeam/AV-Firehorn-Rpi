#include <stdint.h>
#include "bmi08.h"

class Bmi088_Interface {
    public:
    virtual ~Bmi088_Interface() = default;
    virtual uint8_t get_accel_status() = 0;
    virtual uint8_t get_gyro_status() = 0;
    virtual bmi08_sensor_data_f get_accel_data() = 0;
    virtual bmi08_sensor_data_f get_gyro_data() = 0;
};