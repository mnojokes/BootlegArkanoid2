#include <jni.h>
#include "Game/GameControl.h"

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_bootlegarkanoid_MainActivity_Launch(JNIEnv *env, jobject thiz, jint sizeX, jint sizeY, jfloat refreshRate)
{
    return GameControl::Initialize(sizeX, sizeY, refreshRate);
}

extern "C"
JNIEXPORT jboolean JNICALL
Java_com_example_bootlegarkanoid_MainActivity_SignalInputEvent(JNIEnv *env, jobject thiz, jint action, jfloat x, jfloat y)
{
    return GameControl::NewInputEvent(action, x, y);
}
