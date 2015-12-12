#ifndef AUI_H
#define AUI_H

#include <QObject>

class AUI : public QObject
{
    Q_OBJECT
public:
    AUI();
    Q_INVOKABLE void lockPortrait();
};

#endif // AUI_H
