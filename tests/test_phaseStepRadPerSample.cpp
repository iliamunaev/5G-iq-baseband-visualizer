#include <gtest/gtest.h>
#include <cmath>
#include "iq.hpp"

TEST(IQ, PhaseStepZeroFrequencyIsZero) {
    const uint32_t freq = 0;
    const uint32_t fs = 48000;

    const double ps = phaseStepRadPerSample(freq, fs);
    // Zero frequency means no phase advance per sample.
    EXPECT_NEAR(ps, 0.0, 1e-12);
}

TEST(IQ, PhaseStepMatchesTwoPiAtNyquist) {
    const uint32_t freq = 1000;
    const uint32_t fs = 1000;

    // One cycle per sample gives 2π radians of phase advance.
    const double expected = 2.0 * std::acos(-1.0);
    const double ps = phaseStepRadPerSample(freq, fs);
    EXPECT_NEAR(ps, expected, 1e-12);
}

TEST(IQ, PhaseStepAtHalfSampleRateIsPi) {
    const uint32_t freq = 24000;
    const uint32_t fs = 48000;

    // Half the sample rate gives π radians per sample.
    const double expected = std::acos(-1.0);
    const double ps = phaseStepRadPerSample(freq, fs);
    EXPECT_NEAR(ps, expected, 1e-12);
}

TEST(IQ, PhaseStepMatchesFormula) {
    const uint32_t freq = 1000;
    const uint32_t fs = 48000;

    // General formula: 2π * freq / fs.
    const double expected =
        (2.0 * std::acos(-1.0) * static_cast<double>(freq)) /
        static_cast<double>(fs);
    const double ps = phaseStepRadPerSample(freq, fs);
    EXPECT_NEAR(ps, expected, 1e-12);
}

