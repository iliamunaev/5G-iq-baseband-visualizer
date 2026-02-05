#include <cstdint>
#include <cmath>

struct Config {
    uint32_t fs = 48000;     // Time discretization
    uint32_t freq = 1000;    // Phase slope
    float amp = 1.0;        // Power
    float phase = 0.0;      // Sync offset
    float noise = 0.0;      // Channel impairment
};

struct ComplexSignalPoint {
    double i{};
    double q{};
};

ComplexSignalPoint calculatePoint(double amp, double phase);