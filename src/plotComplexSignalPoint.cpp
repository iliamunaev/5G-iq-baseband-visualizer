#include <cstdio>
#include <cstdlib>
#include "iq.hpp"

namespace {
FILE* g_gnuplot = nullptr;

void close_gnuplot() {
    if (g_gnuplot) {
        pclose(g_gnuplot);
        g_gnuplot = nullptr;
    }
}

FILE* open_gnuplot() {
    static bool registered = false;
    if (!g_gnuplot) {
        g_gnuplot = popen("gnuplot -persist", "w");
    }
    if (g_gnuplot && !registered) {
        std::atexit(close_gnuplot);
        registered = true;
    }
    return g_gnuplot;
}
}

void plotComplexSignalPoint(const ComplexSignalPoint& s) {
    FILE* gp = open_gnuplot();
    if (!gp) {
        return;
    }

    static bool initialized = false;
    if (!initialized) {
        std::fprintf(gp, "set size square\n");
        std::fprintf(gp, "set xlabel 'I'\n");
        std::fprintf(gp, "set ylabel 'Q'\n");
        std::fprintf(gp, "set key off\n");
        std::fprintf(gp, "set xrange [-2:2]\n");
        std::fprintf(gp, "set yrange [-2:2]\n");
        initialized = true;
    }

    std::fprintf(gp, "plot '-' with points pointtype 7\n");
    std::fprintf(gp, "%f %f\n", s.i, s.q);
    std::fprintf(gp, "e\n");
    std::fflush(gp);
}