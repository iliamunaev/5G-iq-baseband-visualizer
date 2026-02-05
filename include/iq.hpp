#include <cstddef>
#include <cstdint>
#include <cmath>

struct Config {
    uint32_t fs = 48000;     // Time discretization
    uint32_t freq = 1000;    // Phase slope
    double amp = 1.0;        // Power
    double phase = 1.0;      // Sync offset
};

struct ComplexSignalPoint {
    double i{};
    double q{};
};

// claculation
ComplexSignalPoint calculatePoint(double amp, double phase);
double phaseStepRadPerSample(uint32_t freq, uint32_t fs);

// plot
void plotComplexSignalPoint(const ComplexSignalPoint& s);
void plotComplexSignalFrame(const ComplexSignalPoint* points, std::size_t count);
void plotConstellation(const ComplexSignalPoint* points, std::size_t count);
