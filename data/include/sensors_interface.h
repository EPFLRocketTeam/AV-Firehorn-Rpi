#ifndef SENSOR_INTERFACE_H
#define SENSOR_INTERFACE_H

#include <cstdint>

class SensorInterface {
public:
    virtual ~SensorInterface() = default;
    virtual void calibrate() = 0;
    virtual bool update() = 0;
private :
    virtual void update_status() = 0;
};


#endif // SENSOR_INTERFACE_H