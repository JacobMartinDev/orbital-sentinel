#include <iostream>
#include <string>
#include "Spacecraft.hpp"
#include "SpacecraftTypes.hpp"
#include "Telemetry.hpp"
#include "TelemetryMonitor.hpp"



std::string healthStatusToString(HealthStatus status){
    switch(status) {
        case HealthStatus::Critical: return "Critical";
        case HealthStatus::Warning: return "Warning";
        case HealthStatus::Nominal: return "Nominal";

    }

    return "Unknown";
}



int main() {
    Spacecraft test_spacecraft;
    TelemetryMonitor monitor;

    test_spacecraft.setThruster(ThrusterOutput{50.0});
    test_spacecraft.update(Seconds{1.0});

    // Capture one complete snapshot after the update
    Telemetry telemetry = test_spacecraft.get_telemetry();

    HealthStatus fuelStatus = monitor.checkFuelHealth(telemetry);
    HealthStatus batteryStatus = monitor.checkBatteryHealth(telemetry);
    HealthStatus temperatureStatus = monitor.checkTemperatureHealth(telemetry);
    HealthStatus overallStatus = monitor.checkOverallHealth(telemetry);

    std::cout << "Time: " << telemetry.time.value << " s\n";
    std::cout << "Altitude: " << telemetry.altitude.value << " m\n";
    std::cout << "Velocity: " << telemetry.velocity.value << " m/s\n";
    std::cout << "Thrust: " << telemetry.thruster.value << " %\n";

    std::cout << "Battery: " << telemetry.battery.value << " %\n";
    std::cout << "Battery Status: " 
              << healthStatusToString(batteryStatus) << '\n';

    std::cout << "Fuel: " << telemetry.fuel.value << " %\n";
    std::cout << "Fuel Status: "
              << healthStatusToString(fuelStatus) << '\n';

    std::cout << "Temperature: "
              << telemetry.temperature.value << " C\n";
    std::cout << "Temperature Status: "
              << healthStatusToString(temperatureStatus) << '\n';

    std::cout << "Overall Health: "
              << healthStatusToString(overallStatus) << '\n';

    

    return 0;
}