#include <jni.h>
#include <string>
#include <thread>

extern "C" JNIEXPORT jstring JNICALL
Java_com_example_androidtutorial_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}






