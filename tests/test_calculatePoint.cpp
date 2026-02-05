#include <gtest/gtest.h>
#include <cmath>
#include "iq.hpp"

TEST(IQ, UnitCircleAtAmp1Phase0) {
    const double amp = 1.0;
    const double phase = 0.0;

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, 1.0, 1e-10);
    EXPECT_NEAR(s.q, 0.0, 1e-10);
}

TEST(IQ, MagnitudeMatchesAmplitude) {
    const double amp = 2.5;
    const double phase = 1.234;

    auto s = calculatePoint(amp, phase);
    const double mag = std::sqrt(s.i*s.i + s.q*s.q);
    EXPECT_NEAR(mag, amp, 1e-9);
}

TEST(IQ, PhasePiPointsToNegativeI) {
    const double amp = 1.0;
    const double phase = std::acos(-1.0);

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, -1.0, 1e-10);
    EXPECT_NEAR(s.q, 0.0, 1e-10);
}

TEST(IQ, PhaseTwoPiIsEquivalentToZero) {
    const double amp = 1.0;
    const double phase = 2.0 * std::acos(-1.0);

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, 1.0, 1e-10);
    EXPECT_NEAR(s.q, 0.0, 1e-10);
}

TEST(IQ, PhaseNegativeHalfPiPointsNegativeQ) {
    const double amp = 1.0;
    const double phase = -0.5 * std::acos(-1.0);

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, 0.0, 1e-10);
    EXPECT_NEAR(s.q, -1.0, 1e-10);
}

TEST(IQ, ZeroAmplitudeGivesOrigin) {
    const double amp = 0.0;
    const double phase = 2.123;

    auto s = calculatePoint(amp, phase);
    EXPECT_NEAR(s.i, 0.0, 1e-10);
    EXPECT_NEAR(s.q, 0.0, 1e-10);
}

TEST(IQ, PhaseMatchesAtan2ForUnitAmplitude) {
    const double amp = 1.0;
    const double phase = -1.234;

    auto s = calculatePoint(amp, phase);
    const double reconstructed = std::atan2(s.q, s.i);
    EXPECT_NEAR(reconstructed, phase, 1e-10);
}
