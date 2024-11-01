package com.karis.wavetablesynthesizer.presentation.components

import androidx.compose.foundation.layout.Arrangement
import androidx.compose.foundation.layout.Box
import androidx.compose.foundation.layout.Column
import androidx.compose.foundation.layout.PaddingValues
import androidx.compose.foundation.layout.Row
import androidx.compose.foundation.layout.aspectRatio
import androidx.compose.foundation.layout.fillMaxSize
import androidx.compose.foundation.layout.fillMaxWidth
import androidx.compose.foundation.layout.height
import androidx.compose.foundation.layout.padding
import androidx.compose.foundation.lazy.grid.GridCells
import androidx.compose.foundation.lazy.grid.LazyVerticalGrid
import androidx.compose.foundation.lazy.grid.items
import androidx.compose.foundation.shape.RoundedCornerShape
import androidx.compose.material3.Button
import androidx.compose.material3.Card
import androidx.compose.material3.CardDefaults
import androidx.compose.material3.ExperimentalMaterial3Api
import androidx.compose.material3.MaterialTheme
import androidx.compose.material3.Scaffold
import androidx.compose.material3.Slider
import androidx.compose.material3.Surface
import androidx.compose.material3.Text
import androidx.compose.material3.TopAppBar
import androidx.compose.material3.TopAppBarDefaults
import androidx.compose.runtime.Composable
import androidx.compose.runtime.collectAsState
import androidx.compose.ui.Alignment
import androidx.compose.ui.Modifier
import androidx.compose.ui.res.stringResource
import androidx.compose.ui.text.font.FontWeight
import androidx.compose.ui.text.style.TextAlign
import androidx.compose.ui.unit.dp
import androidx.hilt.navigation.compose.hiltViewModel

@OptIn(ExperimentalMaterial3Api::class)
@Composable
fun WaveTableSynthesizerApp(
    mainActivityViewModel: MainActivityViewModel = hiltViewModel()
) {
    val waveTableSynthesizerState = mainActivityViewModel.waveSynthesizerState.collectAsState()
    val onEvent = mainActivityViewModel::onEvent

    Scaffold(
        topBar = {
            TopAppBar(
                title = {
                    Text(
                        text = "WaveTable Synthesizer",
                        style = MaterialTheme.typography.titleMedium.copy(
                            color = MaterialTheme.colorScheme.onPrimary
                        )
                    )
                },
                colors = TopAppBarDefaults.topAppBarColors(
                    containerColor = MaterialTheme.colorScheme.primary
                )
            )
        },
        bottomBar = {
            Column {
                Row {
                    // Frequency controls
                    Column(
                        modifier = Modifier
                            .weight(1f)
                            .fillMaxWidth()
                            .padding(vertical = 16.dp),
                        verticalArrangement = Arrangement.SpaceEvenly,
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        Text(text = "Frequency", style = MaterialTheme.typography.titleMedium)
                        Text(text = "${waveTableSynthesizerState.value.frequency} Hz")
                        Slider(
                            modifier = Modifier.fillMaxWidth(),
                            value = waveTableSynthesizerState.value.frequency,
                            onValueChange = {
                                onEvent(WaveTableSynthesizerAppEvents.SetFrequencySliderPosition(it))
                            },
                            valueRange = MainActivityViewModel.frequencyRange
                        )
                    }

                    // Amplitude controls
                    Column(
                        modifier = Modifier
                            .weight(1f)
                            .fillMaxWidth()
                            .padding(vertical = 16.dp),
                        verticalArrangement = Arrangement.SpaceEvenly,
                        horizontalAlignment = Alignment.CenterHorizontally
                    ) {
                        Text(text = "Amplitude", style = MaterialTheme.typography.titleMedium)
                        Text(text = "${waveTableSynthesizerState.value.amplitude} dB")
                        Slider(
                            modifier = Modifier.fillMaxWidth(),
                            value = waveTableSynthesizerState.value.amplitude,
                            onValueChange = {
                                onEvent(WaveTableSynthesizerAppEvents.SetVolume(it))
                            },
                            valueRange = MainActivityViewModel.amplitudeRange
                        )
                        Text(
                            text = "(No difference in past 20 dB)",
                            style = MaterialTheme.typography.labelSmall
                        )
                    }
                }


                Button(
                    modifier = Modifier
                        .padding(16.dp)
                        .height(58.dp)
                        .fillMaxWidth(),
                    onClick = {
                        onEvent(WaveTableSynthesizerAppEvents.PlayClicked)
                    },
                    shape = RoundedCornerShape(8.dp)
                ) {
                    Text(text = if (waveTableSynthesizerState.value.isPlaying) "Stop" else "Play")
                }
            }
        }
    ) { padding ->
        Surface(
            modifier = Modifier
                .padding(padding)
                .fillMaxSize(),
            color = MaterialTheme.colorScheme.background
        ) {
            Column {
                Text(
                    text = "Select a WaveTable",
                    style = MaterialTheme.typography.titleMedium.copy(
                        fontWeight = FontWeight.SemiBold
                    ),
                    modifier = Modifier.padding(16.dp)
                )
                LazyVerticalGrid(
                    columns = GridCells.Fixed(2),
                    modifier = Modifier
                        .fillMaxSize()
                        .padding(16.dp),
                    contentPadding = PaddingValues(8.dp)
                ) {
                    // WaveTable grid items
                    items(waveTableSynthesizerState.value.wavetables) { waveTable ->
                        val isSelected = waveTable == waveTableSynthesizerState.value.waveTable

                        // Define colors and font weight based on selection
                        val containerColor = if (isSelected) {
                            MaterialTheme.colorScheme.primary
                        } else {
                            MaterialTheme.colorScheme.primaryContainer
                        }

                        val fontWeight = if (isSelected) {
                            FontWeight.SemiBold
                        } else {
                            MaterialTheme.typography.bodyMedium.fontWeight
                        }

                        Card(
                            modifier = Modifier
                                .padding(8.dp)
                                .aspectRatio(1.8f)
                                .fillMaxWidth(0.45f),
                            onClick = { onEvent(WaveTableSynthesizerAppEvents.SetWavetable(waveTable)) },
                            colors = CardDefaults.cardColors(containerColor = containerColor)
                        ) {
                            Box(
                                modifier = Modifier.fillMaxSize(),
                                contentAlignment = Alignment.Center
                            ) {
                                Text(
                                    text = stringResource(id = waveTable.toResourceString()),
                                    textAlign = TextAlign.Center,
                                    style = MaterialTheme.typography.bodyMedium.copy(fontWeight = fontWeight)
                                )
                            }
                        }
                    }

                }
            }
        }
    }
}
