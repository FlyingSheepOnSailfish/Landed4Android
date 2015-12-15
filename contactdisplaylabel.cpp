#include "contactdisplaylabel.h"

ContactDisplayLabel::ContactDisplayLabel() {}

ContactDisplayLabel::~ContactDisplayLabel() {}

ContactDisplayLabel::ContactDisplayLabel(const ContactDisplayLabel &other) {
    m_label = other.m_label;
}

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

