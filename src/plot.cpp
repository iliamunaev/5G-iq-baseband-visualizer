#include <cstdio>
#include <cstdlib>
#include "iq.hpp"

static FILE* g_gnuplot = nullptr;
static constexpr double kAxisMin = -2.0;
static constexpr double kAxisMax = 2.0;

static void close_gnuplot() {
    if (g_gnuplot) {
        pclose(g_gnuplot);
        g_gnuplot = nullptr;
    }
}

static FILE* open_gnuplot() {
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

static bool has_points(const ComplexSignalPoint* points, std::size_t count) {
    return points && count > 0;
}

static void init_3d_view(FILE* gp) {
    std::fprintf(gp, "set key off\n");
    std::fprintf(gp, "set grid\n");
    std::fprintf(gp, "set xlabel 'Sample'\n");
    std::fprintf(gp, "set ylabel 'I'\n");
    std::fprintf(gp, "set zlabel 'Q'\n");
    std::fprintf(gp, "set view 70, 30, 1, 1\n");
    std::fprintf(gp, "set yrange [%f:%f]\n", kAxisMin, kAxisMax);
    std::fprintf(gp, "set zrange [%f:%f]\n", kAxisMin, kAxisMax);
}

static void init_constellation_view(FILE* gp) {
    std::fprintf(gp, "set key off\n");
    std::fprintf(gp, "set grid\n");
    std::fprintf(gp, "set size square\n");
    std::fprintf(gp, "set xlabel 'I'\n");
    std::fprintf(gp, "set ylabel 'Q'\n");
    std::fprintf(gp, "set xrange [%f:%f]\n", kAxisMin, kAxisMax);
    std::fprintf(gp, "set yrange [%f:%f]\n", kAxisMin, kAxisMax);
}

static void plot_helix(FILE* gp,
                       const ComplexSignalPoint* points,
                       std::size_t count,
                       unsigned long long sample_offset) {
    std::fprintf(gp, "splot '-' using 1:2:3 with lines\n");
    for (std::size_t idx = 0; idx < count; ++idx) {
        const unsigned long long x = sample_offset + idx;
        std::fprintf(gp, "%llu %f %f\n", x, points[idx].i, points[idx].q);
    }
    std::fprintf(gp, "e\n");
}

static void plot_iq_scatter(FILE* gp, const ComplexSignalPoint* points, std::size_t count) {
    std::fprintf(gp, "set term wxt 1\n");
    std::fprintf(gp, "plot '-' using 1:2 with points pointtype 7 notitle\n");
    for (std::size_t idx = 0; idx < count; ++idx) {
        std::fprintf(gp, "%f %f\n", points[idx].i, points[idx].q);
    }
    std::fprintf(gp, "e\n");
}

void plotComplexSignalPoint(const ComplexSignalPoint& s) {
    plotComplexSignalFrame(&s, 1);
}

void plotComplexSignalFrame(const ComplexSignalPoint* points, std::size_t count) {
    if (!has_points(points, count)) {
        return;
    }

    FILE* gp = open_gnuplot();
    if (!gp) {
        return;
    }

    static bool initialized = false;
    if (!initialized) {
        init_3d_view(gp);
        initialized = true;
    }

    static unsigned long long sample_offset = 0;
    plot_helix(gp, points, count, sample_offset);
    std::fflush(gp);
    sample_offset += static_cast<unsigned long long>(count);
}

void plotConstellation(const ComplexSignalPoint* points, std::size_t count) {
    if (!has_points(points, count)) {
        return;
    }

    FILE* gp = open_gnuplot();
    if (!gp) {
        return;
    }

    static bool initialized = false;
    if (!initialized) {
        init_constellation_view(gp);
        initialized = true;
    }

    plot_iq_scatter(gp, points, count);
    std::fflush(gp);
}