#include "iq.hpp"

ComplexSignalPoint calculatePoint(double amp, double phase) {
    double i = amp * std::cos(phase);
    double q = amp * std::sin(phase);

    return ComplexSignalPoint{i, q};
}
