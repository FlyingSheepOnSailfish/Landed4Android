package org.flyingsheep.landed;

import org.qtproject.qt5.android.bindings.QtApplication;
import org.qtproject.qt5.android.bindings.QtActivity;
import android.content.pm.ActivityInfo;
import android.util.Log;
import android.os.Bundle;
import android.os.Build.VERSION;
import android.os.Build.VERSION_CODES;
import android.content.pm.PackageManager;
import android.Manifest;

/*
This version works on both Android 5.0 (Samsung Galaxy Note 3) and Android 7 (Nexus 6P)
It uses Non static versions of the methods sendSMS() - both in LandedActivity and SmsHelper classes.
*/

public class LandedActivity extends QtActivity{

    private SmsHelper smsHelper;

    private static final String[] REQUIRED_PERMS={
      //Manifest.permission.ACCESS_FINE_LOCATION,
      Manifest.permission.SEND_SMS
    };

    public LandedActivity()
    {
        Log.d(QtApplication.QtTAG, "LandedActivity.java: constructor called");
    }

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        //Ensure that we have the permissions required to run the app
        if (requiredPermissionsAreGranted()) {
            Log.d(QtApplication.QtTAG, "LandedActivity: All required 'Dangerous' permissions available on startup");
            smsHelper = new SmsHelper(this);
        } else {
            Log.d(QtApplication.QtTAG, "LandedActivity: One or more required Dangerous permissions missing on startup");
            //TODO: do something to request the missing required permissions.
        }
    }

    private boolean requiredPermissionsAreGranted() {
        int hits = 0;
        for (String requiredPermission: REQUIRED_PERMS)
        {
            if (dangerousPermissionIsGranted(requiredPermission)) {
                hits++;
            }
        }
        if (hits == REQUIRED_PERMS.length) {
            return true;
        } else {
            return false;
        }
    }

    private boolean dangerousPermissionIsGranted(String dangerousPermission) {
        //from Marshmallow onwards, we need to explicitly check for "dangerous" permissions like SEND_SM
        if (VERSION.SDK_INT >= VERSION_CODES.M) {
            int permissionCheck = checkSelfPermission(dangerousPermission);
            if ( permissionCheck == PackageManager.PERMISSION_GRANTED) {
                Log.d(QtApplication.QtTAG, "LandedActivity: " + dangerousPermission + " is granted");
                return true;
            } else {
                Log.d(QtApplication.QtTAG, "LandedActivity: " + dangerousPermission + " NOT granted");
                return false;
            }
        } else {
            Log.d(QtApplication.QtTAG, "LandedActivity: Android version prior to Marshmallow");
            return true;
        }
    }

    /////////////////////////////////////////////////////////////////////////////////
    // SMS Methods
    /////////////////////////////////////////////////////////////////////////////////

    public static native void smsSent(String result);
    public static native void smsDelivered(String result);

    public void sendSMS(String phoneNumber, String message)
    {
        Log.d(QtApplication.QtTAG, "LandedActivity.java: sendSMS called");

        smsHelper.sendSMS(phoneNumber, message);

        Log.d(QtApplication.QtTAG, "LandedActivity.java: sendSMS ended");
    }

    /////////////////////////////////////////////////////////////////////////////////
    //  Contacts Methods
    /////////////////////////////////////////////////////////////////////////////////

    public void getContactsAsync() {
        ContactsHelper contactsHelper = new ContactsHelper();
        contactsHelper.getContactsAsync(this);
    }

    //This method will be called from ContactsHelper.java once sent / delivered to call back to c++
    //TODO: initially signal per contact, later maybe per block of 30?
    protected static native void contactFound(int index, int count, Contact contact);
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





