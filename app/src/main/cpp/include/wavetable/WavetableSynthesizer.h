#pragma once

#include "audio/AudioSource.h"
#include "wavetable/Wavetable.h"
#include "audio/AudioPlayer.h"
#include <cmath>
#include "utilities/Log.h"
#include "audio/OboeAudioPlayer.h"
#include "wavetable/WatableOscillator.h"
#include "wavetable/WatableFactory.h"

namespace wavetablesynthesizer {

    class AudioPlayer;

    constexpr auto sampleRate = 48000;

    class WavetableSynthesizer {
    public:
        WavetableSynthesizer();

        ~WavetableSynthesizer();

        void play();

        void stop();

        bool isPlaying() const;

        void setFrequency(float frequency_in_hz);

        void setVolume(float amplitude_in_db);

        void setWaveTable(WaveTable waveTable);

    private:
        std::atomic<bool> is_playing = false;
        std::mutex _mutex;

        WavetableFactory wavetableFactory;
        WaveTable currentWaveTable{WaveTable::Sine};

        std::shared_ptr<WaveTableOscillator> mOscillator;
        std::unique_ptr<AudioPlayer> mPlayer;
    };
}
