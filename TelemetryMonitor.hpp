#pragma once

#include "Telemetry.hpp"

enum class HealthStatus {
    Nominal,
    Warning,
    Critical
};

class TelemetryMonitor {
public:
    HealthStatus checkFuelHealth(const Telemetry& telemetry) const;

    HealthStatus checkBatteryHealth(const Telemetry& telemetry) const;

    HealthStatus checkTemperatureHealth(const Telemetry& telemetry) const;

    HealthStatus checkOverallHealth(const Telemetry& telemetry) const;


};



