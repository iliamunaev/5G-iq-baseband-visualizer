#include <gtest/gtest.h>
#include <cmath>
#include "iq.hpp"

TEST(IQ, UnitCircleAtAmp1Phase0) {
    const double amp = 1.0;
    const double phase = 0.0;

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, 1.0, 1e-12);
    EXPECT_NEAR(s.q, 0.0, 1e-12);
}

TEST(IQ, MagnitudeMatchesAmplitude) {
    const double amp = 2.5;
    const double phase = 1.234;

    auto s = calculatePoint(amp, phase);
    const double mag = std::sqrt(s.i*s.i + s.q*s.q);
    EXPECT_NEAR(mag, amp, 1e-9);
}
