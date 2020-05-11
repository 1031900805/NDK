#include <jni.h>
#include <string>
#include <android/log.h>
#include "main.h"
#include <iostream>

#define TAG "native-lib"
#define Logg(...) _android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__)

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_ndk_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    main();
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_ndk_MainActivity_test(JNIEnv *env, jobject thiz, jint int1, jint int2) {
    return static_cast<jboolean>((int1 > int2));
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_ndk_JavaActivity_getInfo(JNIEnv *env, jobject thiz, jstring string) {
    return string;
}

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_MainActivity_testType(JNIEnv *env, jobject thiz, jboolean boolean, jbyte byte,
                                           jchar char1, jshort short1, jlong long1, jfloat float1,
                                           jdouble double1, jstring string1, jint int1,
                                           jintArray int_array, jobjectArray string_array,
                                           jbooleanArray boolean_array, jobject person) {
    unsigned char b = boolean;
    const char *name_string = env->GetStringUTFChars(string1, 0);
    env->ReleaseStringUTFChars(string1, name_string);

    const char *preson_class_str = "com/example/ndk/Person";
    jclass clazz = env->FindClass(preson_class_str);

}extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_MainActivity_testFirst(JNIEnv *env, jobject thiz) {

}