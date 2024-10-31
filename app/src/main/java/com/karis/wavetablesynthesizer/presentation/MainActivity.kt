package com.karis.wavetablesynthesizer.presentation

import android.os.Bundle
import androidx.activity.ComponentActivity
import androidx.activity.compose.setContent
import com.karis.wavetablesynthesizer.presentation.components.WaveTableSynthesizerApp
import com.karis.wavetablesynthesizer.presentation.theme.WavetableSynthesizerTheme
import dagger.hilt.android.AndroidEntryPoint

@AndroidEntryPoint
class MainActivity : ComponentActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContent {
            WavetableSynthesizerTheme {
                WaveTableSynthesizerApp()
            }
        }
    }
}