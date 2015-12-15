package org.flyingsheep.landed.landed29;

import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.util.Log;
import android.content.pm.ActivityInfo;
import android.os.Build.VERSION;

public class LandedActivity extends QtActivity{


    public LandedActivity()
    {
        Log.d(QtApplication.QtTAG, "LandedActivity constructor!!!");
        Log.d(QtApplication.QtTAG, "Android SDK Level: " + android.os.Build.VERSION.SDK_INT);
    }

//TODO: would it be better to pass the "this" references to the constructor methods
//      rather than to the "worker" methods????

    /////////////////////////////////////////////////////////////////////////////////
    // SMS Methods
    /////////////////////////////////////////////////////////////////////////////////

//TODO: do I want to create a new instance of smsHelper everytime sendSMS is called
//      or shall I only create one first time (and reuse)?
//      That would imply smsHelper belongs to class

    public void sendSMS(String phoneNumber, String message)
    {
        Log.d(QtApplication.QtTAG, "LandedActivity.java: sendSMS called");
        SmsHelper smsHelper = new SmsHelper();
        //we pass this to smsHelper so that it can access activity behavour
        smsHelper.sendSMS(phoneNumber, message, this);
        Log.d(QtApplication.QtTAG, "LandedActivity.java: sendSMS ended");
    }

    //These methods will be called from SmsHelper.java once sent / delivered to call back to c++
    protected static native void smsSent(String result);
    protected static native void smsDelivered(String result);

    /////////////////////////////////////////////////////////////////////////////////
    //  Contacts Methods
    /////////////////////////////////////////////////////////////////////////////////

    public void getContactsAsync() {
        ContactsHelper contactsHelper = new ContactsHelper();
        contactsHelper.getContactsAsync(this);
    }

    //This method will be called from ContactsHelper.java once sent / delivered to call back to c++
    //TODO: initially signal per contact, later maybe per block of 30?
    protected static native void contactFound(int index, int count, String name, String[] numbers);
    protected static native void contactFound2(int index, int count, Contact contact);
    protected static native void allContactsSent();

    /////////////////////////////////////////////////////////////////////////////////
    //  Torch Methods
    /////////////////////////////////////////////////////////////////////////////////

    private TorchHelper torchHelper;

    public void initTorch()
    {
        //because there are no callbacks, no need to pass in a reference to "this"

        if (android.os.Build.VERSION.SDK_INT >= 23) {
            torchHelper = new TorchHelperMarshmallow();
        } else {
            torchHelper = new TorchHelperLollipop();
        }

        torchHelper.initTorch(this);
    }

    public void releaseTorch()
    {
        torchHelper.releaseTorch();
    }

    public void on()
    {
        torchHelper.on();
    }

    public void off()
    {
        torchHelper.off();
    }

    /////////////////////////////////////////////////////////////////////////////////
    //  AUI Methods
    /////////////////////////////////////////////////////////////////////////////////

    public void lockPortrait()  {
        setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
    }
}




