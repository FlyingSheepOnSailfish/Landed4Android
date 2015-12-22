#ifndef CONTACTDISPLAYLABEL_H
#define CONTACTDISPLAYLABEL_H

#include "droidjni.h"
#include <QDebug>
#include <QMetaType>
#include <QtAndroidExtras/QAndroidJniEnvironment>

using namespace DroidJNI;

namespace DroidJNI {

class ContactDisplayLabel
{
    Q_GADGET
public:
    ContactDisplayLabel();
    ContactDisplayLabel(const ContactDisplayLabel &other);
    ContactDisplayLabel(const QString label);
    ContactDisplayLabel(JNIEnv *env, jobject jcontactDisplayLabel);
    ~ContactDisplayLabel();

    Q_PROPERTY(QString label MEMBER m_label)
    void setlabel(const QString label);

    bool operator==(const ContactDisplayLabel &other) const;
    bool operator!=(const ContactDisplayLabel &other) const;
    bool operator<(const ContactDisplayLabel &other) const;
private:
    QString m_label;

};
}

Q_DECLARE_METATYPE(ContactDisplayLabel)
#endif // CONTACTDISPLAYLABEL_H
