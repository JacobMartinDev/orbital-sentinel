#pragma once
 
#include <iostream>
#include <chrono>



class Telemetry {
    private: 
        double missionTime{0.0}; 
        std::string missionState {"InitialState"};
};