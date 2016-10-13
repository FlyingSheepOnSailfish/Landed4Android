package org.flyingsheep.landed;

import android.util.Log;
import org.qtproject.qt5.android.bindings.QtApplication;
import android.telephony.SmsManager;
import android.app.PendingIntent;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.IntentSender;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import java.util.ArrayList;

//Thanks to the following sites for hints on how to send SMS from Android / Android on Qt
//http://blog.qt.io/blog/2013/12/12/implementing-in-app-purchase-on-android/
//http://stackoverflow.com/questions/12783476/sendtextmessagephonenumber-null-message-null-null-always-returns-success
//https://mobiforge.com/design-development/sms-messaging-android
//https://github.com/novoda/android-demos/blob/master/sms/src/main/java/com/novoda/sms/SMS.java
//http://stackoverflow.com/questions/20895982/how-to-call-non-static-java-method-in-qtactivity-from-c-qt

public class SmsHelper {

    private static LandedActivity callingActivity;

    public SmsHelper(LandedActivity callingActivity)
    {
        Log.d(QtApplication.QtTAG, "SmsHelper.java: constructor called");
        this.callingActivity = callingActivity;
    }

    public void sendSMS(String phoneNumber, String message)
    {
        Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS called: nr: " + phoneNumber + ", msg: " + message);

        String SENT = "SMS_SENT";
        String DELIVERED = "SMS_DELIVERED";

        PendingIntent sentPI = PendingIntent.getBroadcast(callingActivity, 0,new Intent(SENT), 0);
        PendingIntent deliveredPI = PendingIntent.getBroadcast(callingActivity, 0, new Intent(DELIVERED), 0);

        //---when the SMS has been sent---
        callingActivity.registerReceiver(new BroadcastReceiver(){
            @Override
            public void onReceive(Context arg0, Intent arg1) {
                Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS, SENT Receiver");
                switch (getResultCode())
                {
                    case Activity.RESULT_OK:
                        LandedActivity.smsSent("SMS sent");
                        break;
                    case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                        LandedActivity.smsSent("Error: Generic failure");
                        break;
                    case SmsManager.RESULT_ERROR_NO_SERVICE:
                        LandedActivity.smsSent("Error: No service");
                        break;
                    case SmsManager.RESULT_ERROR_NULL_PDU:
                        LandedActivity.smsSent("Error: Null PDU");
                        break;
                    case SmsManager.RESULT_ERROR_RADIO_OFF:
                        LandedActivity.smsSent("Error: Radio off");
                        break;
                }
            }
        }, new IntentFilter(SENT));
        //---when the SMS has been delivered---
        callingActivity.registerReceiver(new BroadcastReceiver(){
            @Override
            public void onReceive(Context arg0, Intent arg1) {
                Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS, DELIVERED Receiver");
                switch (getResultCode())
                {
                    case Activity.RESULT_OK:
                        LandedActivity.smsDelivered("SMS delivered");
                        break;
                    case Activity.RESULT_CANCELED:
                        LandedActivity.smsDelivered("Error: SMS not delivered");
                        break;
                }
            }
        }, new IntentFilter(DELIVERED));

        SmsManager sms = SmsManager.getDefault();
        Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS sending ...");

        //The message may likely be longer than 160 chars, which means it must be divided into
        //chunks of 153 chars each, and sent as a multipart message.
        ArrayList<String> parts = sms.divideMessage(message);
        int smsSize = parts.size();
        ArrayList<PendingIntent> sentPIList = new ArrayList<PendingIntent>(smsSize);
        ArrayList<PendingIntent> deliveredPIList = new ArrayList<PendingIntent>(smsSize);

        for (String part: parts)
        {
            Log.d(QtApplication.QtTAG, "SmsHelper.java: msg part: " + part);
            sentPIList.add(sentPI);
            deliveredPIList.add(deliveredPI);
        }

        sms.sendMultipartTextMessage(phoneNumber, null, parts, sentPIList, deliveredPIList);

        //sms.sendTextMessage(phoneNumber, null, message, sentPI, deliveredPI);

        Log.d(QtApplication.QtTAG, "SmsHelper.java: sendSMS ended");
    }

}
