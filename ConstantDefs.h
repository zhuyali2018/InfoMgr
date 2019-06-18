//#define VERSION 3.50, By Yali Zhu, Features Undo, Move among siblings and save order etc
//#define VERSION 3.51, corrected bugs in Detail loading
/* modified parts on Jan 27, 2005:
	CDetailFile::LoadDetails();
	CDetailFile::ReadString();
*/
//#define VERSION "3.61" //added Redo, input right pane
//#define VERSION "3.62" //added webbrowser on the right pane
//#define VERSION "3.63"	// added Collapse button
//#define VERSION "3.64"	// added Rich Text Editor
//#define VERSION "3.65"	//added accept files dropped
//#define VERSION "3.65.1"	//fixed a drop bug
//#define VERSION "3.66"	//Display picture to fit the window
//#define VERSION "3.66.1"	// can brose UNC address starting with "\\"
//#define VERSION "3.67"	// added playmode setting in menu, so that the movie won't play if it is not in play mode
						// also added Insert On One File drop menu item
//#define VERSION "3.67.1"	// play video in the right pane
//#define VERSION "3.67.2"	// added support for display of https protocal
//#define VERSION "3.67.3"    // added a missed else
//#define VERSION "3.68"      // make shift key insert siblings and control key insert child
//#define VERSION "3.68.1"    // make Edit dialog box 200 pixels wider and higher
//#define VERSION "3.68.2"	// the control key interfier with ctrl-z undo, so, changed it to insert key for inserting a child
//#define VERSION "3.68.3"	//do not reload a web page when resizing the right pane
//#define VERSION "3.69"		// add menu item for read only mode
//#define VERSION "3.70"		// Direct drop files on a node with ALT key pressed
//#define VERSION "4.00"		// added support for relative path for jpg and movie files
//#define VERSION "4.01"		// Fixed bug for displaying rich text
//#define VERSION "4.02"		// Fixed bug for Retrieving and setting rich text
//#define VERSION "4.03"		// Make pics dropped on EditDialog a relative path
//#define VERSION "4.04"		// Fixed the detail loading problem and extra CF\CR adding problem
//#define VERSION "4.05"			// modified to support .png picture file
//#define VERSION "4.06"		// Added support for .gif file, and fixed the line feed/return problem
//#define VERSION "4.07"			// added support for .mp4 and all other file with relative path
//#define VERSION "4.08"		//modified to fit windows 7: 1) adjust the Edit Dialog field name position
							//nothing to be modified, just run it as administrator to so that temp file can be created!
							// draggging resizing keep getting jpg file not found, fixed that!
//#define VERSION "4.09"      //Temp file webpage.htm will be created in current folder instead of c:\ so that it does not have to be launched as administrator
//#define VERSION "4.10"      //image accessing not working for ::FOLDER fixed, now work for both ::FOLDER and ::\FOLDER
#define VERSION "4.11"      //AutoPopulate ::\\images2016\\

#ifdef UNICODE
#define VERSIONNAME "Unicode"
#else
#define VERSIONNAME "Ascii"
#endif