#include "TelemetryMonitor.hpp"

TelemetryMonitor::TelemetryMonitor(const Spacecraft& spacecraft)
    : spacecraft_(spacecraft)
{
}

HealthStatus TelemetryMonitor::checkFuelHealth() const
{
    double fuel_percentage = spacecraft_.get_fuel_level().value;

    constexpr double WARNING_FUEL = 25.0;
    constexpr double CRITICAL_FUEL = 10.0;

    if (fuel_percentage < CRITICAL_FUEL) {
    return HealthStatus::Critical;
    }
    if (fuel_percentage < WARNING_FUEL) {
    return HealthStatus::Warning;
    }
    return HealthStatus::Nominal;
    
   
}

HealthStatus TelemetryMonitor::checkBatteryHealth() const {

    double battery_percentage = spacecraft_.get_battery_percentage().value;

    constexpr double WARNING_BATTERY = 25.0;
    constexpr double CRITICAL_BATTERY = 10.0;

    if (battery_percentage < CRITICAL_BATTERY) {
    return HealthStatus::Critical;
    }
    if (battery_percentage < WARNING_BATTERY) {
    return HealthStatus::Warning;
    }
    return HealthStatus::Nominal;


}

HealthStatus TelemetryMonitor::checkTemperatureHealth() const {

    double current_temperature = spacecraft_.get_temperature().value;

    constexpr double COLD_WARNING = 0.0;
    constexpr double COLD_CRITICAL = -20.0;

    constexpr double HOT_WARNING = 60.0;
    constexpr double HOT_CRITICAL = 80.0;   

    if (current_temperature < COLD_CRITICAL) {
        return HealthStatus::Critical;
    }
    if (current_temperature < COLD_WARNING) {
        return HealthStatus::Warning;
    }
    if (current_temperature > HOT_CRITICAL) {
        return HealthStatus::Critical;
    }
    if (current_temperature > HOT_WARNING) {
        return HealthStatus::Warning;
    }

    return HealthStatus::Nominal;


}

HealthStatus TelemetryMonitor::checkOverallHealth() const {
    HealthStatus fuelStatus = checkFuelHealth();
    HealthStatus batteryStatus = checkBatteryHealth();
    HealthStatus temperatureStatus = checkTemperatureHealth();

    if (fuelStatus == HealthStatus::Critical || 
        batteryStatus == HealthStatus::Critical || 
        temperatureStatus == HealthStatus::Critical){
            return HealthStatus::Critical;
    } 

    if (fuelStatus == HealthStatus::Warning || 
        batteryStatus == HealthStatus::Warning || 
        temperatureStatus == HealthStatus::Warning){
            return HealthStatus::Warning;
    } 
    
        return HealthStatus::Nominal;
    
}