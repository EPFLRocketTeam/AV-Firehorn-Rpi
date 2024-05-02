// The main flight control module, ran by the main thread.

#include "flightControl.h"

FlightControl::FlightControl() : m_data(), m_state(), previousState(State::IDLE) {
    
}

FlightControl::~FlightControl() {
}


void FlightControl::update() {
    // Get new data
    m_data.update();

    // Update the FSM;
    m_state.update(m_data.dump());

    // Check if the command has been updated
    if (previousState != m_state.getCurrentState()) {
        //do stuff, something like handle_command(previousState, m_state.getCurrentState());
    }

    // Send new data to the ground station
    m_data.send();
}


