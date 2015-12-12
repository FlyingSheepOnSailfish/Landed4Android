#ifndef SMSHELPER_H
#define SMSHELPER_H

#include <QObject>

class SmsHelper : public QObject
{
    Q_OBJECT

public:
    explicit SmsHelper(QObject *parent = 0);
    ~SmsHelper();
    Q_INVOKABLE void sendSMS(const QString &contactIdentifier, const QString &message);

    static SmsHelper *instance() { return m_instance; }

    enum MessageState { Pending, Sent, Delivered, Error };
    Q_ENUM(MessageState)

signals:

    //TODO: SailfishOS TelepathyHelper has these 2 signals below
    //in next version, make handling consistent between sailfish and android!
    void stateMsg(const MessageState &msgstate);
    void errorMsg(const QString &errormsg);

    void smsSent(const QString &result);
    void smsDelivered(const QString &result);

private Q_SLOTS:
    void onSendMessageFinished(const QString &result);

private:
    static SmsHelper *m_instance;
};

#endif // SMSHELPER_H
