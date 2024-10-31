#include "audio/OboeAudioPlayer.h"
#include "audio/AudioSource.h"

namespace wavetablesynthesizer {

    OboeAudioPlayer::OboeAudioPlayer(std::shared_ptr<AudioSource> source, int sampleRate)
            : mSource(std::move(source)), mSampleRate(sampleRate) {
    }

    OboeAudioPlayer::~OboeAudioPlayer() {
        if (mStream) {
            mStream.reset(); // Or explicitly delete if needed
        }
    }

    int32_t OboeAudioPlayer::play() {
        oboe::AudioStreamBuilder builder;
        const auto result = builder.setPerformanceMode(oboe::PerformanceMode::LowLatency)
                ->setDirection(oboe::Direction::Output)
                ->setSampleRate(mSampleRate)
                ->setSharingMode(oboe::SharingMode::Exclusive)
                ->setFormat(oboe::AudioFormat::Float)
                ->setChannelCount(channelCount)
                ->setCallback(this)
                ->setSampleRateConversionQuality(oboe::SampleRateConversionQuality::Best)
                ->openStream(mStream);

        if (result != oboe::Result::OK) {
            return static_cast<int32_t>(-1);
        }

        const auto playResult = mStream->requestStart();
        return static_cast<int32_t>(playResult);
    }

    void OboeAudioPlayer::stop() {
        if (mStream) {
            mStream->requestStop();
            mStream->close();
            mStream.reset();
        }
        mSource->onPlayBackStopped();
    }

    oboe::DataCallbackResult OboeAudioPlayer::onAudioReady(
            oboe::AudioStream *audioStream,
            void *audioData,
            int32_t framesCount) {

        auto *floatData = reinterpret_cast<float *>(audioData);

        for (int frame = 0; frame < framesCount; ++frame) {
            float sample = mSource->getSample(); // Get sample once per frame

            for (int channel = 0; channel < channelCount; ++channel) {
                floatData[frame * channelCount + channel] = sample;
            }
        }

        return oboe::DataCallbackResult::Continue;
    }

}
