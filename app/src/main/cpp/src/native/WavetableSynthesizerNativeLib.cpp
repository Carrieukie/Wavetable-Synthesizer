#include <jni.h>
#include <memory>
#include "utilities/Log.h"
#include "wavetable/WavetableSynthesizer.h"

extern "C"
JNIEXPORT jlong JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_create(JNIEnv *env,jobject thiz) {
//     Create the synthesizer using std::make_unique
    auto synthesizer = std::make_unique<wavetablesynthesizer::WavetableSynthesizer>();

    if (!synthesizer) {
        LOGD("Failed to create synthesizer");
        return -1;  // Return -1 to indicate failure
    }
    return reinterpret_cast<jlong>(synthesizer.release());
}

extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_delete(JNIEnv *env,
                                                                           jobject thiz,
                                                                           jlong synthesizer_handle) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Attempting to delete null synthesizer");
        return;
    }
    delete synthesizer;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_play(JNIEnv *env, jobject thiz,
                                                                         jlong synthesizer_handle) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before playing");
        return;
    }
    LOGD("Playing synthesizer");
    synthesizer->play();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_stop(JNIEnv *env, jobject thiz,
                                                                         jlong synthesizer_handle) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before stopping");
        return;
    }
    synthesizer->stop();

}
extern "C"
JNIEXPORT jboolean JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_isPlaying(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jlong synthesizer_handle) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before checking if playing");
        return false;
    }
    return synthesizer->isPlaying();
}
extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_setFrequency(JNIEnv *env,
                                                                                 jobject thiz,
                                                                                 jlong synthesizer_handle,
                                                                                 jfloat frequency_in_hz) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before setting frequency");
        return;
    }
    synthesizer->setFrequency(frequency_in_hz);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_setVolume(JNIEnv *env,
                                                                              jobject thiz,
                                                                              jlong synthesizer_handle,
                                                                              jfloat amplitude_in_db) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before setting volume");
        return;
    }
    synthesizer->setVolume(static_cast<float>(amplitude_in_db));
}
extern "C"
JNIEXPORT void JNICALL
Java_com_karis_wavetablesynthesizer_data_NativeWavetableSynthesizer_setWavetable(JNIEnv *env,
                                                                                 jobject thiz,
                                                                                 jlong synthesizer_handle,
                                                                                 jint wavetable) {
    auto *synthesizer = reinterpret_cast<wavetablesynthesizer::WavetableSynthesizer *>(synthesizer_handle);
    if (!synthesizer) {
        LOGD("Sysnthesizer not created. Please create synthesizer first before setting wavetable");
        return;
    }
    synthesizer->setWaveTable(static_cast<wavetablesynthesizer::WaveTable>(wavetable));
}