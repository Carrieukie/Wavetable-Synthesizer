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

        std::vector<float> mPulseTable;
        std::vector<float> mWhiteNoiseTable;
        std::vector<float> mPinkNoiseTable;
        std::vector<float> mTriangleSineHybridTable;
        std::vector<float> mHarmonicSeriesTable;
        std::vector<float> mSuperSawTable;
        std::vector<float> mBellTable;


        std::vector<float> sineWaveTable();
        std::vector<float> triangleWaveTable();
        std::vector<float> squareWaveTable();
        std::vector<float> sawToothTable();

        std::vector<float> pulseWaveTable(float dutyCycle = 0.5);
        std::vector<float> whiteNoiseTable();
        std::vector<float> pinkNoiseTable();
        std::vector<float> triangleSineHybridTable(float mix = 0.5);
        std::vector<float> harmonicSeriesTable(std::vector<float> harmonics);
        std::vector<float> superSawTable(int numVoices = 7, float detuneAmount = 0.1f);

    };
}
