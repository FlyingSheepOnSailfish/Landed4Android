# Landed4Android
A port of the paragliding app Landed from SailfishOS to Android

landed

An app for paraglider pilots to send GPS coords via SMS to a recovery team using a few button pushes only.

Development / Migration Status:

landed29 is the current "work-in-progress" port form SailfishOS to Android. Most things are in place and even work, but lots of cleaning up is still required, and will take place over the next few weeks.

landed28 is the latest version for Sailfish Qt5, and was previously the lead version.

landed25 is the fully functional version for Harmattan. It was the last major verison on that platform.

Follow progress on my blog: http://flyingsheeponsailfish.blogspot.ch/

Purpose:

The Landed app is intended for a paraglider pilot flying cross-country to easily transmit his GPS coordinates via SMS to a recovery team.

The app is intended to be used "in action" with a bare minimum of button presses. The thinking behind this is that the pilot may be in the best case tired, and in the worse case hanging from a tree! So the app has to be very simple to use, with any "hard work" done beforehand.

To achieve this we use prefilled SMS templates. On landing the Pilot just choses the most appropriate template, and presses send. The GPS coordinates are automatically added to the placeholders in the template, and an SMS is sent to the contact associated with the template.

So there is no cutting and pasting or copying of GPS co-ordinates with all the possibilities of transposing digits, and no scrolling through long lists of contacts.

The templates and associated contacts are setup in the sidekick app LandedSettings, more of which below.

Data Model.

The top level entity is "Area", which equates to an country or region where I frequently fly (e.g. Switzerland, Greece, South Africa).

Each Area can contain multiple "Sites". i.e. recognised Takeoffs and Landings sites. These are used to give reference to GPS coords (e..g 10km SE of Piketberg Takeoff.

Each Area is also the parent of two SMS Templates, one normal Recovery SMS Template, and one emergency "Help me!" SMS Template. A Template is the text body that will be sent.

Each Template is the the parent of several "Tags": these are placeholders that will be replaced by values from the GPS Location (e.g. Latittude, Longitude).

Each Template is the parent of several "Contacts", one of which is the default.

All Data is stored in a json text file queried by jsonpath. This can be editted with any text editor or visual json editor.

Using Landed:

When Landed starts, it automatically fires up the GPS. When the location is found, the nearest "Group" is selected, and the SMS Buttons are activated, allowing the sending of either a normal Recovery SMS, or an emergency "Help Me!" SMS.

The user can: 1) change the "Area" by clicking on the "Area" header between the GPS Display and the SMS buttons. 2) edit the SMS text to add more information to the default text. 3) change the preselected contact, by pressing on the displayed contact. This opens a Contact Selection page with three tabs: 3.1) Favourite Contacts: from the LocalStorageDb 3.2) A Dialer, allowing a number to be dialed. 3.3.) PhoneContactPage: allowing the phones contacts pages to be selected (this bit is not fully ported on Sailfish, coming soon). 4) On the Emergency SMS a torch is available to signal with beam or flash (e.g. to a helicopter).

Safety / Legal:

We give no warranty or guarantee that this app will actually work. If you are in a new location, please please test it with your recovery. Check that the coords transmitted make sense, and you and your recovery agree that you know where you are! I have not been able to test this app "all over the world", so I cannot totally eliminate the possibility that there maybe an error in the coordinates algorithm!

For the app to work you will need both GPS reception, and Cell-phone signal
