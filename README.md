# Orbital Sentinel

A modular C++17 spacecraft simulation that models vehicle state over time and
publishes structured telemetry snapshots to a separate health-monitoring layer.

## What it does

- Simulates altitude, velocity, fuel, battery and temperature as a function of
  commanded thruster output, advancing one fixed time-step at a time.
- Publishes a `Telemetry` snapshot after every step, so the thing being flown
  never knows about the thing watching it.
- Classifies fuel, battery, temperature and overall vehicle health as
  `Nominal` / `Warning` / `Critical` against defined thresholds.
- Cuts thrust automatically when fuel or battery is exhausted, and halts the
  run when overall health reaches `Critical`.

## Design notes

**Units live in the type system.** Every measurement is wrapped in its own type
— `Altitude`, `Velocity`, `Fuel`, `Battery`, `Celsius`, `Seconds` — each with an
`explicit` constructor. Passing a velocity where an altitude belongs is a
compile error rather than a number that looks fine and isn't. Mars Climate
Orbiter was lost to exactly that class of mistake.

**The simulation and the monitor are decoupled.** `Spacecraft` owns state and
advances it. `TelemetryMonitor` reads a snapshot and judges it. Neither includes
the other; `Telemetry` is the entire contract between them. That boundary is
what lets the monitor be tested exhaustively without a simulation running.

**Thresholds use strict inequality, deliberately.** A value sitting exactly on a
boundary resolves to the less severe state. That is a decision rather than an
accident, and the test suite asserts it explicitly at every boundary.

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

Produces two executables — `orbital_sentinel` (the simulation loop) and
`telemetry_monitor_tests` (the verification suite). Multi-config generators
place them in a subfolder such as `build/Debug/`.

## Verification

23 assert-based test cases covering every threshold boundary for fuel, battery
and temperature, plus overall-health aggregation. Each case tests the boundary
value itself along with the values immediately on either side of it.

```
23 / 23 tests passed
```

## Sample run

```
<<< PASTE YOUR 8 TELEMETRY LINES HERE >>>
```

## Known simplifications

- Rate constants are plausible placeholders, not derived from a real vehicle.
- The monitor evaluates whether a value is out of bounds; it does not yet
  evaluate whether the value can be trusted in the first place.
- One-dimensional: no attitude, no orbital mechanics.

## Status

Actively developed. Next: monitoring the *validity* of a reading rather than
only its magnitude — range, rate-of-change and stuck-signal detection ahead of
threshold classification.