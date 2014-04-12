/* ----------------------------------------------------------------------
.context DayCreate
.category Day-Field-Windows
BOOL DayCreate ( HWND  hwnd, MPARAM mp1, MPARAM mp2 )

Description: 
     This procedure creates a WC_ENTRYFIELD window that will then be
subclassed to provide the error checking of the field.

Parameter     Description
-------------------------------------------------------------------------
hwnd          a 32 bit pointer for the window this message was sent to

mp1, mp2      see WM_CREATE

Returns: 

Comments: 

References: 

See Also: WM_CREATE, DayWinProc, DaySubWinProc, WinSubclassWindow
.ref WM_CREATE, DayWinProc, DaySubWinProc, WinSubclassWindow

Development History: 
  Date         Programmer          Description of modification   
  07/20/1989   Paul Montgomery     Initial development           
-------------------------------------------------------------------- */

#define INCL_PM
#define INCL_DOSMODULEMGR
#include <os2.h>

#include "day.h"

#include "daysubpr.h"

BOOL DayCreate ( HWND  hwnd, MPARAM mp1, MPARAM mp2 )
   {
   HPS hps;
   FONTMETRICS fm;
   PCREATESTRUCT pcs;
   SEL           sel;
   PDAYINFO      pdayi;
   HMODULE       hmod;
   PFNWP         pfentry;
   SHORT         xchar, ychar;
   CHAR          fname[4];

   // the "DAYFIELD" class needs some window specific data so we create a
   // segment that we hang off of the hwnd.
   DosAllocSeg(sizeof(DAYINFO), 
       &sel,                    
       0);                      
   pdayi = MAKEP(sel, 0);       

   WinSetWindowULong(hwnd,PDAYI_OFFSET,(ULONG)pdayi);

   // part of the data we need is the handle for the DLL that this proc
   // was loaded from.
   DosLoadModule(fname, sizeof(fname), MODNAME, &hmod);             
   WinSetWindowULong(hwnd,DAYHMOD_OFFSET,(ULONG)hmod);

   // figure out what it is we are supposed to look like and use the parms
   // in the creation of the WC_ENTRYFIELD
   pcs = (PCREATESTRUCT)mp2;

   // get the sizes of the character used in this window
   hps = WinGetPS ( hwnd );
   GpiQueryFontMetrics ( hps, (LONG) sizeof ( fm ), &fm );
   ychar = (SHORT) fm.lMaxBaselineExt;
   xchar = (SHORT) fm.lAveCharWidth;
   WinReleasePS ( hps );

   // the WC_ENTRYFIELD if it is of style ES_MARGIN offsets itself and
   // draws a border.  the offsets below allow this window to position 
   // itself and the WC_ENTRYFIELD so that they are where the user really
   // want them to be.

   pdayi->xoffset = (pcs->flStyle & ES_MARGIN )? xchar/2:0;
   pdayi->yoffset = (pcs->flStyle & ES_MARGIN )? ychar/4:0;
   pdayi->flStyle = pcs->flStyle;

   // create the WC_ENTRYFIELD window
   pdayi->hwndEntry = WinCreateWindow ( hwnd,
                     WC_ENTRYFIELD,
                     pcs->pszText,
                     pcs->flStyle,
                     0,0,     // relative to this window
                     pcs->cx,
                     pcs->cy,
                     pcs->hwndOwner,
                     pcs->hwndInsertBehind,
                     pcs->id,
                     pcs->pCtlData,
                     pcs->pPresParams);

   // subclass the WC_ENTRYFIELD window to do the filtering

   pfentry = WinSubclassWindow ( pdayi->hwndEntry, (PFNWP)DaySubWinProc );
   WinSetWindowULong(pdayi->hwndEntry,QWL_USER,(ULONG)pfentry);

   return FALSE;
}
