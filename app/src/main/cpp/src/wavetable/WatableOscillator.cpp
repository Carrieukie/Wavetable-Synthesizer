#include "audio/AudioSource.h"       // Include header for audio source management
#include "cmath"                     // Include for mathematical functions like fmod
#include "wavetable/WatableOscillator.h"
#include <vector>                   // Include for using std::vector

namespace wavetablesynthesizer {

    // Constructor for WaveTableOscillator
    // Takes a vector of floats representing the wave table and a sample rate
    WaveTableOscillator::WaveTableOscillator(std::vector<float> waveTable, float sampleRate) :
            mWaveTable(std::move(waveTable)), // Initialize the wave table using the passed vector
            sampleRate(sampleRate) {          // Set the sample rate
    }

    // Generates the next sample of audio
    float WaveTableOscillator::getSample() {
        swapWaveTableIfNecessary(); // Check and swap wave tables if necessary

        // Wrap the index to ensure it stays within bounds of the wave table size
        index = std::fmod(index, static_cast<float>(mWaveTable.size()));

        // Interpolate the sample based on the current index and increment
        const auto sample = interpolateLinearly();
        index += indexIncrement; // Update the index for the next sample generation
        return volume * sample;  // Return the sample multiplied by the current volume
    }

    // Checks if a wave table swap is needed and performs it
    void WaveTableOscillator::swapWaveTableIfNecessary() {
        waveTableIsSwapping.store(true, std::memory_order_release); // Mark that swapping is in progress

        // If a swap is requested, perform the swap
        if (swapWaveTable.load(std::memory_order_acquire)) {
            std::swap(mWaveTable, waveTableToSwap); // Swap current wave table with the new one
            swapWaveTable.store(false, std::memory_order_relaxed); // Reset swap request
        }

        waveTableIsSwapping.store(false, std::memory_order_release); // Mark that swapping is complete
    }

    // Set the frequency of the oscillator
    void WaveTableOscillator::setFrequency(float frequency) {
        // Calculate index increment based on frequency and sample rate
        indexIncrement = frequency * static_cast<float>(mWaveTable.size()) /
                         static_cast<float>(sampleRate);
    }

    // Reset the index when playback stops
    void WaveTableOscillator::onPlayBackStopped() {
        index = 0.f; // Reset index to zero
    }

    // Interpolates the sample value between two points in the wave table
    float WaveTableOscillator::interpolateLinearly() const {
        // Get the truncated index for the current sample
        const auto truncatedIndex =
                static_cast<typename decltype(mWaveTable)::size_type>(index);
        const auto nextIndex = (truncatedIndex + 1u) % mWaveTable.size(); // Get the next index (wrap around)
        const auto nextIndexWeight = index - static_cast<float>(truncatedIndex); // Calculate weight for interpolation

        // Perform linear interpolation between current and next sample
        return mWaveTable[nextIndex] * nextIndexWeight +
               (1.f - nextIndexWeight) * mWaveTable[truncatedIndex];
    }

    // Set the volume of the oscillator
    void WaveTableOscillator::setVolume(float newAmplitude) {
        volume.store(newAmplitude); // Update volume with new amplitude
    }

    // Swap the current wave table with a new one
    void WaveTableOscillator::setWaveTable(const std::vector<float> &waveTable)  {
        // Wait for the previous swap to complete if the oscillator is active
        swapWaveTable.store(false, std::memory_order_release); // Reset swap flag
        while (waveTableIsSwapping.load(std::memory_order_acquire)) {
            // Busy-wait until swapping is complete
        }
        waveTableToSwap = waveTable; // Set the new wave table to swap with
        swapWaveTable.store(true, std::memory_order_release); // Indicate a swap is requested
    }
}
