#ifndef CONTACT_H
#define CONTACT_H

#include "droidjni.h"
#include "contactname.h"
#include "contactdisplaylabel.h"
#include <QDebug>
#include <QMetaType>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QStringList>

//This simple data structure will be passed from C++ ContactsHelper class
//to QML PhoneContactsBackEnd.qml

using namespace DroidJNI;

namespace DroidJNI {

class Contact
{
        Q_GADGET
public:

    Contact();
    Contact(const Contact &other);
    ~Contact();

    Q_PROPERTY(QString contactId MEMBER m_contactId)
    //Q_PROPERTY(QString displayLabel MEMBER m_displayLabel)
    Q_PROPERTY(ContactDisplayLabel displayLabel MEMBER m_displayLabel)
    Q_PROPERTY(ContactName name MEMBER m_contactName)
    Q_PROPERTY(QString phoneNumber MEMBER m_phoneNumber)
    Q_PROPERTY(QStringList phoneNumbers MEMBER m_phoneNumbers)
    Q_PROPERTY(int phoneNumbersCount MEMBER m_phoneNumbersCount)

    void setContactId(const QString contactId);
    //void setDisplayLabel(const QString displayLabel);
    void setDisplayLabel(JNIEnv *env, const jobject jcontact);

    //Here we expose the names to ContactHelper "flat" as strings, rather than as a contactName object
    void setFirstName(const QString firstName);
    void setLastName(const QString lastName);
    void setPhoneNumber(const QString phoneNumber);
    void setPhoneNumbers(const QStringList phoneNumbers);
    void setPhoneNumbersCount(const int phoneNumbersCount);

private:
    QString m_contactId;
    //QString m_displayLabel;
    ContactDisplayLabel m_displayLabel;
    ContactName m_contactName;
    QString m_phoneNumber;
    QStringList m_phoneNumbers;
    int m_phoneNumbersCount;
};

}

Q_DECLARE_METATYPE(Contact)
#endif // CONTACT_H
