#include <iostream>
#include "iq.hpp"


// void plotComplexSignalPoint(const ComplexSignalPoint& s) {

// }

// int main(int argc, char** argv) {
int main() {

    Config config;
    
    while(true) {
        ComplexSignalPoint s = calculatePoint(config.amp, config.phase);

        std::cout << s.i << " " << s.q << std::endl;
        // plotComplexSignalPoint(s);
    }
    
    return 0;
}

