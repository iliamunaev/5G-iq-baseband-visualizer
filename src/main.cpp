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

ComplexSignalPoint calculateComplexSignalPoint(const Config& config) {

    double i = config.amp * std::cos(config.phase);
    double q = config.amp * std::sin(config.phase);
    
    return ComplexSignalPoint{i, q};
}

void plotComplexSignalPoint(const ComplexSignalPoint& s) {

}

int main(int argc, char** argv) {

    Config config;
    
    while(true) {
        ComplexSignalPoint s = calculateComplexSignalPoint(config);
        plotComplexSignalPoint(s);
    }
    
    return 0;
}

