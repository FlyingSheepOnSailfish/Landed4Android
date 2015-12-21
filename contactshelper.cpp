#include "contactshelper.h"
#include "contact.h"
#include "contactname.h"
#include "contactdisplaylabel.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>
#include <QtQml>

ContactsHelper::ContactsHelper(QObject *parent) :
    QObject(parent)
{
    m_instance = this;
}

ContactsHelper::~ContactsHelper()
{
}

ContactsHelper *ContactsHelper::m_instance = 0;

void ContactsHelper::registerTypes() {
    qmlRegisterType<ContactsHelper>("ContactsHelper",1,0,"ContactsHelper");
    qRegisterMetaType<Contact>();
    qRegisterMetaType<ContactName>();
    QMetaType::registerComparators<ContactName>();
    qRegisterMetaType<ContactDisplayLabel>();
    QMetaType::registerComparators<ContactDisplayLabel>();
}

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
    void contactFoundByJava(JNIEnv *env, jclass /*clazz*/, jint index, jint count, jobject jcontact)
    {
        Contact contact;
        contact.setContactId(getJObjectFieldValue(env, jcontact, "contactId", "Ljava/lang/String;"));
        contact.setDisplayLabel(getJObjectFieldValue(env, jcontact, "displayLabel", "Ljava/lang/String;"));
        contact.setFirstName(getJObjectFieldValue(env, jcontact, "firstName", "Ljava/lang/String;"));
        contact.setLastName(getJObjectFieldValue(env, jcontact, "lastName", "Ljava/lang/String;"));
        contact.setPhoneNumbers(getJObjectFieldArray(env, jcontact, "phoneNumbers", "[Ljava/lang/String;"));
        contact.setPhoneNumber(getJObjectFieldValue(env, jcontact, "phoneNumber", "Ljava/lang/String;"));
        ContactsHelper::instance()->contactFound(index, count, contact);
    }

    //http://stackoverflow.com/questions/14036004/how-to-convert-jobject-to-jstring
    //http://stackoverflow.com/questions/5972207/passing-string-array-from-java-to-c-with-jni
    //http://stackoverflow.com/questions/19591873/get-an-array-of-strings-from-java-to-c-jni

}

