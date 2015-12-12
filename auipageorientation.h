#ifndef AUIPAGEORIENTATION_H
#define AUIPAGEORIENTATION_H

#include <QObject>

class AUIPageOrientation : public QObject
{
    Q_OBJECT

public:
    enum PageOrientation {Automatic, LockPortrait, LockLandscape, LockPrevious};
    Q_ENUM(PageOrientation)

};

#endif // AUIPAGEORIENTATION_H
