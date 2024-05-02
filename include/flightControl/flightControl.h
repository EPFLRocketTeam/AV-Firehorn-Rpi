#ifndef flightControl_H
#define flightControl_H

#include "data.h"
#include "AvState.h"

class FlightControl {
public:
    FlightControl();
    ~FlightControl();

    bool update();
private:
    Data m_data;
    AvState m_state;
    State previousState;
};


#endif /* flightControl_H */