#include "contactname.h"
#include <QDebug>

ContactName::ContactName() {}

ContactName::ContactName(const ContactName &other) {
    m_firstName = other.m_firstName;
    m_lastName = other.m_lastName;
}

//constructor to cast from jcontactName to QT ContactName
ContactName::ContactName(JNIEnv *env, jobject jcontactName) {
    m_firstName = getJObjectFieldStringValue(env, jcontactName, "firstName");
    m_lastName = getJObjectFieldStringValue(env, jcontactName, "lastName");
}

ContactName::~ContactName() {}

void ContactName::setFirstName(const QString firstName) {
    //qDebug() << "Contact: setting firstName: " << firstName;
    m_firstName = firstName;
}

void ContactName::setLastName(const QString lastName) {
    //qDebug() << "Contact: setting lastName: " << lastName;
    m_lastName = lastName;
}


bool ContactName::operator==(const ContactName &other) const {
    if(this == &other)
        return true;

    return (m_firstName == other.m_firstName &&
            m_lastName == other.m_lastName );
}

bool ContactName::operator!=(const ContactName &other) const {
    return !(m_firstName == other.m_firstName &&
            m_lastName == other.m_lastName );
}

bool ContactName::operator<(const ContactName &other) const {
    return (m_firstName + m_lastName < other.m_firstName + other.m_lastName);
}

