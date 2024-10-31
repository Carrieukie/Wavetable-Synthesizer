package com.karis.wavetablesynthesizer

import android.app.Application
import dagger.hilt.android.HiltAndroidApp

@HiltAndroidApp
class WavetableSynthesizerApplication : Application() {
    override fun onCreate() {
        super.onCreate()
        System.loadLibrary("wavetablesynthesizer")
    }
}