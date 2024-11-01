package com.karis.wavetablesynthesizer.domain

import androidx.annotation.StringRes
import com.karis.wavetablesynthesizer.R

enum class WaveTable {
    SINE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.sine
        }
    },

    TRIANGLE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.triangle
        }
    },

    SQUARE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.square
        }
    },

    SAW {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.sawtooth
        }
    },

    PULSE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.pulse
        }
    },

    WHITE_NOISE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.white_noise
        }
    },

    PINK_NOISE {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.pink_noise
        }
    },

    TRIANGLE_SINE_HYBRID {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.triangle_sine_hybrid
        }
    },

    HARMONIC_SERIES {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.harmonic_series
        }
    },

    SUPER_SAW {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.super_saw
        }
    },

    BELL {
        @StringRes
        override fun toResourceString(): Int {
            return R.string.bell
        }
    };



    @StringRes
    abstract fun toResourceString(): Int
}