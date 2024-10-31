package com.karis.wavetablesynthesizer.presentation.components

import com.karis.wavetablesynthesizer.domain.WaveTable

sealed interface WaveTableSynthesizerAppEvents {
    data class UpdateUiState(
        val reducer: WaveTableSynthesizerState.() -> WaveTableSynthesizerState
    ) : WaveTableSynthesizerAppEvents

    data class SetFrequencySliderPosition(
        val frequencySliderPosition: Float
    ) : WaveTableSynthesizerAppEvents

    data class SetVolume(
        val volumeInDb: Float
    ) : WaveTableSynthesizerAppEvents

    data class SetWavetable(
        val newWavetable: WaveTable
    ) : WaveTableSynthesizerAppEvents

    data object PlayClicked : WaveTableSynthesizerAppEvents

}