#ifndef AUIPAGESTATUS_H
#define AUIPAGESTATUS_H

#include <QObject>

class AUIPageStatus : public QObject
{
    Q_OBJECT

public:
    enum Status { Inactive, Activating, Active, Deactivating };
    Q_ENUM(Status)
};

#endif // AUIPAGESTATUS_H
