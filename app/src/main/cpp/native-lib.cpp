#include <jni.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdint.h>

extern "C"
JNIEXPORT jstring JNICALL Java_netease_com_jnisot_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL Java_netease_com_jnisot_MainActivity_printLog(
        JNIEnv *env,
        jobject) {
    printf("this write by c!");
    //uint32_t 就是一个32bit（位）的int类型记录地址，这是个指针
}

