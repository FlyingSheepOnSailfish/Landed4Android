import QtQuick 2.0
import SmsHelper 1.0

SmsHelper {

//TODO: consider which of these signals we really want
//to forward to our GUI
//onStateMsg is the signal generated by our original Harmattan / Sailfish Telepathy backend
//onSmsSent / onSmsDelivered are the "native" signals from our Andorid backend

//perhaps it would be better to emit one signal messageState
//with status in the msgState
//a) sending
//b) sent
//c) delivered
//e) error
//the SMS Gui can then respond accordingly

//the signal should have 2 params (int state, string errorMsg)
//the state should be in an enum,

    signal messageState(string msgState)

    onStateMsg: {
        var stateTxt = msgstate.toString()
        console.log("QML SmsHelper: onStateMsg: " + stateTxt);
        messageState(msgstate.toString());
    }

    onSmsSent: {
        console.log("QML SmsHelper: onSmsSent");
        messageState(result);
    }

    onSmsDelivered: {
        console.log("QML SmsHelper: onSmsDelivered");
    }

    onErrorMsg: {
      console.log("QML SmsHelper: onErrorMsg");
    }

}



