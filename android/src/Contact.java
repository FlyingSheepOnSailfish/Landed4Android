package org.flyingsheep.landed;

//This structure will be filled by ContactsHelper.java, and passed via JNI back to C++
public class Contact {

    public String contactId;
    public ContactDisplayLabel displayLabel;
    public ContactName name;
    public String phoneNumber;
    public ContactPhoneNumber phoneNumbers[];
    public int phoneNumbersCount;

}

