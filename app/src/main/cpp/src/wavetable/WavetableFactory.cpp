
#include "wavetable/WatableFactory.h"
#include <cmath>

namespace {
    const auto WAVE_TABLE_LENGTH = 256; // Define the length of the wave tables

    // Template function to generate a wave table only if it is currently empty
    template<typename F>
    std::vector<float> generateWaveTableOnce(std::vector<float> &wave_table, F &&generator) {
        // If the wave table is empty, generate it using the provided generator function
        if (wave_table.empty()) {
            wave_table = generator();
        }
        return wave_table; // Return the generated or existing wave table
    }

    // Function to generate a sine wave table
    std::vector<float> generateSineTable() {
        auto sine_wave_table = std::vector<float>(WAVE_TABLE_LENGTH);
        // Fill the sine wave table using the sine function
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            sine_wave_table[i] = std::sin(2 * M_PI * static_cast<float>(i) / WAVE_TABLE_LENGTH);
        }
        return sine_wave_table; // Return the generated sine wave table
    }

    // Function to generate a triangle wave table using Fourier series
    std::vector<float> generateTriangleTable() {
        auto triangleWaveTable = std::vector<float>(WAVE_TABLE_LENGTH,
                                                    0.f); // Initialize the triangle wave table to zero

        constexpr auto HARMONICS_COUNT = 13; // Define the number of harmonics to use in the generation

        // Sum the contributions of harmonics to create a triangle wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j /
                                   WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                triangleWaveTable[j] += 8.f / std::pow(M_PI, 2.f) * std::pow(-1.f, k) *
                                        std::pow(2 * k - 1, -2.f) * // Fourier series coefficients
                                        std::sin((2.f * k - 1.f) *
                                                 phase); // Add harmonic contribution
            }
        }

        return triangleWaveTable; // Return the generated triangle wave table
    }

    // Function to generate a square wave table using Fourier series
    std::vector<float> generateSquareTable() {
        auto square_wave_table = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the square wave table
        constexpr auto HARMONICS_COUNT = 7; // Define the number of harmonics

        // Sum the contributions of harmonics to create a square wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j /
                                   WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                square_wave_table[j] += 4.f / M_PI * std::pow(2.f * k - 1.f, -1.f) *
                                        std::sin(
                                                (2.f * k - 1) * phase); // Add harmonic contribution
            }
        }
        return square_wave_table; // Return the generated square wave table
    }

    // Function to generate a sawtooth wave table using Fourier series
    std::vector<float> generateSawtoothTable() {
        auto sawtooth_wave_table = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the sawtooth wave table
        constexpr auto HARMONICS_COUNT = 26; // Define the number of harmonics

        // Sum the contributions of harmonics to create a sawtooth wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j /
                                   WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                sawtooth_wave_table[j] += 2.f / M_PI * std::pow(-1.f, k) * std::pow(k, -1.f) *
                                          std::sin(k * phase); // Add harmonic contribution
            }
        }
        return sawtooth_wave_table; // Return the generated sawtooth wave table
    }


    std::vector<float> generatePulseTable(float dutyCycle = 0.5) {
        auto pulseWaveTable = std::vector<float>(WAVE_TABLE_LENGTH,
                                                 0.f); // Initialize the pulse wave table to zero

        // Fill the pulse wave table based on the duty cycle
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            pulseWaveTable[i] = i < WAVE_TABLE_LENGTH * dutyCycle ? 1.f : -1.f;
        }

        return pulseWaveTable; // Return the generated pulse wave table
    }

    std::vector<float> generateWhiteNoiseTable() {
        auto whiteNoiseTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the white noise table

        // Fill the white noise table with random values between -1 and 1
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            whiteNoiseTable[i] = static_cast<float>(rand()) / RAND_MAX * 2.f - 1.f;
        }

        return whiteNoiseTable; // Return the generated white noise table
    }

    std::vector<float> generatePinkNoiseTable() {
        auto pinkNoiseTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the pink noise table

        // Fill the pink noise table with random values between -1 and 1
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            pinkNoiseTable[i] = static_cast<float>(rand()) / RAND_MAX * 2.f - 1.f;
        }

        return pinkNoiseTable; // Return the generated pink noise table
    }

    std::vector<float> generateTriangleSineHybridTable(float mix = 0.5) {
        auto triangleSineHybridTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the hybrid table

        // Fill the hybrid table with a mix of triangle and sine waves
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            triangleSineHybridTable[i] =
                    mix * std::sin(2 * M_PI * static_cast<float>(i) / WAVE_TABLE_LENGTH) +
                    (1 - mix) * (i < WAVE_TABLE_LENGTH / 2 ? 1.f : -1.f);
        }

        return triangleSineHybridTable; // Return the generated hybrid table
    }

    std::vector<float> generateHarmonicSeriesTable(std::vector<float> harmonics) {
        auto harmonicSeriesTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the harmonic series table

        // Fill the harmonic series table with the sum of harmonics
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            for (auto harmonic: harmonics) {
                harmonicSeriesTable[i] += std::sin(
                        2 * M_PI * static_cast<float>(i) / WAVE_TABLE_LENGTH * harmonic);
            }
        }

        return harmonicSeriesTable; // Return the generated harmonic series table
    }

    std::vector<float> generateSuperSawTable(int numVoices = 7, float detuneAmount = 0.1f) {
        auto superSawTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the super saw table

        // Fill the super saw table with the sum of detuned sawtooth waves
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            for (auto voice = 0; voice < numVoices; voice++) {
                superSawTable[i] += std::sin(
                        2 * M_PI * static_cast<float>(i) / WAVE_TABLE_LENGTH * (voice + 1) *
                        (1 + detuneAmount * (voice - numVoices / 2)));
            }
        }

        return superSawTable; // Return the generated super saw table
    }

    std::vector<float> generateBellWaveTable(float modFrequency, float modIndex) {
        auto bellWaveTable = std::vector<float>(
                WAVE_TABLE_LENGTH); // Initialize the bell wave table

        // Fill the bell wave table with a modulated sine wave
        for (auto i = 0; i < WAVE_TABLE_LENGTH; i++) {
            bellWaveTable[i] = std::sin(2 * M_PI * static_cast<float>(i) / WAVE_TABLE_LENGTH) *
                               std::sin(2 * M_PI * modFrequency * static_cast<float>(i) /
                                        WAVE_TABLE_LENGTH * modIndex);
        }

        return bellWaveTable; // Return the generated bell wave table
    }


}

