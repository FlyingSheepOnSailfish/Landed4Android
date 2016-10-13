#include "contact.h"
#include <QDebug>

Contact::Contact() {}

Contact::Contact(const Contact &other) {
    //qDebug() << "Contact: copy constructor called: " << other.m_displayLabel;
    m_contactId = other.m_contactId;
    m_displayLabel = other.m_displayLabel;
    m_contactName = other.m_contactName;
//    m_firstName = other.m_firstName;
//    m_lastName = other.m_lastName;
    m_phoneNumber = other.m_phoneNumber;
    m_phoneNumbers = other.m_phoneNumbers;
    m_phoneNumbersCount = other.m_phoneNumbersCount;
}


Contact::Contact(JNIEnv *env, jobject jcontact) {
    m_contactId = getJObjectFieldStringValue(env, jcontact, "contactId");
    m_displayLabel = ContactDisplayLabel(env, getJObjectChildJObject(env, jcontact, "displayLabel", "Lorg/flyingsheep/landed/ContactDisplayLabel;"));
    m_contactName = ContactName(env, getJObjectChildJObject(env, jcontact, "name", "Lorg/flyingsheep/landed/ContactName;"));

    jobjectArray jObjArray = getJObjectFieldObjectArray(env, jcontact, "phoneNumbers", "[Lorg/flyingsheep/landed/ContactPhoneNumber;");
//  The jobjectArray is now filled with jobjects
//  We must now cycle through it, and cast each of the jobjects with its phoneNumber equivalent Qt Custom Object

    int size = env->GetArrayLength(jObjArray);
    //qDebug() << "Contact: Array has members: " << size;
    for (int i=0; i < size; ++i)
    {
        jobject jobj = (jobject)env->GetObjectArrayElement(jObjArray, i);
        //cast jobj to phoneNumber, then cast to QVariant to be able to append to QVariantList
        ContactPhoneNumber temp = ContactPhoneNumber(env, jobj);
        m_phoneNumbers.append(QVariant::fromValue(temp));
    }

    m_phoneNumber = getJObjectFieldStringValue(env, jcontact, "phoneNumber");
}

Contact::~Contact() {}

void Contact::setContactId(const QString contactId) {
    //qDebug() << "Contact: setting contactId: " << contactId;
    m_contactId = contactId;
}

void Contact::setDisplayLabel(JNIEnv *env, const jobject jcontact) {
    m_displayLabel = ContactDisplayLabel(getJObjectFieldStringValue(env, jcontact, "label"));
}


//Here we expose the names flat, rather than as contactName object
void Contact::setFirstName(const QString firstName) {
    //qDebug() << "Contact: setting firstName: " << firstName;
    m_contactName.setFirstName(firstName);
}

void Contact::setLastName(const QString lastName) {
    //qDebug() << "Contact: setting lastName: " << lastName;
    m_contactName.setLastName(lastName);
}

void Contact::setPhoneNumber(const QString phoneNumber) {
    //qDebug() << "Contact: setting phoneNumber: " << phoneNumber;
    m_phoneNumber = phoneNumber;
}

void Contact::setPhoneNumbers(const QVariantList phoneNumbers) {
    qDebug() << "Contact: setting phoneNumbers: " << phoneNumbers;
    m_phoneNumbers = phoneNumbers;
}

void Contact::setPhoneNumbersCount(const int phoneNumbersCount) {
    qDebug() << "Contact: setting phoneNumbersCount: " << phoneNumbersCount;
    m_phoneNumbersCount = phoneNumbersCount;
}
