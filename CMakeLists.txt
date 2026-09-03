cmake_minimum_required(VERSION 3.10)
project(OrbitalSentinel CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Core simulation logic, shared by the main app and the test binary
add_library(orbital_core
    Spacecraft.cpp
    TelemetryMonitor.cpp
)
target_include_directories(orbital_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Main simulation executable
add_executable(orbital_sentinel main.cpp)
target_link_libraries(orbital_sentinel PRIVATE orbital_core)

# Test executable
enable_testing()
add_executable(telemetry_monitor_tests tests/test_telemetry_monitor.cpp)
target_link_libraries(telemetry_monitor_tests PRIVATE orbital_core)
add_test(NAME TelemetryMonitorTests COMMAND telemetry_monitor_tests)
