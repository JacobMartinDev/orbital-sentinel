#include "Spacecraft.hpp"
#include <algorithm>
#include <iostream>

// Default Constructor
Spacecraft::Spacecraft() {}

// Custom Constructor
Spacecraft::Spacecraft(
    Altitude altitude,
    Velocity velocity,
    Fuel fuel_level,
    Battery battery_percentage,
    Celsius temperature)

        : current_altitude_(altitude),
          current_velocity_(velocity),
          fuel_level_(fuel_level),
          battery_percentage_(battery_percentage),
          current_temperature_(temperature) 
          {}

// Getters
  Altitude Spacecraft::get_altitude() const {
    return current_altitude_;
  }       
  
  Velocity Spacecraft::get_velocity() const {
    return current_velocity_;
  }

  Fuel Spacecraft::get_fuel_level() const {
    return fuel_level_;
  }

  Battery Spacecraft::get_battery_percentage() const {
    return battery_percentage_;
  }

  Celsius Spacecraft::get_temperature() const {
    return current_temperature_;
  }

  Seconds Spacecraft::get_seconds() const {
    return current_seconds_passed_;
  }

  ThrusterOutput Spacecraft::get_thruster_output() const {
    return current_thruster_output_;
}

Telemetry Spacecraft::get_telemetry() const {
    return Telemetry{
        current_seconds_passed_,
        current_altitude_,
        current_velocity_,
        fuel_level_,
        battery_percentage_,
        current_temperature_,
        current_thruster_output_
    };
}

void Spacecraft::setThruster(ThrusterOutput output) {
    current_thruster_output_ = output;
}

void Spacecraft::update(Seconds dt) {
    // 1. Track total time elapsed
    current_seconds_passed_.value += dt.value;

    double thruster_fraction = current_thruster_output_.value / 100.0;

    // 2. Calculate rates
    double acceleration_rate = thruster_fraction * 5.5;
    double fuel_rate         = thruster_fraction * -0.5;
    double battery_rate      = thruster_fraction * -0.2;
    double temperature_rate  = thruster_fraction * 1.5;

    // 3. Update altitude using current velocity + acceleration over time
    current_altitude_.value +=
        current_velocity_.value * dt.value
        + 0.5 * acceleration_rate * dt.value * dt.value;

    // 4. Update velocity
    current_velocity_.value += acceleration_rate * dt.value;

    // 5. Update remaining spacecraft state
    current_temperature_.value += temperature_rate * dt.value;

    // TODO 1: Update fuel_level_.value using fuel_rate, same as before,
    //         but wrap the result in std::clamp(..., 0.0, 100.0)
    //         so it can never go negative or above 100.
    fuel_level_.value = std::clamp(fuel_level_.value + fuel_rate * dt.value, 0.0, 100.0);

    if (fuel_level_.value <= 0.0){
      current_thruster_output_ = ThrusterOutput{0.0};
    }
    // TODO 2: Do the same for battery_percentage_.value using battery_rate.
    battery_percentage_.value = std::clamp(battery_percentage_.value + battery_rate * dt.value, 0.0, 100.0);

    if (battery_percentage_.value <= 0.0) {
      current_thruster_output_ = ThrusterOutput{0.0};
    }
    // TODO 3: After fuel is updated, check: if fuel_level_.value is <= 0.0,
    //         force current_thruster_output_ back to ThrusterOutput{0.0}.
    //         Think about WHERE this check needs to go relative to TODO 1 —
    //         it needs the *updated* fuel value, not the old one.


}