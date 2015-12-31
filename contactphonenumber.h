#ifndef CONTACTPHONENUMBER_H
#define CONTACTPHONENUMBER_H

#include "droidjni.h"
#include <QDebug>
#include <QMetaType>
#include <QtAndroidExtras/QAndroidJniEnvironment>

using namespace DroidJNI;

namespace DroidJNI {

class ContactPhoneNumber
{
    Q_GADGET
public:
    ContactPhoneNumber();
    ContactPhoneNumber(const ContactPhoneNumber &other);
    ContactPhoneNumber(JNIEnv *env, jobject jcontactPhoneNumber);
    ~ContactPhoneNumber();

    Q_PROPERTY(QString number MEMBER m_number)
    Q_PROPERTY(int type MEMBER m_type)

    void setNumber(const QString number);
    void setType(const int type);

    bool operator==(const ContactPhoneNumber &other) const;
    bool operator!=(const ContactPhoneNumber &other) const;
    bool operator<(const ContactPhoneNumber &other) const;

private:
    QString m_number;
    int m_type;
};

}
Q_DECLARE_METATYPE(ContactPhoneNumber)

#endif // CONTACTPHONENUMBER_H
