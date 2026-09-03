// Lightweight assert-based test suite for TelemetryMonitor.
// No external framework required — just build and run this executable.
// Exit code is 0 if all tests pass, 1 if any test fails.

#include "../TelemetryMonitor.hpp"
#include "../Telemetry.hpp"
#include "../SpacecraftTypes.hpp"
#include <iostream>
#include <string>

static int total = 0;
static int passed = 0;

std::string toString(HealthStatus status) {
    switch (status) {
        case HealthStatus::Critical: return "Critical";
        case HealthStatus::Warning:  return "Warning";
        case HealthStatus::Nominal:  return "Nominal";
    }
    return "Unknown";
}

// Builds a Telemetry snapshot with only the fields under test varied;
// unrelated fields are held at safe defaults.
Telemetry makeTelemetry(double fuel = 100.0, double battery = 100.0, double temperature = 20.0) {
    return Telemetry{
        Seconds{0.0},
        Altitude{0.0},
        Velocity{0.0},
        Fuel{fuel},
        Battery{battery},
        Celsius{temperature},
        ThrusterOutput{0.0}
    };
}

void check(const std::string& name, HealthStatus actual, HealthStatus expected) {
    total++;
    if (actual == expected) {
        passed++;
    } else {
        std::cout << "FAIL: " << name
                  << " (expected " << toString(expected)
                  << ", got " << toString(actual) << ")\n";
    }
}

int main() {
    TelemetryMonitor monitor;

    // ---- Fuel: thresholds are Critical < 10.0, Warning < 25.0 ----
    check("Fuel well below critical (1.0)",
          monitor.checkFuelHealth(makeTelemetry(1.0, 100.0, 20.0)), HealthStatus::Critical);
    check("Fuel just below critical boundary (9.9)",
          monitor.checkFuelHealth(makeTelemetry(9.9, 100.0, 20.0)), HealthStatus::Critical);
    check("Fuel exactly at critical boundary (10.0) -> Warning (strict <)",
          monitor.checkFuelHealth(makeTelemetry(10.0, 100.0, 20.0)), HealthStatus::Warning);
    check("Fuel mid-warning range (15.0)",
          monitor.checkFuelHealth(makeTelemetry(15.0, 100.0, 20.0)), HealthStatus::Warning);
    check("Fuel exactly at warning boundary (25.0) -> Nominal (strict <)",
          monitor.checkFuelHealth(makeTelemetry(25.0, 100.0, 20.0)), HealthStatus::Nominal);
    check("Fuel comfortably nominal (80.0)",
          monitor.checkFuelHealth(makeTelemetry(80.0, 100.0, 20.0)), HealthStatus::Nominal);

    // ---- Battery: same thresholds as fuel ----
    check("Battery well below critical (5.0)",
          monitor.checkBatteryHealth(makeTelemetry(100.0, 5.0, 20.0)), HealthStatus::Critical);
    check("Battery exactly at critical boundary (10.0) -> Warning (strict <)",
          monitor.checkBatteryHealth(makeTelemetry(100.0, 10.0, 20.0)), HealthStatus::Warning);
    check("Battery exactly at warning boundary (25.0) -> Nominal (strict <)",
          monitor.checkBatteryHealth(makeTelemetry(100.0, 25.0, 20.0)), HealthStatus::Nominal);
    check("Battery comfortably nominal (90.0)",
          monitor.checkBatteryHealth(makeTelemetry(100.0, 90.0, 20.0)), HealthStatus::Nominal);

    // ---- Temperature: Critical < -20 or > 80, Warning < 0 or > 60 ----
    check("Temperature far below cold-critical (-30)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, -30.0)), HealthStatus::Critical);
    check("Temperature exactly at cold-critical boundary (-20) -> Warning (strict <)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, -20.0)), HealthStatus::Warning);
    check("Temperature mid cold-warning range (-10)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, -10.0)), HealthStatus::Warning);
    check("Temperature exactly at cold-warning boundary (0) -> Nominal (strict <)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 0.0)), HealthStatus::Nominal);
    check("Temperature comfortably nominal (20)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 20.0)), HealthStatus::Nominal);
    check("Temperature exactly at hot-warning boundary (60) -> Nominal (strict >)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 60.0)), HealthStatus::Nominal);
    check("Temperature mid hot-warning range (70)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 70.0)), HealthStatus::Warning);
    check("Temperature exactly at hot-critical boundary (80) -> Warning (strict >)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 80.0)), HealthStatus::Warning);
    check("Temperature above hot-critical (95)",
          monitor.checkTemperatureHealth(makeTelemetry(100.0, 100.0, 95.0)), HealthStatus::Critical);

    // ---- Overall health: worst-of-three aggregation ----
    check("Overall nominal when all subsystems nominal",
          monitor.checkOverallHealth(makeTelemetry(100.0, 100.0, 20.0)), HealthStatus::Nominal);
    check("Overall warning when one subsystem is warning",
          monitor.checkOverallHealth(makeTelemetry(15.0, 100.0, 20.0)), HealthStatus::Warning);
    check("Overall critical when one subsystem is critical",
          monitor.checkOverallHealth(makeTelemetry(5.0, 100.0, 20.0)), HealthStatus::Critical);
    check("Overall critical takes priority over a simultaneous warning",
          monitor.checkOverallHealth(makeTelemetry(15.0, 5.0, 20.0)), HealthStatus::Critical);

    std::cout << "\n" << passed << " / " << total << " tests passed\n";
    return (passed == total) ? 0 : 1;
}
