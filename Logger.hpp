#pragma once

#include <iostream>
#include <chrono>

class Logger {
    private:
        double altitude {0.0};
        double velocity {0.0};
        double fuel {100.0};
        double battery {100.0};
        double temperature {20.0};
        double missionTime {0.0};
        std::string missionState {"InitialState"};

};