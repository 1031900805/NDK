#include <jni.h>
#include <string>
#include <android/log.h>
#include "main.h"
#include <iostream>

#define TAG "native-lib"
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG,  __VA_ARGS__)

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_JNIActivity_testPerson(JNIEnv *env, jobject thiz) {
    // TODO: implement testPerson()
}


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

    int num = int1;
    LOGD("test");
    LOGD("test01\n");
    const char *preson_class_str = "com/example/ndk/Person";
//    jclass clazz = env->FindClass(preson_class_str);



}

jclass dogClass;    //放在这里并不意味着全局引用

extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_JNIActivity_testDog(JNIEnv *env, jobject thiz) {

    if (dogClass == NULL) {
        const char *dogPath = "com/example/ndk/bean/Dog";
        //这种写法只是局部引用
//        dogClass = env->FindClass(dogPath);

        jclass dogClazz = env->FindClass(dogPath);
        //这样写才是全局引用
        dogClass = static_cast<jclass >(env->NewGlobalRef(dogClazz));

        __android_log_print(ANDROID_LOG_DEBUG, "99788", "dogClass == null");
    }

    jmethodID init = env->GetMethodID(dogClass, "<init>", "()V");
    env->NewObject(dogClass, init);
    //执行之后会隐式释放dogClass
}

/**
 * 手动释放  对象存在于堆区 需要释放
 * @param env
 */
void unDog(JNIEnv *env) {
    if (dogClass != NULL) {
        env->DeleteGlobalRef(dogClass);
        dogClass == NULL;
    }
}

/**
 * 测试方法 将一个类当作对象传递到另一个类中的方法中 并且调用
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_example_ndk_JNIActivity_testObject(JNIEnv *env, jobject thiz) {
    const char *classPath = "com/example/ndk/bean/People";
    jclass peopleClass = env->FindClass(classPath);
    jobject people = env->AllocObject(peopleClass);

    jmethodID setDog = env->GetMethodID(peopleClass, "setStudent", "(Lcom/example/ndk/bean/Dog;)V");

    //创建dog对象 并且set数据
    const char *dogPath = "com/example/ndk/bean/Dog";
    jclass dogClass = env->FindClass(dogPath);
    jobject dog = env->AllocObject(dogClass);

    jmethodID setName = env->GetMethodID(dogClass, "setName", "(Ljava/lang/String;)V");
    jmethodID setAge = env->GetMethodID(dogClass, "setAge", "(I)V");
    jstring str = env->NewStringUTF("憨豆");
    jint age = 6;
    env->CallVoidMethod(dog, setName, str);
    env->CallVoidMethod(dog, setAge, age);

    //调用setDog并且传递对象
    env->CallVoidMethod(people, setDog, dog);
}

void dynamicRegister(JNIEnv *env, jobject thiz, jstring string) {
    const char *textValue = env->GetStringUTFChars(string, NULL);
    __android_log_print(ANDROID_LOG_DEBUG, "99788", "动态注册的函数执行了 %s", textValue);
    env->ReleaseStringUTFChars(string, textValue);
}

jobject instance;
JavaVM *jvm;

/**
 * 线程要运行的方法
 * @param pVoid
 * @return
 */
void *customThread(void *pVoid) {
    //子线程需要获取env操作
    JNIEnv *env = nullptr;
    //把native的线程附加到jvm上
    jint result = jvm->AttachCurrentThread(&env, 0);
    if (result != 0) {
        return 0;
    }

    //获取到方法
    jclass activity = env->GetObjectClass(instance);
    const char *sig = "()V";
    jmethodID toast = env->GetMethodID(activity, "toast", sig);

    env->CallVoidMethod(instance, toast);

    jvm->DetachCurrentThread();
    return 0;
}

void testThread(JNIEnv *env, jobject thiz) {

    instance = env->NewGlobalRef(thiz); //全局引用对象 方法结束不会清除 否则会悬空

    pthread_t pthread;
    pthread_create(&pthread, 0, customThread, instance);
    pthread_join(pthread, 0);
}

//具体方法
static const JNINativeMethod jniNativeMethod[] = {
        // 方法名字             参数和返回值(签名)
        {"dynamicRegister", "(Ljava/lang/String;)V", (void *) (dynamicRegister)},
        {"testThread",      "()V",                   (void *) (testThread)}
};
/**
 * 动态注册
 * @param vm
 * @param unused
 * @return
 */
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *unused) {
    jvm = vm;
    JNIEnv *jniEnv = nullptr;
    //获取到env操作
    jint result = jvm->GetEnv(reinterpret_cast<void **>(&jniEnv), JNI_VERSION_1_6);

    if (result != JNI_OK) {
        return -1;
    }

    //获取类名
    const char *classStr = "com/example/ndk/JNIActivity";
    jclass clazz = jniEnv->FindClass(classStr);
    //注册native方法 类名，方法，数量
    jniEnv->RegisterNatives(clazz, jniNativeMethod,
                            sizeof(jniNativeMethod) / sizeof(JNINativeMethod));
    return JNI_VERSION_1_6;
}