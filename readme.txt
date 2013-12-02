PostWhat WPS Class Example
---------------------------
Version 0.1
2013-01-12
---------------------------

Description
--------------

PostWhat WPS Class Example is a WPS class made by Lars Erdmann.

This class implements yellow sticky notes on WPS as a learning process for SOM/WPS.

This class is derived from the WPAbstract class (which also means it is placing all its content text into OS2.INI ...)

As an additional learning effort Lars also implemented a replacement class for the one created, just changing the coloring from a yellow sticky note to a red sticky note.

There are quite a few things you can learn from this example:

* How to remove and add menu items to an objects menu and tie these to functionality.
* How to add a completely new view to an object (that is none of the icon/structure/tree views but rather a new custom view), how to add this new view to the use list and how to make it show up in the window list.
* How to do some cleanup in OS2.INI on object deletion where WPAbstract does not do the job properly.
* How to do exception handling for a WPS class.
* How FFST (first failure support technology) works to add logging info to the system log (used by the classes to write exception info to the system log)
* How a replacement class works / how you derive one class from another class.
	
Compile Information
--------------------
1) It is based on IBM VisualAge for C. You will need to adjust makefiles to use it with other compilers like WATCOM for example. 
2) It expects the IBM Toolkit to be installed and it expects the SOMBASE environment variable to point into the corresponding Toolkit directory (normally this is OS2TK45\som).
3) It expects SMINCLUDE environment variable to have the default value after Toolkit installation.

	
License
----------
BSD 3 Clause 

Links
--------
http://www.edm2.com/index.php/PostWhat_WPS_Class_Example

Author
-------
Lars Erdmann 

