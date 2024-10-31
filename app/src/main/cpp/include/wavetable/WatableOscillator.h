#pragma once

#include "audio/AudioSource.h"
#include "WatableOscillator.h"
#include "cmath"
#include <vector>
namespace wavetablesynthesizer {

    class WaveTableOscillator: public AudioSource {
    public:
        WaveTableOscillator() = default;

        WaveTableOscillator(std::vector<float> waveTable, float sampleRate);

        float getSample() override;

        void onPlayBackStopped() override;

        virtual void setFrequency(float frequency_in_hz);

        virtual void setVolume(float amplitude_in_db);

        virtual void setWaveTable(const std::vector<float> &waveTable);

    private:
        float interpolateLinearly() const;
        void swapWaveTableIfNecessary();

        float index = 0.0f;
        std::atomic<float> indexIncrement{440.0f};
        std::vector<float> mWaveTable;
        float sampleRate{};
        std::atomic<float> volume{1.f};

        std::atomic<bool> swapWaveTable{false};
        std::vector<float> waveTableToSwap;
        std::atomic<bool> waveTableIsSwapping{false};
    };

}
