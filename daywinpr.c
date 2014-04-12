/* ----------------------------------------------------------------------
.context DayWinProc
.category Day-Field-Windows
MRESULT EXPENTRY DayWinProc ( HWND   hwnd,
                              USHORT msg,
                              MPARAM mp1,
                              MPARAM mp2 );

Description:
     This procedure is the Window Procedure for the Field class window.

Parameter     Description
-------------------------------------------------------------------------
hwnd          A handle (32 bit) for the window to which the message is
              addressed.

msg           A USHORT identifying the type of message that is being
              received.

mp1           Message type specific 32 bit value.

mp2           Message type specific 32 bit value.



Returns:  
     a MRESULT: a 32 bit pointer to a void data type

Comments: 
     The DayFIELD class is used to allow the user to enter PRIMARY or
SECONDARY to
an entry field.  All other values are not allowed or cause the focus to
shift to other windows.  This is done by subclassing the default
WC_ENTRYFIELD window class and only passing the allowed WM_CHAR msgs.
All messages that are meant for the subclassed WC_ENTRYFIELD window are
passed on to it.  All other messages are handled here.

References: 
     Charles Petzolds Programming the OS/2 Presentation Manager.

See Also:  DayCreate, DaySubWinProc, WinSubclassWindow
.ref DayCreate, DaySubWinProc, WinSubclassWindow

Development History: 
  Date         Programmer          Description of modification   
  07/11/1989   Paul Montgomery     Initial development           
-------------------------------------------------------------------- */

#define INCL_PM
#define INCL_DOSMODULEMGR
#include <os2.h>

#include "day.h"
#include "daycrate.h"

MRESULT EXPENTRY DayWinProc ( HPS hwnd, USHORT msg, MPARAM mp1, MPARAM mp2 )
   {              
   PDAYINFO   pdayi;
   PSWP       pswp;
   HPS        hps;

   pdayi = (PDAYINFO)WinQueryWindowULong(hwnd, PDAYI_OFFSET);
   switch ( msg )
      {
      case WM_PAINT:
         WinSetWindowPos(pdayi->hwndEntry, HWND_TOP,
            pdayi->xoffset,
            pdayi->yoffset,
            0,
            0,
            SWP_ACTIVATE | SWP_MOVE | SWP_SHOW); /* flags  */
         hps = WinBeginPaint(hwnd, NULL, NULL);
         WinEndPaint(hps);
         return 0;
         break;

      case WM_CREATE:
         return DayCreate(hwnd, mp1, mp2);
         break;

      case EM_CLEAR:
      case EM_CUT:
      case EM_COPY:
      case EM_PASTE:
      case EM_QUERYCHANGED:
      case EM_QUERYFIRSTCHAR:
      case EM_QUERYSEL:
      case EM_SETFIRSTCHAR:
      case EM_SETSEL:
      case EM_SETTEXTLIMIT:
      case WM_ACTIVATE:
      case WM_BUTTON1DOWN:
      case WM_BUTTON2DOWN:
      case WM_BUTTON3DOWN:
      case WM_BUTTON1DBLCLK:
      case WM_BUTTON1UP:
      case WM_SETFOCUS:
      case WM_FOCUSCHANGE:
      case WM_HITTEST:
      case WM_QUERYWINDOWPARAMS:
      case WM_SETWINDOWPARAMS:
      case WM_SETSELECTION:
      case WM_TIMER:
      case WM_ENABLE:
      case WM_MOUSEMOVE:
      case WM_CHAR:
      case WM_QUERYDLGCODE:
         return WinSendMsg(pdayi->hwndEntry, msg, mp1, mp2);
         break;

      case WM_ADJUSTWINDOWPOS:
         pswp = (PSWP)mp1;
         pswp->x -= pdayi->xoffset;
         pswp->y -= pdayi->yoffset;
         pswp->cx += pdayi->xoffset * 2;
         pswp->cy += pdayi->yoffset * 2;
         return TRUE;
         break;

      case WM_CONTROL:
         return WinSendMsg(WinQueryWindow(hwnd, QW_PARENT,FALSE),
                           msg, mp1, mp2);
         break;

      case WM_DESTROY:
         DosFreeModule(WinQueryWindowULong(hwnd, DAYHMOD_OFFSET));
         DosFreeSeg(SELECTOROF(pdayi));
         return 0;
         break;

      default:
         return WinDefWindowProc ( hwnd, msg, mp1, mp2 );
      }
   return 0L;
   }

