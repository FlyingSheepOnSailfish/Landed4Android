#ifndef DROIDJNI
#define DROIDJNI
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>

namespace DroidJNI {

    //QString castJStrToQStr(JNIEnv *env, jstring jstr);
    QString castJStrToQStr(JNIEnv *env, jstring jstr);
    QString getJObjectFieldValue(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature);
    QStringList getJObjectFieldArray(JNIEnv *env, const jobject &jobj, const char *fieldName, const char *fieldTypeSignature);

    const char* const classname = "org/flyingsheep/landed/landed29/LandedActivity";

    // Callbacks from java to C++
    // The implementations of these are found at the end of relevant class file
    // in the DroidJNI namespace section.
    // Using a common namespace gives JNI_OnLoad etc access to these even though they are distributed
    // amongst multiple source files.

    void allContactsSentByJava(JNIEnv *env, jclass /*clazz*/);
    void contactFoundByJava(JNIEnv *env, jclass /*clazz*/, jint index, jint count, jobject jcontact);
    void smsSentFromJava(JNIEnv *env, jclass /*clazz*/, jstring result);
    void smsDeliveredFromJava(JNIEnv *env, jclass /*clazz*/, jstring result);

    //mappings between C++ (native) and java function names
    const JNINativeMethod methods[] = {
        //1) name of the function called in java
        //2) signature (void string)
        //3) equivalent name of the function in C++
        {"allContactsSent", "()V", (void *)allContactsSentByJava},
        {"contactFound", "(IILorg/flyingsheep/landed/landed29/Contact;)V", (void *)contactFoundByJava},
        {"smsSent", "(Ljava/lang/String;)V", (void *)smsSentFromJava},
        {"smsDelivered", "(Ljava/lang/String;)V", (void *)smsDeliveredFromJava}
    };

    //Note: When a callback params are changed, check the following
    //a) java call of the native method
    //b) java declaration of the native method (LandedActivity.java)
    //c) entry in methods array above
    //e) C++ declaration of function above
    //f) C++ implementation of function in relevant source file
    //g) C++ declaration of the equivalent signal to QML in relevant header file
    //h) C++ implementation / call to signal is written by MOC

}

#endif // DROIDJNI

