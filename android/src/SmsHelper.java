package org.flyingsheep.landed;

import org.qtproject.qt5.android.bindings.QtApplication;
import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.telephony.SmsManager;
import android.util.Log;

//Thanks to the following sites for hints on how to send SMS from Android / Android on Qt
//http://blog.qt.io/blog/2013/12/12/implementing-in-app-purchase-on-android/
//http://stackoverflow.com/questions/12783476/sendtextmessagephonenumber-null-message-null-null-always-returns-success
//https://mobiforge.com/design-development/sms-messaging-android
//https://github.com/novoda/android-demos/blob/master/sms/src/main/java/com/novoda/sms/SMS.java
//http://stackoverflow.com/questions/20895982/how-to-call-non-static-java-method-in-qtactivity-from-c-qt

public class SmsHelper {

    public void sendSMS(String phoneNumber, String message, LandedActivity landed)
    {
        Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS called");

        String SENT = "SMS_SENT";
        String DELIVERED = "SMS_DELIVERED";

        PendingIntent sentPI = PendingIntent.getBroadcast(landed, 0,new Intent(SENT), 0);
        PendingIntent deliveredPI = PendingIntent.getBroadcast(landed, 0, new Intent(DELIVERED), 0);

        //---when the SMS has been sent---
        landed.registerReceiver(new BroadcastReceiver(){
            @Override
            public void onReceive(Context arg0, Intent arg1) {
                Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS, SENT Receiver");
                switch (getResultCode())
                {
                    case Activity.RESULT_OK:
                        LandedActivity.smsSent("SMS sent");
                        break;
                    case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                        LandedActivity.smsSent("Generic failure");
                        break;
                    case SmsManager.RESULT_ERROR_NO_SERVICE:
                        LandedActivity.smsSent("No service");
                        break;
                    case SmsManager.RESULT_ERROR_NULL_PDU:
                        LandedActivity.smsSent("Null PDU");
                        break;
                    case SmsManager.RESULT_ERROR_RADIO_OFF:
                        LandedActivity.smsSent("Radio off");
                        break;
                }
            }
        }, new IntentFilter(SENT));
        //---when the SMS has been delivered---
        landed.registerReceiver(new BroadcastReceiver(){
            @Override
            public void onReceive(Context arg0, Intent arg1) {
                Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS, DELIVERED Receiver");
                switch (getResultCode())
                {
                    case Activity.RESULT_OK:
                        LandedActivity.smsDelivered("SMS delivered");
                        break;
                    case Activity.RESULT_CANCELED:
                        LandedActivity.smsDelivered("SMS not delivered");
                        break;
                }
            }
        }, new IntentFilter(DELIVERED));

        SmsManager sms = SmsManager.getDefault();
        sms.sendTextMessage(phoneNumber, null, message, sentPI, deliveredPI);

        Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS ended");

    }
}

