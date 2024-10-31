#pragma once

#include  <vector>
#include "Wavetable.h"

namespace wavetablesynthesizer {
    class WavetableFactory {
    public:
        std::vector<float> getWaveTable(wavetablesynthesizer::WaveTable waveTable);

    private:
        std::vector<float> mSineTable;
        std::vector<float> mTriangleTable;
        std::vector<float> mSquareTable;
        std::vector<float> mSawtoothTable;

        std::vector<float> sineWaveTable();
        std::vector<float> triangleWaveTable();
        std::vector<float> squareWaveTable();
        std::vector<float> sawToothTable();
    };
}
