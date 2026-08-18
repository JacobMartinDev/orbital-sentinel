#pragma once

#include "Spacecraft.hpp"

enum class HealthStatus {
    Nominal,
    Warning,
    Critical
};

class TelemetryMonitor {
public:
    explicit TelemetryMonitor(const Spacecraft& spacecraft);

        HealthStatus checkFuelHealth() const;

        HealthStatus checkBatteryHealth() const;

        HealthStatus checkTemperatureHealth() const;

private:
    const Spacecraft& spacecraft_;
};