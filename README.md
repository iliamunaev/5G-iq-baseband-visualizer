# 5G-iq-baseband-visualizer

This project builds practical intuition for Layer-1 signal processing by
generating and visualizing complex baseband I/Q data in discrete time.

I/Q data (In-phase / Quadrature data) is a concept used to represent complex signals.
It is used in modern wireless communication systems, including 5G.

## Usage
```bash
git clone https://github.com/iliamunaev/5G-iq-baseband-visualizer.git
cd 5G-iq-baseband-visualizer
make
./viz_iq
```
![I/Q visualization](imgs/demo.gif)

Core concepts:
- Complex baseband representation (I/Q)
- Frequency as phase slope (2π·f / fs)
- Discrete-time sampling and timing
- Frames as fixed-duration windows of samples
- Relationship between time domain, constellation, and signal geometry

## Config tuning
Defaults live in `include/iq.hpp` under the `Config` struct. Adjust them to see
how the signal changes:
- `fs` (sample rate): higher values make the phase advance per sample smaller.
- `freq` (tone frequency): higher values increase phase rotation speed.
- `amp` (amplitude): scales I/Q magnitude (bigger or smaller radius).
- `phase` (initial phase): shifts the starting point of the signal.

## Tests
```bash
cmake -S . -B build && cmake --build build
ctest --test-dir build --output-on-failure
```