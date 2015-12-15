#include "contactshelper.h"
#include "contact.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>



ContactsHelper::ContactsHelper(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
}

ContactsHelper::~ContactsHelper()
{
}

ContactsHelper *ContactsHelper::m_instance = 0;

void ContactsHelper::getContacts()
{
    qDebug() << "ContactsHelper: getContacts called 1";

    QtAndroid::androidActivity().callMethod<void>("getContactsAsync");
    qDebug() << "ContactsHelper: getContacts called 2";

    QAndroidJniEnvironment env;
    if (env->ExceptionCheck()) {
        // Handle exception here.
        env->ExceptionClear();
    }
}

//Callbacks from Andorid Java
#include "droidjni.h"
namespace DroidJNI {
    using namespace DroidJNI;

    void allContactsSentByJava(JNIEnv *env, jclass /*clazz*/)
    {
        //signal to QML
        ContactsHelper::instance()->allContactsSent();
    }

    //Called from Java PhoneContacts, when a Contact is found
    //Will in turn cause a signal to be emitted to QML
    void contactFoundByJava2(JNIEnv *env, jclass /*clazz*/, jint index, jint count, jobject jcontact)
    {
        Contact contact;
        contact.setContactId(getJObjectFieldValue(env, jcontact, "contactId", "Ljava/lang/String;"));
        contact.setDisplayLabel(getJObjectFieldValue(env, jcontact, "displayLabel", "Ljava/lang/String;"));
        contact.setFirstName(getJObjectFieldValue(env, jcontact, "firstName", "Ljava/lang/String;"));
        contact.setLastName(getJObjectFieldValue(env, jcontact, "lastName", "Ljava/lang/String;"));
        contact.setPhoneNumber(getJObjectFieldValue(env, jcontact, "phoneNumber", "Ljava/lang/String;"));
        ContactsHelper::instance()->contactFound2(index, count, contact);
    }

    //Called from Java PhoneContacts, when a Contact is found
    //Will in turn cause a signal to be emitted to QML
    //name is the name of the contact, phoneNumbers is a string array of phone numbers of the contact.
    void contactFoundByJava(JNIEnv *env, jclass /*clazz*/, jint index, jint count, jstring name, jobjectArray phoneNumbers)
    {
        QString qname = castJStrToQStr(env, name);

        //process numbers array
        int size = env->GetArrayLength(phoneNumbers);
        //qDebug() << "ContactsHelper: contactFound invoked by java: " << index << " of " << count << ", with " << size << " number(s)";
        QVariantList numbers;
        for (int i=0; i < size; ++i)
        {
            jstring jnumber = (jstring) env->GetObjectArrayElement(phoneNumbers, i);
            QString qnumber = castJStrToQStr(env, jnumber);
            numbers.append(qnumber);
            //qDebug() << "Number:  " << i << " : " << qnumber;
        }

        //signal to QML with results
        ContactsHelper::instance()->contactFound(index, count, qname, numbers);

        //http://stackoverflow.com/questions/14036004/how-to-convert-jobject-to-jstring
        //http://stackoverflow.com/questions/5972207/passing-string-array-from-java-to-c-with-jni
        //http://stackoverflow.com/questions/19591873/get-an-array-of-strings-from-java-to-c-jni
    }

}

