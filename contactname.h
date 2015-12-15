#ifndef CONTACTNAME_H
#define CONTACTNAME_H

#include <QDebug>
#include <QMetaType>

class ContactName
{
    Q_GADGET
public:
    ContactName();
    ContactName(const ContactName &other);
    ~ContactName();

    Q_PROPERTY(QString firstName MEMBER m_firstName)
    Q_PROPERTY(QString lastName MEMBER m_lastName)

    void setFirstName(const QString firstName);
    void setLastName(const QString lastName);

    bool operator==(const ContactName &other) const;
    bool operator!=(const ContactName &other) const;
    bool operator<(const ContactName &other) const;

private:
    QString m_firstName;
    QString m_lastName;
};

Q_DECLARE_METATYPE(ContactName)

#endif // CONTACTNAME_H
