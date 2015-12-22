TEMPLATE = app

QT += qml quick widgets androidextras positioning sensors

SOURCES += main.cpp \
    smshelper.cpp \
    contactshelper.cpp \
    droidJniUtils.cpp \
    jsonstorage.cpp \
    satinfosource.cpp \
    torchhelper.cpp \
    aui.cpp \
    contact.cpp \
    contactname.cpp \
    contactdisplaylabel.cpp \
    contactphonenumber.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/SmsHelper.java \
    android/src/ContactsHelper.java \
    android/src/TorchHelper.java \
    android/src/LandedActivity.java \
    android/src/TorchHelperMarshmallow.java \
    android/src/TorchHelperLollipop.java \
    android/src/Contact.java \
    android/src/ContactPhoneNumber.java \
    android/src/ContactName.java \
    android/src/ContactDisplayLabel.java \
    android/src/ContactDisplayLabel.java \
    android/src/ContactName.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

HEADERS += \
    smshelper.h \
    contactshelper.h \
    droidjni.h \
    jsonstorage.h \
    satinfosource.h \
    landedtheme.h \
    torchhelper.h \
    aui.h \
    auipageorientation.h \
    auipagestatus.h \
    contact.h \
    contactname.h \
    contactdisplaylabel.h \
    contactphonenumber.h

