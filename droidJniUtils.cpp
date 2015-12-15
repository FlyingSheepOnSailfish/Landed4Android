#include "droidjni.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>

//This file contains utility functions used by the JNI callback functions
//It also contains the on JNI_OnLoad function allowed per app

using namespace DroidJNI;

namespace DroidJNI {

    QString castJStrToQStr(JNIEnv *env, jstring jstr) {
        const char *cstr = env->GetStringUTFChars( jstr, 0 );
        QString qstr(cstr);
        env->ReleaseStringUTFChars(jstr, cstr);
        //env->DeleteLocalRef(jstr);
        return qstr;
    }

//    QString getJObjectFieldValue(JNIEnv *env, const jobject &jobj, const QString &fieldName, const QString &fieldTypeSignature) {
//        jclass cls = env->GetObjectClass(jobj);
//        jfieldID fieldId = env->GetFieldID(cls, fieldName.toUtf8().constData(), fieldTypeSignature.toUtf8().constData());
//        jstring jstr = (jstring)env->GetObjectField(jobj, fieldId);
//        return castJStrToQStr(env, jstr);
//    }


    QString getJObjectFieldValue(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature) {
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jstring jstr = (jstring)env->GetObjectField(jobj, fieldId);
        return castJStrToQStr(env, jstr);
    }

}

JNIEXPORT jint JNI_OnLoad(JavaVM* vm, void* /*reserved*/)
{
    JNIEnv* env;
    // get the JNIEnv pointer.
    if (vm->GetEnv(reinterpret_cast<void**>(&env), JNI_VERSION_1_6) != JNI_OK) {
        qDebug() << "ERROR: JNI version";
        return JNI_ERR;
    }
    // search for Java class which declares the native methods
    jclass javaClass = env->FindClass(classname);
    if (!javaClass) {
        qDebug() << "ERROR: " << classname << " not found";
        return JNI_ERR;
    } else {
        qDebug() << "Success:  " << classname << " found";
    }
    // register our native methods
    if (env->RegisterNatives(javaClass, methods, sizeof(methods) / sizeof(methods[0])) < 0) {
        qDebug() << "ERROR: Registering Natives";
        return JNI_ERR;
    }
    return JNI_VERSION_1_6;
}

