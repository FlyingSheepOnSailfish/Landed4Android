#include "aui.h"
#include "auipagestatus.h"
//#include "auidialogstatus.h"
#include "auipageorientation.h"
#include <QDebug>
#include <QtAndroidExtras/QtAndroid>
//#include <QtAndroidExtras/QAndroidJniObject>

AUI::AUI()
{

}

void AUI::lockPortrait()
{
    qDebug() << "AUI: lockPortrait() called 1";
    QtAndroid::androidActivity().callMethod<void>("lockPortrait");
    qDebug() << "AUI: lockPortrait() called 2";
}

