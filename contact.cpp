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

Contact::~Contact() {}

void Contact::setContactId(const QString contactId) {
    //qDebug() << "Contact: setting contactId: " << contactId;
    m_contactId = contactId;
}

////expose displayLabel flat, rather than as displayLabel object
//void Contact::setDisplayLabel(const QString displayLabel) {
//    //qDebug() << "Contact: setting displayLabel: " << displayLabel;
//    m_displayLabel.setlabel(displayLabel);
//}

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

void Contact::setPhoneNumbers(const QStringList phoneNumbers) {
    qDebug() << "Contact: setting phoneNumbers: " << phoneNumbers;
    m_phoneNumbers = phoneNumbers;
}

void Contact::setPhoneNumbersCount(const int phoneNumbersCount) {
    qDebug() << "Contact: setting phoneNumbersCount: " << phoneNumbersCount;
    m_phoneNumbersCount = phoneNumbersCount;
}
