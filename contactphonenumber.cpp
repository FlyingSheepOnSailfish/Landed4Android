#include "contactphonenumber.h"

ContactPhoneNumber::ContactPhoneNumber() {}

ContactPhoneNumber::ContactPhoneNumber(const ContactPhoneNumber &other) {
    m_number = other.m_number;
    m_type = other.m_type;
}

ContactPhoneNumber::ContactPhoneNumber(JNIEnv *env, jobject jcontactPhoneNumber) {
    m_number = getJObjectFieldStringValue(env, jcontactPhoneNumber, "number");
}

ContactPhoneNumber::~ContactPhoneNumber() {}

void ContactPhoneNumber::setNumber(const QString number) {
    m_number = number;
}

void ContactPhoneNumber::setType(const int type) {
    m_type = type;
}

bool ContactPhoneNumber::operator==(const ContactPhoneNumber &other) const {
    if(this == &other)
        return true;
    return (m_number == other.m_number &&
            m_type == other.m_type );
}

bool ContactPhoneNumber::operator!=(const ContactPhoneNumber &other) const {
    return !(m_number == other.m_number &&
            m_type == other.m_type );
}

bool ContactPhoneNumber::operator<(const ContactPhoneNumber &other) const {
    return (m_number + m_type < other.m_number + other.m_type);
}

