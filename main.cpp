#include <iostream>
#include "Spacecraft.hpp"
#include "TelemetryMonitor.hpp"



int main() {

Spacecraft test_spacecraft;
TelemetryMonitor monitor(test_spacecraft);

test_spacecraft.setThruster(ThrusterOutput {50.0});
test_spacecraft.update(Seconds{1.0});

HealthStatus fuelStatus = monitor.checkFuelHealth();
HealthStatus batteryStatus = monitor.checkBatteryHealth();
HealthStatus temperatureStatus = monitor.checkTemperatureHealth();
HealthStatus overallStatus = monitor.checkOverallHealth();

std::cout << "Time: " << test_spacecraft.get_seconds().value << " s\n";
std::cout << "Altitude: " << test_spacecraft.get_altitude().value << " m\n";
std::cout << "Velocity: " << test_spacecraft.get_velocity().value << " m/s\n";
std::cout << "Thrust: " << test_spacecraft.get_thruster_output().value << " %\n";

std::cout << "Battery: " << test_spacecraft.get_battery_percentage().value << " %\n";
std::cout << "Battery Status: ";
switch(batteryStatus){
    case HealthStatus::Nominal:
    std::cout << "Nominal\n";
    break;

    case HealthStatus::Warning:
    std::cout << "Warning\n";
    break;

    case HealthStatus::Critical:
    std::cout << "Critical \n";
    break;
}

std::cout << "Fuel: " << test_spacecraft.get_fuel_level().value << " %\n";
std::cout << "Fuel Status: ";
switch(fuelStatus){
    case HealthStatus::Nominal:
    std::cout << "Nominal\n";
    break;

    case HealthStatus::Warning:
    std::cout << "Warning\n";
    break;

    case HealthStatus::Critical:
    std::cout << "Critical \n";
    break;
}

std::cout << "Temperature: " << test_spacecraft.get_temperature().value << " C\n";
std::cout << "Temperature Status: ";
switch(temperatureStatus){
    case HealthStatus::Nominal:
    std::cout << "Nominal \n";
    break;

    case HealthStatus::Warning:
    std::cout << "Warning \n";
    break;
    
    case HealthStatus::Critical:
    std::cout << "Critical \n";
    break;
}

std::cout << "Overall Health: ";
switch(overallStatus){
    case HealthStatus::Nominal:
    std::cout << "Nominal \n";
    break;
    case HealthStatus::Warning:
    std::cout << "Warning \n";
    break;
    case HealthStatus::Critical:
    std::cout << "Critical \n";
    break;
}



    return 0;
}