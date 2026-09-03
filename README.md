# Orbital Sentinel

A modular C++ spacecraft simulation that models core vehicle state over
time and publishes structured telemetry snapshots for real-time health
monitoring.

## What it does

- Simulates a spacecraft's altitude, velocity, fuel, battery, and
  temperature as a function of commanded thruster output, advancing the
  state one discrete time-step at a time.
- Publishes a `Telemetry` snapshot of all state variables after every
  step, decoupling "what the spacecraft is doing" from "who's watching it."
- Classifies fuel, battery, temperature, and overall vehicle health into
  `Nominal` / `Warning` / `Critical` status using threshold-based rules in
  `TelemetryMonitor`.
- Automatically halts the simulation if fuel is depleted or overall
  health reaches `Critical`.

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

This produces two executables:

- `orbital_sentinel` — runs the simulation loop and prints telemetry each step.
- `telemetry_monitor_tests` — runs the automated test suite (see below).

## Testing

`TelemetryMonitor`'s health-classification logic is covered by an
assert-based unit test suite (`tests/test_telemetry_monitor.cpp`) —
23 test cases exercising every threshold boundary for fuel, battery,
and temperature, plus overall-health aggregation:

```bash
./telemetry_monitor_tests
```

## Status

Actively in development. Current focus areas: expanding the physics
model, adding more telemetry channels, and building out the
health-monitoring logic beyond simple thresholds.
