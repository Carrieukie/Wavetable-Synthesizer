#pragma once

#include<android/log.h>

#ifndef NDEBUG
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, "wavetablesynthesizer", __VA_ARGS__)
#else
#define LOGD(...)
#endif

