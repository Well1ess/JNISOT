#include <time.h>
#include <stdlib.h>
#include <string>
#include <stddef.h>
#include <assert.h>

#include <stdbool.h>
#include <fcntl.h>
#include <dlfcn.h>

#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <utime.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "Log.h"
#include "art_5_0.h"


extern "C"
JNIEXPORT jstring JNICALL Java_netease_com_jnisot_Ap_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C" {
void static printInfo(JNIEnv *env,jobject srcMethod)
{
    art::mirror::ArtMethod* srcMethodInfo =
            (art::mirror::ArtMethod *) env->FromReflectedMethod(srcMethod);
    LOGD("methodInfo: %d",reinterpret_cast<art::mirror::Class*>(srcMethodInfo->declaring_class_)->status_);

}
JNIEXPORT void JNICALL Java_netease_com_jnisot_Ap_printLog(
        JNIEnv *env,
        jobject) {
    printf("this write by c!");
    //uint32_t 就是一个32bit（位）的int类型记录地址，这是个指针
}
JNIEXPORT void JNICALL Java_netease_com_jnisot_Ap_printAPILevel(
        JNIEnv *env,
        jobject,
        int api) {
    LOGD("apk: %d", api);
}
JNIEXPORT void JNICALL Java_netease_com_jnisot_Ap_printMethodInfo(
        JNIEnv *env,
        jobject,
        jobject srcMethod) {
    printInfo(env, srcMethod);
}

JNIEXPORT void JNICALL Java_netease_com_jnisot_Ap_replace(
        JNIEnv *env,
        jobject,
        jobject srcMethod,
        jobject dest) {


    printInfo(env, srcMethod);
    printInfo(env, dest);
    art::mirror::ArtMethod* smeth =
            (art::mirror::ArtMethod*) env->FromReflectedMethod(srcMethod);

    art::mirror::ArtMethod* dmeth =
            (art::mirror::ArtMethod*) env->FromReflectedMethod(dest);

    reinterpret_cast<art::mirror::Class*>(dmeth->declaring_class_)->class_loader_ =
            reinterpret_cast<art::mirror::Class*>(smeth->declaring_class_)->class_loader_;
//    //for plugin classloader
    reinterpret_cast<art::mirror::Class*>(dmeth->declaring_class_)->clinit_thread_id_ =
            reinterpret_cast<art::mirror::Class*>(smeth->declaring_class_)->clinit_thread_id_;
    reinterpret_cast<art::mirror::Class*>(dmeth->declaring_class_)->status_ =
            reinterpret_cast<art::mirror::Class*>(smeth->declaring_class_)->status_-1;
    //for reflection invoke
    reinterpret_cast<art::mirror::Class*>(dmeth->declaring_class_)->super_class_ = 0;

    smeth->declaring_class_ = dmeth->declaring_class_;
    smeth->access_flags_ = dmeth->access_flags_ | 0x0001;
    smeth->dex_cache_resolved_types_ = dmeth->dex_cache_resolved_types_;
    smeth->dex_cache_resolved_methods_ = dmeth->dex_cache_resolved_methods_;
    smeth->dex_cache_strings_ = dmeth->dex_cache_strings_;
    smeth->dex_code_item_offset_ = dmeth->dex_code_item_offset_;
    smeth->dex_method_index_ = dmeth->dex_method_index_;
    smeth->gc_map_ = dmeth->gc_map_;
    smeth->entry_point_from_jni_ = dmeth->entry_point_from_jni_;
    smeth->entry_point_from_quick_compiled_code_ = dmeth->entry_point_from_quick_compiled_code_;

    smeth->entry_point_from_interpreter_ = dmeth->entry_point_from_interpreter_;

    smeth->method_index_ = dmeth->method_index_;

    LOGD("replace_5_0: %d , %d", smeth->entry_point_from_quick_compiled_code_,
         dmeth->entry_point_from_quick_compiled_code_);
}
}
