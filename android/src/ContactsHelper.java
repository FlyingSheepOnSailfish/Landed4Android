package org.flyingsheep.landed;

import org.qtproject.qt5.android.bindings.QtApplication;
import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.net.Uri;
import android.provider.ContactsContract;
import android.provider.ContactsContract.CommonDataKinds.Phone;
import android.provider.ContactsContract.CommonDataKinds.StructuredName;
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

    private void getContacts(LandedActivity landed) {
        ContentResolver cr = landed.getContentResolver();
        Uri CONTENT_URI = ContactsContract.Contacts.CONTENT_URI;
        //Order by names with leading char = character first (case insensitive), second those starting with a numeral, finally anything else.
        String orderBy =  "CASE"
                        + " WHEN " + Contacts.DISPLAY_NAME + " GLOB '[A-z]*' THEN 'A' || " + Contacts.DISPLAY_NAME
                        + " WHEN " + Contacts.DISPLAY_NAME + " GLOB '[0-9]*' THEN 'B' || " + Contacts.DISPLAY_NAME
                        + " ELSE 'C' || " + Contacts.DISPLAY_NAME
                        + " END COLLATE NOCASE";
        Cursor contactCursor = cr.query(CONTENT_URI, null, null, null, orderBy);
        int count = contactCursor.getCount();
        Log.d(QtApplication.QtTAG, "ContactsHelper.java contacts found: " + count);
        if (count > 0) {
            while (contactCursor.moveToNext()) {
                String id = getColumnValue(contactCursor, Contacts._ID);
                String name = getColumnValue(contactCursor, Contacts.DISPLAY_NAME);
                Log.d(QtApplication.QtTAG, "ContactsHelper.java contact: " + name + ", id: " + id );
                if (hasPhoneNumber(contactCursor)) {
                    int index = contactCursor.getPosition() + 1;
                    Contact contact = new Contact();
                    contact.contactId = getColumnValue(contactCursor, Contacts._ID);
                    contact.displayLabel = setDisplayLabel(getColumnValue(contactCursor, Contacts.DISPLAY_NAME));
                    contact.name = setNames(id, cr);
                    //Log.d(QtApplication.QtTAG, "ContactsHelper.java: firstName: " + contact.firstName + ", lastName: " + contact.lastName);
                    contact.phoneNumbers = getNumbersForContact(id, cr);
                    contact.phoneNumbersCount =  contact.phoneNumbers.length;
                    contact.phoneNumber = contact.phoneNumbers[0];
                    //new call, return data structure "contact" to C++
                    landed.contactFound(index, count, contact);
                }
            }
            contactCursor.close();
        }
    }

    private ContactDisplayLabel setDisplayLabel(String label) {
        ContactDisplayLabel contactDisplayLabel = new ContactDisplayLabel();
        contactDisplayLabel.label = label;
        return contactDisplayLabel;
    }

    private ContactName setNames(String id, ContentResolver cr) {
        ContactName contactName = new ContactName();
        //get the first and last names from a separate table
        String whereName = ContactsContract.Data.CONTACT_ID + " = ? AND " + ContactsContract.Data.MIMETYPE + " = ?";
        String[] whereNameParams = new String[]{id, ContactsContract.CommonDataKinds.StructuredName.CONTENT_ITEM_TYPE};
        Cursor nameCur = cr.query(ContactsContract.Data.CONTENT_URI, null, whereName, whereNameParams, ContactsContract.CommonDataKinds.StructuredName.GIVEN_NAME);
        while (nameCur.moveToNext()) {
            contactName.firstName  = nameCur.getString(nameCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredName.GIVEN_NAME));
            contactName.lastName = nameCur.getString(nameCur.getColumnIndex(ContactsContract.CommonDataKinds.StructuredName.FAMILY_NAME));
            //Log.d(QtApplication.QtTAG, "ContactsHelper.java: firstName: " + contact.firstName + ", lastName: " + contact.lastName);
        }
        nameCur.close();
        return contactName;
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
            //Log.d(QtApplication.QtTAG,"Phone number: " + phoneNumber + " type: " + numType);
            numbers[phoneCursor.getPosition()] = phoneNumber;
        }
        phoneCursor.close();
        return numbers;
    }

}


