package com.karis.wavetablesynthesizer.di

import com.karis.wavetablesynthesizer.data.NativeWavetableSynthesizer
import com.karis.wavetablesynthesizer.domain.WavetableSynthesizer
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
object AppModule {

    @Singleton
    @Provides
    fun provideNativeWavetableSynthesizer(
        nativeWavetableSynthesizer: NativeWavetableSynthesizer
    ) : WavetableSynthesizer {
        return nativeWavetableSynthesizer
    }
}