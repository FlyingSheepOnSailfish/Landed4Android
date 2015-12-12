#include "smshelper.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QDebug>

SmsHelper::SmsHelper(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
    connect(this, &SmsHelper::smsSent, this, &SmsHelper::onSendMessageFinished);
}

SmsHelper::~SmsHelper()
{
}

SmsHelper *SmsHelper::m_instance = 0;

void SmsHelper::sendSMS(const QString &contactIdentifier, const QString &message)
{
    emit stateMsg(MessageState::Pending);
    qDebug() << "SmsHelper: sendSMS called 1";
    QAndroidJniObject contact = QAndroidJniObject::fromString(contactIdentifier);
    QAndroidJniObject msg = QAndroidJniObject::fromString(message);


    QtAndroid::androidActivity().callMethod<void>("sendSMS",
                                                          "(Ljava/lang/String;Ljava/lang/String;)V",
                                                          contact.object<jstring>(),
                                                          msg.object<jstring>());

    qDebug() << "SmsHelper: sendSMS called 2";
}


//For compatability with the Sailfish implementation
//we will emit either stateMsg, or error msg
void SmsHelper::onSendMessageFinished(const QString &result)
{
    if (result == "SMS sent") {
        emit stateMsg(MessageState::Sent);
    } else {
        emit errorMsg(result);
    }
}


//Callbacks from Andorid Java
#include "droidjni.h"
namespace DroidJNI {
    using namespace DroidJNI;

    //called from Java Activity, when Sms has been sent
    void smsSentFromJava(JNIEnv *env, jclass /*clazz*/, jstring result)
    {
        //nasty cast from jstring to qstring found
        //https://groups.google.com/forum/#!topic/android-qt/qdlKrzi3mTQ
        //however I have not found an easier / cleaner way!
        const char *strResult = env->GetStringUTFChars( result, 0 );
        QString qresult(strResult);
        env->ReleaseStringUTFChars(result, strResult);
        SmsHelper::instance()->smsSent(qresult);
        qDebug() << "SmsHelper: smsSent invoked by java: " << qresult;

        //as SmsActivity result codes are integers, it might be better to pass those
        // back as such to c++, then handle on the C++ side with an enum;
        // int intValue = (int) jIntValue;

    }

    //called from Java SmSActivity, when Sms has been delivered
    void smsDeliveredFromJava(JNIEnv *env, jclass /*clazz*/, jstring result)
    {
        const char *strResult = env->GetStringUTFChars( result, 0 );
        QString qresult(strResult);
        env->ReleaseStringUTFChars(result, strResult);
        SmsHelper::instance()->smsDelivered(qresult);
        qDebug() << "SmsHelper: smsDelivered invoked by java";
    }

}