namespace wavetablesynthesizer {

    // Factory method to get the desired wave table based on the enum value
    std::vector<float> WavetableFactory::getWaveTable(wavetablesynthesizer::WaveTable waveTable) {
        switch (waveTable) {
            case WaveTable::Sine:
                return sineWaveTable(); // Get sine wave table
            case WaveTable::Triangle:
                return triangleWaveTable(); // Get triangle wave table
            case WaveTable::Square:
                return squareWaveTable(); // Get square wave table
            case WaveTable::Sawtooth:
                return sawToothTable(); // Get sawtooth wave table
            case WaveTable::Pulse:
                return pulseWaveTable(); // Get pulse wave table
            case WaveTable::WhiteNoise:
                return whiteNoiseTable(); // Get white noise table
            case WaveTable::PinkNoise:
                return pinkNoiseTable(); // Get pink noise table
            case WaveTable::TriangleSineHybrid:
                return triangleSineHybridTable(); // Get triangle-sine hybrid table
            case WaveTable::HarmonicSeries:
                return harmonicSeriesTable({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}); // Get harmonic series table
            case WaveTable::SuperSaw:
                return superSawTable(); // Get super saw wave table
            case WaveTable::Bell:
                return generateWaveTableOnce(mBellTable, []() { return generateBellWaveTable(2, 3); });

            default:
                return std::vector<float>(WAVE_TABLE_LENGTH,
                                          0.0f); // Return a zeroed table if none matches
        }
    }

    // Method to get the sine wave table, utilizing the generateWaveTableOnce function
    std::vector<float> WavetableFactory::sineWaveTable() {
        return generateWaveTableOnce(mSineTable, generateSineTable);
    }

    // Method to get the triangle wave table
    std::vector<float> WavetableFactory::triangleWaveTable() {
        return generateWaveTableOnce(mTriangleTable, generateTriangleTable);
    }

    // Method to get the square wave table
    std::vector<float> WavetableFactory::squareWaveTable() {
        return generateWaveTableOnce(mSquareTable, generateSquareTable);
    }

    // Method to get the sawtooth wave table
    std::vector<float> WavetableFactory::sawToothTable() {
        return generateWaveTableOnce(mSawtoothTable, generateSawtoothTable);
    }


    std::vector<float> WavetableFactory::pulseWaveTable(float dutyCycle) {
        return generateWaveTableOnce(mPulseTable, [dutyCycle]() { return generatePulseTable(dutyCycle); });
    }

    std::vector<float> WavetableFactory::whiteNoiseTable() {
        return generateWaveTableOnce(mWhiteNoiseTable, generateWhiteNoiseTable);
    }

    std::vector<float> WavetableFactory::pinkNoiseTable() {
        return generateWaveTableOnce(mPinkNoiseTable, generatePinkNoiseTable);
    }

    std::vector<float> WavetableFactory::triangleSineHybridTable(float mix) {
        return generateWaveTableOnce(mTriangleSineHybridTable, [mix]() { return generateTriangleSineHybridTable(mix); });
    }

    std::vector<float> WavetableFactory::harmonicSeriesTable(std::vector<float> harmonics) {
        return generateWaveTableOnce(mHarmonicSeriesTable, [harmonics]() { return generateHarmonicSeriesTable(harmonics); });
    }

    std::vector<float> WavetableFactory::superSawTable(int numVoices, float detuneAmount) {
        return generateWaveTableOnce(mSuperSawTable, [numVoices, detuneAmount]() { return generateSuperSawTable(numVoices, detuneAmount); });
    }


}
