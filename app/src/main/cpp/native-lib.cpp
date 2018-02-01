#include <jni.h>
#include <stdlib.h>
#include <string>
#include <android/log.h>
#define TAG    "DroidMage"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)


extern "C"
JNIEXPORT jstring JNICALL Java_netease_com_jnisot_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" {
JNIEXPORT void JNICALL Java_netease_com_jnisot_MainActivity_printLog(
        JNIEnv *env,
        jobject) {
    printf("this write by c!");
    //uint32_t 就是一个32bit（位）的int类型记录地址，这是个指针
}
JNIEXPORT void JNICALL Java_netease_com_jnisot_MainActivity_printAPILevel(
        JNIEnv *env,
        jobject,
        int api) {
    char num[1];
    num[0] = api % 10;
    LOGD(api + "", api + " ");
}
}
