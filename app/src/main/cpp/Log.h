//
// Created by shs1330 on 2018/2/1.
//

#ifndef JNISOT_LOG_H
#define JNISOT_LOG_H
#include <android/log.h>
#define TAG "Native"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGW(...)  __android_log_print(ANDROID_LOG_WARN,TAG,__VA_ARGS__)
#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,TAG,__VA_ARGS__)
#endif //JNISOT_LOG_H
