package com.karis.wavetablesynthesizer.presentation.components

import androidx.lifecycle.ViewModel
import androidx.lifecycle.viewModelScope
import com.karis.wavetablesynthesizer.domain.WaveTable
import com.karis.wavetablesynthesizer.domain.WaveTable.BELL
import com.karis.wavetablesynthesizer.domain.WaveTable.HARMONIC_SERIES
import com.karis.wavetablesynthesizer.domain.WaveTable.PINK_NOISE
import com.karis.wavetablesynthesizer.domain.WaveTable.PULSE
import com.karis.wavetablesynthesizer.domain.WaveTable.SAW
import com.karis.wavetablesynthesizer.domain.WaveTable.SINE
import com.karis.wavetablesynthesizer.domain.WaveTable.SQUARE
import com.karis.wavetablesynthesizer.domain.WaveTable.SUPER_SAW
import com.karis.wavetablesynthesizer.domain.WaveTable.TRIANGLE
import com.karis.wavetablesynthesizer.domain.WaveTable.TRIANGLE_SINE_HYBRID
import com.karis.wavetablesynthesizer.domain.WaveTable.WHITE_NOISE
import com.karis.wavetablesynthesizer.domain.WavetableSynthesizer
import dagger.hilt.android.lifecycle.HiltViewModel
import kotlinx.coroutines.flow.MutableStateFlow
import kotlinx.coroutines.flow.SharingStarted
import kotlinx.coroutines.flow.onSubscription
import kotlinx.coroutines.flow.stateIn
import kotlinx.coroutines.launch
import kotlinx.coroutines.runBlocking
import timber.log.Timber
import javax.inject.Inject


@HiltViewModel
class MainActivityViewModel @Inject constructor(
    private val wavetableSynthesizer: WavetableSynthesizer
) : ViewModel() {

    private var _waveSynthesizerState = MutableStateFlow(WaveTableSynthesizerState())
    val waveSynthesizerState = _waveSynthesizerState
        .onSubscription {
            applyParameters()
        }
        .stateIn(
            scope = viewModelScope,
            started = SharingStarted.WhileSubscribed(),
            initialValue = WaveTableSynthesizerState()
        )

    fun onEvent(event: WaveTableSynthesizerAppEvents) {
        when (event) {
            is WaveTableSynthesizerAppEvents.UpdateUiState -> {
                updateState(event.reducer)
            }

            is WaveTableSynthesizerAppEvents.PlayClicked -> {
                playClicked()
            }
            is WaveTableSynthesizerAppEvents.SetFrequencySliderPosition -> {
                setFrequencySliderPosition(event.frequencySliderPosition)
            }
            is WaveTableSynthesizerAppEvents.SetVolume -> {
                setVolume(event.volumeInDb)
            }
            is WaveTableSynthesizerAppEvents.SetWavetable -> {
                setWaveTable(event.newWavetable)
            }
        }
    }

    private fun setFrequencySliderPosition(frequencySliderPosition: Float) {
        updateState { copy(frequency = frequencySliderPosition) }
        viewModelScope.launch {
            wavetableSynthesizer.setFrequency(frequencySliderPosition)
        }
    }

    private fun setVolume(volumeInDb: Float) {
        updateState { copy(amplitude = volumeInDb) }
        viewModelScope.launch {
            wavetableSynthesizer.setVolume(volumeInDb)
        }
    }

    private fun setWaveTable(newWavetable: WaveTable) {
        updateState { copy(waveTable = newWavetable) }
        viewModelScope.launch {
            wavetableSynthesizer.setWavetable(newWavetable)
        }
    }

    private fun playClicked() {
        Timber.d("playClicked")
        viewModelScope.launch {
            if (wavetableSynthesizer.isPlaying()) {
                wavetableSynthesizer.stop()
            } else {
                wavetableSynthesizer.play()
            }
            updateState { copy(isPlaying = runBlocking { wavetableSynthesizer.isPlaying() }) }
        }
    }

    private fun applyParameters() {
        viewModelScope.launch {
            wavetableSynthesizer.setFrequency(waveSynthesizerState.value.frequency)
            wavetableSynthesizer.setVolume(waveSynthesizerState.value.amplitude)
            wavetableSynthesizer.setWavetable(waveSynthesizerState.value.waveTable)
        }
    }

    private fun updateState(reducer: WaveTableSynthesizerState.() -> WaveTableSynthesizerState) {
        _waveSynthesizerState.value = _waveSynthesizerState.value.reducer()
    }

    companion object {
        private const val TAG = "MainActivityViewModel"
        private const val MINIMUM_VALUE = 0.001f

        val frequencyRange = 40f..3000f
        val amplitudeRange = (-60f)..20f



    }
}

data class WaveTableSynthesizerState(
    val waveTable: WaveTable = WaveTable.SINE,
    val frequency: Float = 440f,
    val amplitude: Float = 1f,
    val isPlaying: Boolean = false,
    val wavetables:List<WaveTable> = listOf(
        SINE,
        TRIANGLE,
        SQUARE,
        SAW,
        PULSE,
        WHITE_NOISE,
        PINK_NOISE,
        TRIANGLE_SINE_HYBRID,
        HARMONIC_SERIES,
        SUPER_SAW,
        BELL
    )
)