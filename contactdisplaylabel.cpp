#include "contactdisplaylabel.h"
#include "droidjni.h"

ContactDisplayLabel::ContactDisplayLabel() {}

ContactDisplayLabel::ContactDisplayLabel(const ContactDisplayLabel &other) {
    m_label = other.m_label;
}

//temporary constructor, takes a string for the single property!
ContactDisplayLabel::ContactDisplayLabel(const QString label) {
    m_label = label;
}

//constructor to cast from jcontactDisplayLabel to QT ContactDisplayLabel
ContactDisplayLabel::ContactDisplayLabel(JNIEnv *env, jobject jcontactDisplayLabel) {
    m_label = getJObjectFieldStringValue(env, jcontactDisplayLabel, "label");
}

ContactDisplayLabel::~ContactDisplayLabel() {}

void ContactDisplayLabel::setlabel(const QString label) {
    //qDebug() << "Contact: setting label: " << label;
    m_label = label;
}

bool ContactDisplayLabel::operator==(const ContactDisplayLabel &other) const {
    if(this == &other)
        return true;

    return (m_label == other.m_label);
}

bool ContactDisplayLabel::operator!=(const ContactDisplayLabel &other) const {
    return !(m_label == other.m_label);
}

bool ContactDisplayLabel::operator<(const ContactDisplayLabel &other) const {
    return (m_label < other.m_label);
}

