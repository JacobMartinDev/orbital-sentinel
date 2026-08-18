#pragma once


// ------------------------------------------------------------
// Strong domain types
// ------------------------------------------------------------
// These structs wrap raw double values in meaningful types.
//
// Instead of storing every measurement as a plain double,
// we create dedicated types such as Altitude, Velocity, etc.
//
// This helps the code communicate intent more clearly and can
// help prevent accidentally mixing unrelated values later.
//
// Example:
// Altitude { 100.0 } means "100 m of altitude"
// rather than simply "some double value".
// ------------------------------------------------------------

struct Altitude {
    double value;

    explicit Altitude(double v) : value(v) {}
};

struct Velocity {
    double value;

    explicit Velocity(double v) : value(v) {}
};

struct Fuel {
    double value;

    explicit Fuel(double v) : value(v) {}
};

struct Battery {
    double value;

    explicit Battery(double v) : value(v) {}
};

struct Celsius {
    double value;

    explicit Celsius(double v) : value(v) {}
};

struct ThrusterOutput{
    double value;

    explicit ThrusterOutput(double v) : value(v) {}
};

struct Seconds{
    double value;

    explicit Seconds(double v) : value(v) {}
};

// ------------------------------------------------------------
// Spacecraft
// ------------------------------------------------------------
// The Spacecraft class represents the current state of the
// simulated spacecraft.
//
// Its main responsibilities are:
//
// 1. Own the spacecraft's current state.
// 2. Accept commands that affect the spacecraft.
// 3. Update its state as simulation time passes.
// 4. Allow other parts of the program to safely read that state.
//
// The actual state variables are private so outside code cannot
// directly modify them.
// ------------------------------------------------------------

class Spacecraft {

private:

    // --------------------------------------------------------
    // Current spacecraft state
    // --------------------------------------------------------
    // These values describe the spacecraft at the current
    // moment in the simulation.
    //
    // The trailing "_" is simply a naming convention that helps
    // identify these variables as private class members.
    // --------------------------------------------------------

    Altitude current_altitude_{0.0};          // meters
    Velocity current_velocity_{0.0};          // meters per second
    Fuel fuel_level_{100.0};                  // percent remaining
    Battery battery_percentage_{100.0};       // percent remaining
    Celsius current_temperature_{20.0};       // degrees Celsius
    ThrusterOutput current_thruster_output_{0.0};
    Seconds current_seconds_passed_{0.0};

public:

    // --------------------------------------------------------
    // Constructors
    // --------------------------------------------------------

    // Creates a spacecraft using custom starting values.
    //
    // This allows the simulation to begin from a specific
    // altitude, velocity, fuel level, battery level, and
    // temperature.
    Spacecraft(
        Altitude altitude,
        Velocity velocity,
        Fuel fuel_level,
        Battery battery_percentage,
        Celsius temperature
    );


    // Creates a spacecraft using its default starting state.
    //
    // The default values are the values assigned to the private
    // member variables above.
    Spacecraft();


    // --------------------------------------------------------
    // Commands
    // --------------------------------------------------------
    // Commands tell the spacecraft to DO something.
    //
    // These functions may change the spacecraft's internal state.
    // --------------------------------------------------------

    // Changes the spacecraft's requested thruster output.
    //
    // "output" will eventually represent how strongly the
    // spacecraft's thruster is being commanded.
    void setThruster(ThrusterOutput output);


    // Advances the spacecraft simulation.
    //
    // "dt" means delta time: the amount of simulation time that
    // has passed since the previous update.
    //
    // Eventually this function will be responsible for causing
    // values such as altitude, velocity, fuel, battery, and
    // temperature to change over time.
    void update(Seconds dt);


    // --------------------------------------------------------
    // Queries / Getters
    // --------------------------------------------------------
    // These functions allow the rest of the program to READ the
    // spacecraft's current state without directly accessing the
    // private member variables.
    //
    // The "const" at the end means the function promises not to
    // modify the Spacecraft object while returning the value.
    // --------------------------------------------------------

    Altitude get_altitude() const;

    Velocity get_velocity() const;

    Fuel get_fuel_level() const;

    Battery get_battery_percentage() const;

    Celsius get_temperature() const;

    Seconds get_seconds() const;

    ThrusterOutput get_thruster_output() const;
};