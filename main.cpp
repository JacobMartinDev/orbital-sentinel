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

void printTelemetry(const Telemetry& telemetry, HealthStatus overallStatus) {
    std::cout << "t=" << telemetry.time.value << "s"
              << "  alt=" << telemetry.altitude.value << "m"
              << "  vel=" << telemetry.velocity.value << "m/s"
              << "  fuel=" << telemetry.fuel.value << "%"
              << "  batt=" << telemetry.battery.value << "%"
              << "  temp=" << telemetry.temperature.value << "C"
              << "  thrust=" << telemetry.thruster.value << "%"
              << "  status=" << healthStatusToString(overallStatus)
              << '\n';
}

int main() {
    Spacecraft spacecraft;
    TelemetryMonitor monitor;

    spacecraft.setThruster(ThrusterOutput{50.0});

    constexpr double DT_SECONDS = 1.0;
    constexpr int MAX_STEPS = 300;

    // Run the simulation one time-step at a time until either the
    // spacecraft runs out of fuel or we hit the step cap. Each step
    // publishes a full telemetry snapshot and its derived health status,
    // the same way a real flight-software loop would report state on
    // every tick rather than just once at the end.
    for (int step = 0; step < MAX_STEPS; ++step) {
        spacecraft.update(Seconds{DT_SECONDS});

        Telemetry telemetry = spacecraft.get_telemetry();
        HealthStatus overallStatus = monitor.checkOverallHealth(telemetry);

        printTelemetry(telemetry, overallStatus);

        if (overallStatus == HealthStatus::Critical) {
            std::cout << "\nMission critical condition reached at t="
                      << telemetry.time.value << "s. Halting simulation.\n";
            break;
        }

        if (telemetry.fuel.value <= 0.0) {
            std::cout << "\nFuel depleted at t="
                      << telemetry.time.value << "s. Halting simulation.\n";
            break;
        }
    }

    return 0;
}
