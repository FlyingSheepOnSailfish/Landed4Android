#ifndef CONTACTSHELPER_H
#define CONTACTSHELPER_H
#include "contact.h"
#include <QObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>

class ContactsHelper : public QObject
{
    Q_OBJECT

public:
    explicit ContactsHelper(QObject *parent = 0);
    ~ContactsHelper();
    Q_INVOKABLE void getContacts();

    static ContactsHelper *instance() { return m_instance; }
    static void registerTypes();

signals:
    void allContactsSent();
    void contactFound(const int index, const int count, const QString &name, const QVariantList &numbers);
    void contactFound2(const int index, const int count, const Contact &contact);

private:
    static ContactsHelper *m_instance;
    static jint registerNatives();

};

#endif // CONTACTSHELPER_H
