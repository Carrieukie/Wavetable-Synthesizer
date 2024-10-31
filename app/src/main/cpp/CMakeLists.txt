cmake_minimum_required(VERSION 3.22.1)
project("wavetablesynthesizer")

# Include directories
include_directories(
        include
)

# Add library
add_library(wavetablesynthesizer
        SHARED
        src/audio/OboeAudioPlayer.cpp

        src/wavetable/WavetableSynthesizer.cpp
        src/wavetable/WatableOscillator.cpp
        src/wavetable/WavetableFactory.cpp

        src/native/WavetableSynthesizerNativeLib.cpp
)

# Find Oboe package
set(OBOE_DIR "${CMAKE_SOURCE_DIR}/include")
find_package(oboe REQUIRED CONFIG PATHS ${OBOE_DIR})

# Find Android NDK libraries
find_library(log-lib log)
find_library(android-lib android)

# Link libraries
target_link_libraries(wavetablesynthesizer
        oboe::oboe
        android
        log
)
