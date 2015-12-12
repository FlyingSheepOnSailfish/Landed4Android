package org.flyingsheep.landed.landed29;

import org.qtproject.qt5.android.bindings.QtApplication;
import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.provider.ContactsContract.Contacts;
import android.os.AsyncTask;
import android.util.Log;

public class ContactsHelper {

    public ContactsHelper()
    {
        Log.d(QtApplication.QtTAG, "ContactsHelper constructor!!!");
    }

    //supporting functions
    //TODO: Move to a helper class? could be static methods
    private boolean hasPhoneNumber(Cursor contactCursor) {
        if (Integer.parseInt(contactCursor.getString(contactCursor.getColumnIndex(Contacts.HAS_PHONE_NUMBER))) > 0) {
            return true;
        } else {
            return false;
        }
    }
    private Uri deduplicateQuery(Uri uri) {
        return uri.buildUpon()
                .appendQueryParameter(ContactsContract.REMOVE_DUPLICATE_ENTRIES, "1")
                .build();
    }
    private String getColumnValue(Cursor cur, String col) {
        return cur.getString(cur.getColumnIndex(col));
    }
    //supporting functions

    //Get the contacts in the background, returning control to GUI immediately while contacts are still being listed
    public void getContactsAsync(final LandedActivity landed) {
        new AsyncTask<Void, Void, Void>()
            {
                @Override
                protected void onPreExecute()
                {
                }

                @Override
                protected Void doInBackground(Void... params)
                {
                    getContacts(landed);
                    return null;
                }

                @Override
                protected void onPostExecute(Void result)
                {
                    Log.d(QtApplication.QtTAG, "ContactsHelper.getContactsAsync.onPostExecute ");
 //TODO: emit a call / signal back to C++ to indicate all contacts sent
                    landed.allContactsSent();
                }
        }.execute((Void[]) null);

    }

    //This example code retrieves the contacts successfully!
    private void getContacts(LandedActivity landed) {
        ContentResolver cr = landed.getContentResolver();
        Cursor contactCursor = cr.query(Contacts.CONTENT_URI, null, null, null, null);
        int count = contactCursor.getCount();
        Log.d(QtApplication.QtTAG, "ContactsHelper contacts found: " + count);
        if (count > 0) {
            while (contactCursor.moveToNext()) {
                String id = getColumnValue(contactCursor, Contacts._ID);
                String name = getColumnValue(contactCursor, Contacts.DISPLAY_NAME);
                Log.d(QtApplication.QtTAG, "ContactsHelper contact: " + name + ", id: " + id );
                if (hasPhoneNumber(contactCursor)) {
                    int index = contactCursor.getPosition() + 1;
                    landed.contactFound(index, count, name, getNumbersForContact(id, cr)); //signal back to C++ contact has been found
                }
            }
            contactCursor.close();
        }
    }

    //return an array of numbers for the contact
    private String[] getNumbersForContact(String id, ContentResolver cr) {
        //ensure numbers returned are deduplicated
        Uri phoneUri = deduplicateQuery(Phone.CONTENT_URI);
        Cursor phoneCursor = cr.query(phoneUri,
            null,
            Phone.CONTACT_ID + " = ?",
            new String[] {id},
            null);
        String[] numbers = new String[phoneCursor.getCount()];
        while (phoneCursor.moveToNext()) {
            String phoneNumber = getColumnValue(phoneCursor, Phone.NUMBER);
            String numType = getColumnValue(phoneCursor, Phone.TYPE);
            Log.d(QtApplication.QtTAG,"Phone number: " + phoneNumber + " type: " + numType);
            numbers[phoneCursor.getPosition()] = phoneNumber;
        }
        phoneCursor.close();
        return numbers;
    }

}


