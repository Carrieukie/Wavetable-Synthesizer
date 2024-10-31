#pragma once

#include "audio/AudioPlayer.h"
#include "AudioSource.h"
#include <oboe/Oboe.h>
#include <oboe/Definitions.h>
#include <cstdint>
#include <memory> // Don't forget to include memory for std::shared_ptr

namespace wavetablesynthesizer {

    class OboeAudioPlayer : public oboe::AudioStreamCallback,
                            public AudioPlayer {
    public:
        static constexpr auto channelCount = oboe::ChannelCount::Mono;

        OboeAudioPlayer(std::shared_ptr<AudioSource> source, int sampleRate);
        ~OboeAudioPlayer() override;

        int32_t play() override;
        void stop() override;

        oboe::DataCallbackResult onAudioReady(
                oboe::AudioStream *audioStream,
                void *audioData,
                int32_t framesCount) override;

    private:
        std::shared_ptr<AudioSource> mSource;
        std::shared_ptr<oboe::AudioStream> mStream;
        int mSampleRate;
    };
}
