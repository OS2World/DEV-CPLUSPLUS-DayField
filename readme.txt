This collection of code is a DAY of the WEEK type of subclassed WC_ENTRYFIELD
control.  It can be used in dialog boxes or as a stand alone control window in
an application.  In both case's you need to register the class in your process
through the use of the RegisterDayFieldClass call.  The "TEST" code is an
example of how you use the class from an application as a control window.

To build the DLL you use BLD.CMD enter  "BLD ?" to see what the options are 
to the BLD command file.  It does a make on "DAYFIELD".  Do a make on the file
"test" to compile the example code.

The file dayfield.hlp is a Quickhelp format database.  It is built by doing a
make on "MAKEHELP"

If you have any questions/comments I can be reached on Compuserve as
Paul Montgomery  71500,3525

For all you c++ people, lets see how you would do this same thing using c++.


Of course, if you use this code elsewhere, please at least acknowledge that it
came from me, other than that, its yours to play with.

Oh yeah, I am assuming that you know where to put .DLL files on your system 
and that you have MSC 5.1.  Good luck.

