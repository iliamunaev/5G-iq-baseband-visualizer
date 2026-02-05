#include <chrono>
#include <thread>
#include <vector>
#include "iq.hpp"

int n = 100;
int rate = 20;

int main() {
    Config config;

    auto phase_step = phaseStepRadPerSample(config.freq, config.fs);

    while (true) {
        std::vector<ComplexSignalPoint> frame;
        frame.reserve(static_cast<std::size_t>(n));

        for (int idx = 0; idx < n; ++idx) {
            frame.push_back(calculatePoint(config.amp, config.phase));
            config.phase += static_cast<float>(phase_step);
        }

        plotComplexSignalFrame(frame.data(), frame.size());

        if (rate > 0) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1000 / rate));
        }
    }

    return 0;
}
