#pragma once

namespace wavetablesynthesizer {
    class AudioSource {
    public:
        virtual ~AudioSource() = default;

        virtual float getSample() = 0;

        virtual void onPlayBackStopped() = 0;
    };
}
