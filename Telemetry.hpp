// Telemetry.hpp represents a snapshot of the spacecraft’s measured
// state at one specific moment.

#pragma once
 
#include "SpacecraftTypes.hpp"



struct Telemetry {
    Seconds time;
    Altitude altitude;
    Velocity velocity;
    Fuel fuel;
    Battery battery;
    Celsius temperature;
    ThrusterOutput thruster;

};

