#include <iostream>

#include "Spacecraft.hpp"
#include "SpacecraftTypes.hpp"
#include "Telemetry.hpp"
#include "TelemetryMonitor.hpp"

int main() {
    Spacecraft test_spacecraft;
    TelemetryMonitor monitor(test_spacecraft);

    test_spacecraft.setThruster(ThrusterOutput{50.0});
    test_spacecraft.update(Seconds{1.0});

    // Capture one complete snapshot after the update
    Telemetry telemetry = test_spacecraft.get_telemetry();

    HealthStatus fuelStatus = monitor.checkFuelHealth();
    HealthStatus batteryStatus = monitor.checkBatteryHealth();
    HealthStatus temperatureStatus = monitor.checkTemperatureHealth();
    HealthStatus overallStatus = monitor.checkOverallHealth();

    std::cout << "Time: " << telemetry.time.value << " s\n";
    std::cout << "Altitude: " << telemetry.altitude.value << " m\n";
    std::cout << "Velocity: " << telemetry.velocity.value << " m/s\n";
    std::cout << "Thrust: " << telemetry.thruster.value << " %\n";

    std::cout << "Battery: " << telemetry.battery.value << " %\n";
    std::cout << "Battery Status: ";

    switch (batteryStatus) {
        case HealthStatus::Nominal:
            std::cout << "Nominal\n";
            break;

        case HealthStatus::Warning:
            std::cout << "Warning\n";
            break;

        case HealthStatus::Critical:
            std::cout << "Critical\n";
            break;
    }

    std::cout << "Fuel: " << telemetry.fuel.value << " %\n";
    std::cout << "Fuel Status: ";

    switch (fuelStatus) {
        case HealthStatus::Nominal:
            std::cout << "Nominal\n";
            break;

        case HealthStatus::Warning:
            std::cout << "Warning\n";
            break;

        case HealthStatus::Critical:
            std::cout << "Critical\n";
            break;
    }

    std::cout << "Temperature: "
              << telemetry.temperature.value << " C\n";
    std::cout << "Temperature Status: ";

    switch (temperatureStatus) {
        case HealthStatus::Nominal:
            std::cout << "Nominal\n";
            break;

        case HealthStatus::Warning:
            std::cout << "Warning\n";
            break;

        case HealthStatus::Critical:
            std::cout << "Critical\n";
            break;
    }

    std::cout << "Overall Health: ";

    switch (overallStatus) {
        case HealthStatus::Nominal:
            std::cout << "Nominal\n";
            break;

        case HealthStatus::Warning:
            std::cout << "Warning\n";
            break;

        case HealthStatus::Critical:
            std::cout << "Critical\n";
            break;
    }

    return 0;
}