#include <numbers>

#include "iq.hpp"


double phaseStepRadPerSample(uint32_t freq, uint32_t fs) {
    const double phase_step =
        (2.0 * std::numbers::pi * static_cast<double>(freq)) /
        static_cast<double>(fs);
        
        return phase_step;
    }


ComplexSignalPoint calculatePoint(double amp, double phase) {
    double i = amp * std::cos(phase);
    double q = amp * std::sin(phase);

    return ComplexSignalPoint{i, q};
}
