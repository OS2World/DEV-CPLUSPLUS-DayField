/* ----------------------------------------------------------------------
.context RegisterDayFieldClass
.category Day-Field-Windows
BOOL APIENTRY RegisterDayFieldClass ( HAB hab );

Description: 
     This procedure is called by the application wishing to create a
Day Field.  It makes a WinRegisterClass call with the proper
parms for this class of window.  The application then does a
WinCreateStdWindow on the class name "ANTFIELD".

Parameter     Description
-------------------------------------------------------------------------
hab           a 32 bit handle to the anchor block for the application.

Returns: 
     The status of the WinRegisterClass call.

Comments: 

References: 

See Also: 
.ref 

Development History: 
  Date         Programmer          Description of modification   
  05/31/1989   Paul Montgomery     Initial development           
-------------------------------------------------------------------- */

#define INCL_PM
#include <os2.h>

#include "day.h"
#include "DayWinPr.h"

BOOL APIENTRY RegisterDayFieldClass ( HAB hab )
{
   return WinRegisterClass( hab, MODNAME, DayWinProc,
                            0L, DATASIZE);
}
