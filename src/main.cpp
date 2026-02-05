#include <chrono>
#include <thread>
#include <vector>
#include "iq.hpp"

int main(void) {
    Config config;
    const int frame_size = 100;
    const int fps = 20;

    auto phase_step = phaseStepRadPerSample(config.freq, config.fs);

    while (true) {
        std::vector<ComplexSignalPoint> frame;
        frame.reserve(frame_size);

        for (int idx = 0; idx < frame_size; ++idx) {
            frame.push_back(calculatePoint(config.amp, config.phase));
            config.phase += phase_step;
        }

        plotComplexSignalFrame(frame.data(), frame.size());

        if (fps > 0) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(1000 / fps));
        }
    }

    return 0;
}
