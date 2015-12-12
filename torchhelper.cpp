#include "torchhelper.h"
#include <QtAndroidExtras/QtAndroid>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QDebug>

TorchHelper::TorchHelper(QObject *parent) :
    QObject(parent), timer(0), mEnabled(false), mlightOnEnabled(false), mTorchOn(false), mtorchMode(Beam), mStatus(offBeam)
{

}

TorchHelper::~TorchHelper()
{
    releaseTimer();
    releaseTorch();
}
void TorchHelper::initTorch() {
    //in SailfishOS, here we initiate via Gstreamer C++ api calls
    //in Android, here we initiate via Andorid java api calls
    QtAndroid::androidActivity().callMethod<void>("initTorch");
}

void TorchHelper::initTimer() {
    qDebug() << "timer initialising";
    timer = new QTimer(this);
    timer->setInterval(mFlashRate);
    timer->setSingleShot(false);
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(flashEvent()));
}

void TorchHelper::releaseTimer() {
    if(timer)
        timer->stop();
    delete timer;
}

void TorchHelper::releaseTorch() {
    QtAndroid::androidActivity().callMethod<void>("releaseTorch");
}


bool  TorchHelper::enabled(){
    qDebug() << "enabled: " << mEnabled;
    return mEnabled;
}

void  TorchHelper::setEnabled(bool enabled){
    qDebug() << "SET ENABLED" << enabled;
    if (enabled != mEnabled) {
        mEnabled = enabled;
        emit enabledChanged(enabled);
        if (enabled) {
            qDebug() << "Initiating Torch and Timer";
            initTorch();
            initTimer();
            if (mlightOnEnabled) {
                setTorchOn(true);
            }
        } else {
            qDebug() << "Releasing Torch and Timer";
            mTorchOn = false;
            releaseTimer();
            releaseTorch();
        }
    }
}

//this is the entry point from QML to turn torch on or off
void TorchHelper::toggleTorchOnOff(){
    qDebug() << "TOGGLE TORCH ON / OFF from" << mTorchOn << "to" << !mTorchOn;
    setTorchOn(!mTorchOn);
}

bool  TorchHelper::torchOn(){
    qDebug() << "torchOn: " << mTorchOn;
    return mTorchOn;
}

void  TorchHelper::setTorchOn(bool torchOn){
    qDebug() << "SET TORCH ON / OFF" << torchOn;
    if (mEnabled) {
        if (torchOn){
            on();
            if (mtorchMode == Flash){
                timer->start();
            }
        } else {
            off();
            if (mtorchMode == Flash){
                timer->stop();
            }
            mStatus = offBeam;
        }
        setStatus(torchOn, mtorchMode, false);
        mTorchOn = torchOn;
        emit torchOnChanged(torchOn);
    } else {
        qDebug() << "WARNING: Torch not enabled, cannot be turned on";
    }
}

void TorchHelper::toggleTorchMode(){
    qDebug() << "TOGGLE TORCH MODE FLASH / BEAM";
    if (mtorchMode == Beam) {
        setTorchMode(Flash);
    }
    else if (mtorchMode == Flash) {
        setTorchMode(Beam);
    }
}

TorchHelper::Mode TorchHelper::torchMode(){
    qDebug() << "FLASHING MODE";
    return mtorchMode;
}

void  TorchHelper::setTorchMode(Mode mode){
    qDebug() << "SET TORCH MODE" << mode;
    if (mode == Flash){
        if (mStatus == onBeam){
            timer->start();
        }
    }
    else if (mode == Beam) {
        timer->stop();
        if (mStatus == onFlashOff) {
            on();
        }
    }
    setStatus(mTorchOn, mode, false);
    mtorchMode = mode;
    emit torchModeChanged(mode);
}

void TorchHelper::flashEvent(){
    qDebug() << "FLASH EVENT";
    //don't emit any signals if we turn the torch "off" due to a flash event, from an outside view it is still on
    if (mStatus == onFlashOn) {
        setStatus(mTorchOn, mtorchMode, false);
        off();
    }
    else if (mStatus == onFlashOff) {
        setStatus(mTorchOn, mtorchMode, true);
        on();
    }
    //for other states, do nothing
}

void TorchHelper::setStatus(bool torchOn, Mode torchMode, bool flashOn){
    //{offBeam, onBeam, onFlashOn, onFlashOff, offFlash}
    if ( torchOn && (torchMode == Beam) ) {
        mStatus = onBeam;
    }
    if ( torchOn && (torchMode == Flash) && flashOn) {
        mStatus = onFlashOn;
    }
    if ( torchOn && (torchMode == Flash) && !flashOn) {
        mStatus = onFlashOff;
    }
    if ( !torchOn && (torchMode == Beam) ) {
        mStatus = offBeam;
    }
    if ( !torchOn && (torchMode == Flash) ) {
        mStatus = offFlash;
    }
}

bool  TorchHelper::lightOnEnabled(){
    qDebug() << "lightOnEnabled: " << mlightOnEnabled;
    return mlightOnEnabled;
}

void  TorchHelper::setLightOnEnabled(bool lightOnEnabled){
    qDebug() << "SET LIGHTONENABLED" << lightOnEnabled;
    mlightOnEnabled = lightOnEnabled;
    emit lightOnEnabledChanged(lightOnEnabled);
}

int TorchHelper::flashRate(){
    qDebug() << "flashRate" <<mFlashRate;
    return mFlashRate;
}

void TorchHelper::setFlashRate(int flashRate) {
    qDebug() << "SET FLASHRATE" << flashRate;
    mFlashRate = flashRate;
    emit flashRateChanged(flashRate);
    if (timer) {
        timer->setInterval(flashRate);
    }
}

void TorchHelper::on()
{
    qDebug() << "TorchHelper: on() called 1";
    QtAndroid::androidActivity().callMethod<void>("on");
    qDebug() << "TorchHelper: on() called 2";
}

void TorchHelper::off()
{
    qDebug() << "TorchHelper: off() called 1";
    QtAndroid::androidActivity().callMethod<void>("off");
    qDebug() << "TorchHelper: off() called 2";
}

