#include "droidjni.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>

//This file contains utility functions used by the JNI callback functions
//It also contains the on JNI_OnLoad function allowed per app

using namespace DroidJNI;

namespace DroidJNI {

//    QString castJStrToQStr(JNIEnv *env, jstring jstr) {

    QString castJStrToQStr(JNIEnv *env, jstring jstr) {
        if (jstr != NULL) {
            //if GetStringUTFChars is fed NULL it goes bang.
            const char *cstr = env->GetStringUTFChars( jstr, 0 );
            QString qstr(cstr);
            env->ReleaseStringUTFChars(jstr, cstr);
            //env->DeleteLocalRef(jstr);
            return qstr;
        } else {
            return "";
        }
    }

    QString getJObjectFieldStringValue(JNIEnv *env, const jobject &jobj, const char *fieldName) {
        char *fieldTypeSignature = "Ljava/lang/String;";
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jstring jstr = (jstring)env->GetObjectField(jobj, fieldId);
        return castJStrToQStr(env, jstr);
    }

    QStringList getJObjectFieldArray(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature) {
        QStringList qlist;


        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jobjectArray jstringArray = (jobjectArray)env->GetObjectField(jobj, fieldId);
        int size = env->GetArrayLength(jstringArray);

        for (int i=0; i < size; ++i)
        {
            jstring jstr = (jstring)env->GetObjectArrayElement(jstringArray, i);
            QString qstr = castJStrToQStr(env, jstr);
            //qDebug() << "droidJniUtils: getJObjectFieldArray: " + qstr;
            qlist.append(qstr);
        }
        return qlist;
    }

 /*


//Stackoverflow examples
int size = env->GetArrayLength(stringArrays);

for (int i=0; i < size; ++i)
{
    jstring string = env->GetObjectArrayElement(stringArrays, i);
    const char* mayarray = env->GetStringUTFChars(string, 0);
    .... do some work or copy it to a c++ array of char*....
    env->ReleaseStringUTFChars(string, myarray);
    env->DeleteLocalRef(string);
}



    void MyJNIFunction(JNIEnv *env, jobject object, jobjectArray stringArray) {

        int stringCount = env->GetArrayLength(stringArray);

        for (int i=0; i<stringCount; i++) {
            jstring string = (jstring) GetObjectArrayElement(env, stringArray, i);
            const char *rawString = GetStringUTFChars(env, string, 0);
            // Don't forget to call `ReleaseStringUTFChars` when you're done.
        }
    }
   */

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

