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
    };

    @StringRes
    abstract fun toResourceString(): Int
}