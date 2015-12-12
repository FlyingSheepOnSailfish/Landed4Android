#ifndef TORCHHELPER_H
#define TORCHHELPER_H

#include <QObject>
#include <QTimer>

class TorchHelper: public QObject
{
    Q_OBJECT
    Q_ENUMS(Status)
    Q_ENUMS(Mode)

public:
    explicit TorchHelper(QObject *parent = 0);
    ~TorchHelper();

    enum Status { offBeam, onBeam, onFlashOn, onFlashOff, offFlash };
    enum Mode { Beam, Flash };
    //The property "enabled" was used by SailfishOS to allow / disallow LED access depending on Permissions Plugin
    //import org.nemomobile.policy 1.0
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    bool enabled();
    //The property "lightOnEnabled" causes the then torch to immediately turn on, when torch is enabled
    //if false it waits for a toggleTorchOnOff() call from QML
    Q_PROPERTY(bool lightOnEnabled READ lightOnEnabled WRITE setLightOnEnabled NOTIFY lightOnEnabledChanged)
    bool lightOnEnabled();
    Q_PROPERTY(bool torchOn READ torchOn WRITE setTorchOn NOTIFY torchOnChanged)
    bool torchOn();
    Q_PROPERTY(Mode torchMode READ torchMode WRITE setTorchMode NOTIFY torchModeChanged)
    Mode torchMode();
    Q_PROPERTY(int flashRate READ flashRate WRITE setFlashRate NOTIFY flashRateChanged)
    int flashRate();


    Q_INVOKABLE void toggleTorchOnOff();
    Q_INVOKABLE void toggleTorchMode(); // toggle between Beam and Torch


signals:
    void enabledChanged(bool enabled);
    void lightOnEnabledChanged(bool lightOnEnabled);
    void torchOnChanged(bool on);
    void torchModeChanged(Mode mode);
    void flashRateChanged(int flashRate);

protected slots:
    void flashEvent();

private:
    void initTorch();
    void initTimer();
    void releaseTorch();
    void releaseTimer();
    void on();
    void off();
    void setEnabled(bool enabled);
    void setLightOnEnabled(bool lightOnEnabled);
    void setTorchOn(bool torchOn);
    void setTorchMode(Mode mode);
    void setFlashRate(int flashRate);
    void setStatus(bool torchOn, Mode torchMode, bool flashOn);

    bool mEnabled;
    bool mlightOnEnabled;
    bool mTorchOn; // true = on
    Mode mtorchMode; // true = on, i.e if the torch is active, it will flash.
    int mFlashRate;
    Status mStatus;
//TODO: consider, should the timer be here (consistent with Gstreamer code, or in java?)
    QTimer *timer;

};

#endif // TORCHHELPER_H
