
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
        auto triangleWaveTable = std::vector<float>(WAVE_TABLE_LENGTH, 0.f); // Initialize the triangle wave table to zero

        constexpr auto HARMONICS_COUNT = 13; // Define the number of harmonics to use in the generation

        // Sum the contributions of harmonics to create a triangle wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j / WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                triangleWaveTable[j] += 8.f / std::pow(M_PI, 2.f) * std::pow(-1.f, k) *
                                        std::pow(2 * k - 1, -2.f) * // Fourier series coefficients
                                        std::sin((2.f * k - 1.f) * phase); // Add harmonic contribution
            }
        }

        return triangleWaveTable; // Return the generated triangle wave table
    }

    // Function to generate a square wave table using Fourier series
    std::vector<float> generateSquareTable() {
        auto square_wave_table = std::vector<float>(WAVE_TABLE_LENGTH); // Initialize the square wave table
        constexpr auto HARMONICS_COUNT = 7; // Define the number of harmonics

        // Sum the contributions of harmonics to create a square wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j / WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                square_wave_table[j] += 4.f / M_PI * std::pow(2.f * k - 1.f, -1.f) *
                                        std::sin((2.f * k - 1) * phase); // Add harmonic contribution
            }
        }
        return square_wave_table; // Return the generated square wave table
    }

    // Function to generate a sawtooth wave table using Fourier series
    std::vector<float> generateSawtoothTable() {
        auto sawtooth_wave_table = std::vector<float>(WAVE_TABLE_LENGTH); // Initialize the sawtooth wave table
        constexpr auto HARMONICS_COUNT = 26; // Define the number of harmonics

        // Sum the contributions of harmonics to create a sawtooth wave
        for (auto k = 1; k <= HARMONICS_COUNT; ++k) {
            for (auto j = 0; j < WAVE_TABLE_LENGTH; ++j) {
                const auto phase = 2.f * M_PI * 1.f * j / WAVE_TABLE_LENGTH; // Calculate the phase for each sample
                sawtooth_wave_table[j] += 2.f / M_PI * std::pow(-1.f, k) * std::pow(k, -1.f) *
                                          std::sin(k * phase); // Add harmonic contribution
            }
        }
        return sawtooth_wave_table; // Return the generated sawtooth wave table
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
            default:
                return std::vector<float>(WAVE_TABLE_LENGTH, 0.0f); // Return a zeroed table if none matches
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
}
