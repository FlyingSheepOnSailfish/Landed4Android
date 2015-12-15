package org.flyingsheep.landed.landed29;

//This structure will be filled by ContactsHelper.java, and passed via JNI back to C++
public class Contact {

    public String contactId;
    public String displayLabel;
    public String firstName;
    public String lastName;
    public String phoneNumber;
    public String phoneNumbers[];
    public int phoneNumbersCount;

}

