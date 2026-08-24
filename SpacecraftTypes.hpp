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