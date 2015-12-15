#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include "aui.h"
#include "auipageorientation.h"
#include "auipagestatus.h"
#include "landedtheme.h"
#include "jsonstorage.h"
#include "torchhelper.h"
#include "satinfosource.h"
#include "smshelper.h"
#include "contactshelper.h"

static QObject *aui_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    AUI *aui = new AUI();
    return aui;
}

static QObject *theme_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    LandedTheme *landedTheme = new LandedTheme();
    return landedTheme;
}

static QObject *jsonStorage_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)

    JSONStorage *jsonStorage = new JSONStorage();
    return jsonStorage;
}

int main(int argc, char *argv[])
{

    QApplication app(argc, argv);

    QCoreApplication::setOrganizationDomain("org.flyingsheep.landed");

    qmlRegisterUncreatableType<AUIPageOrientation>("AUI", 1, 0, "AUIPageOrientation", "");
    qmlRegisterUncreatableType<AUIPageStatus>("AUI", 1, 0, "AUIPageStatus", "");
    qmlRegisterSingletonType<AUI>("AUI", 1, 0, "AUI", aui_singletontype_provider);
    qmlRegisterSingletonType<LandedTheme>("LandedTheme", 1, 0, "LandedTheme", theme_singletontype_provider);
    qmlRegisterSingletonType<JSONStorage>("JSONStorage",1,0,"JSONStorage", jsonStorage_singletontype_provider);
    qmlRegisterType<SatInfoSource>("SatInfoSource",1,0,"SatInfoSource");
    qmlRegisterType<SmsHelper>("SmsHelper",1,0,"SmsHelper");
    ContactsHelper::registerTypes();
    qmlRegisterType<TorchHelper>("TorchHelper",1,0,"TorchHelper");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}

