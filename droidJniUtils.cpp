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

    int getJObjectFieldIntValue(JNIEnv *env, const jobject &jobj, const char *fieldName) {
        char *fieldTypeSignature = "I";
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jint j_int = (jint)env->GetObjectField(jobj, fieldId);
        return j_int;
    }


    QString getJObjectFieldStringValue(JNIEnv *env, const jobject &jobj, const char *fieldName) {
        char *fieldTypeSignature = "Ljava/lang/String;";
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jstring jstr = (jstring)env->GetObjectField(jobj, fieldId);
        return castJStrToQStr(env, jstr);
    }

    jobject getJObjectChildJObject(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature) {
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jobject jChildObject = (jobject)env->GetObjectField(jobj, fieldId);
        return jChildObject;
    }

    jobjectArray getJObjectFieldObjectArray(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature) {
        jclass cls = env->GetObjectClass(jobj);
        jfieldID fieldId = env->GetFieldID(cls, fieldName, fieldTypeSignature);
        jobjectArray jObjArray = (jobjectArray)env->GetObjectField(jobj, fieldId);

        return jObjArray;
    }

    QStringList getJObjectFieldStringArray(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature) {
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

    //http://stackoverflow.com/questions/14036004/how-to-convert-jobject-to-jstring
    //http://stackoverflow.com/questions/5972207/passing-string-array-from-java-to-c-with-jni
    //http://stackoverflow.com/questions/19591873/get-an-array-of-strings-from-java-to-c-jni

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

