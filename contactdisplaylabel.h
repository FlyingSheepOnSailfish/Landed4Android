#ifndef CONTACTDISPLAYLABEL_H
#define CONTACTDISPLAYLABEL_H

#include <QDebug>
#include <QMetaType>

class ContactDisplayLabel
{
    Q_GADGET
public:
    ContactDisplayLabel();
    ContactDisplayLabel(const ContactDisplayLabel &other);
    ~ContactDisplayLabel();

    Q_PROPERTY(QString label MEMBER m_label)
    void setlabel(const QString label);

    bool operator==(const ContactDisplayLabel &other) const;
    bool operator!=(const ContactDisplayLabel &other) const;
    bool operator<(const ContactDisplayLabel &other) const;
private:
    QString m_label;

};

#endif // CONTACTDISPLAYLABEL_H
