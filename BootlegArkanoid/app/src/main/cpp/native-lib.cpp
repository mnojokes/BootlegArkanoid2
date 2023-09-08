#include <jni.h>
#include <android/native_window_jni.h>
#include "Game/GameControl.h"
#include <

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_bootlegarkanoid_MainActivity_Launch(JNIEnv *env, jobject thiz, jobject surface, jfloat refreshRate)
{
    ANativeWindow *window = ANativeWindow_fromSurface(env, surface);
    window.
   // ANativeWindow_release(window);
    return GameControl::Initialize(window, refreshRate);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_bootlegarkanoid_MainActivity_SignalInputEvent(JNIEnv *env, jobject thiz, jint action, jfloat x, jfloat y)
{
    return GameControl::NewInputEvent(action, x, y);
}
