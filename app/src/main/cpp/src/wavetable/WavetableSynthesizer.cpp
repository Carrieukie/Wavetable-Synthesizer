#include "utilities/Log.h"
#include <string>
#include "wavetable/WavetableSynthesizer.h"
#include "wavetable/WatableOscillator.h"
#include "memory"
#include "audio/OboeAudioPlayer.h"


namespace wavetablesynthesizer {

    WavetableSynthesizer::WavetableSynthesizer(): mOscillator{
        std::make_shared<WaveTableOscillator>(wavetableFactory.getWaveTable(currentWaveTable),sampleRate
    )},
              mPlayer(std::make_unique<OboeAudioPlayer>(mOscillator, sampleRate)) {

        LOGD("WavetableSynthesizer created with sample rate: %d", sampleRate);
        LOGD("OboeAudioPlayer initialized.");
    }

    WavetableSynthesizer::~WavetableSynthesizer() {
        // Log the destruction of the WavetableSynthesizer
        LOGD("WavetableSynthesizer destroyed.");
    }

    void WavetableSynthesizer::play() {
        std::lock_guard<std::mutex> lock(_mutex);
        const auto result = mPlayer->play();
        if (result == 0) {
            is_playing = true;
        } else {
            LOGD("Failed to play audio.");
        }
    }

    void WavetableSynthesizer::stop() {
        std::lock_guard<std::mutex> lock(_mutex);

        LOGD("wavetablesynthesizer stop");
        mPlayer->stop();
        is_playing = false;
    }

    bool WavetableSynthesizer::isPlaying() const {
        LOGD("wavetablesynthesizer isPlaying");
        return is_playing;
    }

    float dbToAmplitude(float db) {
        return std::pow(10.0f, db / 20.0f);
    }

    void WavetableSynthesizer::setVolume(float amplitude_in_db) {
        LOGD("wavetablesynthesizer setVolume: %f", amplitude_in_db);
        mOscillator->setVolume(dbToAmplitude(amplitude_in_db));
    }

    void WavetableSynthesizer::setFrequency(float frequency_in_hz) {
        LOGD("wavetablesynthesizer setFrequency: %f", frequency_in_hz);
        mOscillator->setFrequency(frequency_in_hz);
    }


    void WavetableSynthesizer::setWaveTable(WaveTable waveTable) {
        if (currentWaveTable != waveTable) {
            currentWaveTable = waveTable;
            mOscillator->setWaveTable(wavetableFactory.getWaveTable(waveTable));
        }
    }

}