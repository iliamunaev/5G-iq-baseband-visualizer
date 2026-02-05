#include "iq.hpp"

int main() {

    Config config;
    
    while(true) {
        ComplexSignalPoint s = calculatePoint(config.amp, config.phase);
        plotComplexSignalPoint(s);
    }
    
    return 0;
}
