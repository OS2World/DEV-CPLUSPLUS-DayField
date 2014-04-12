/* ----------------------------------------------------------------------
.context DaySubWinProc
.category Day-Field-Windows
MRESULT EXPENTRY DaySubWinProc ( HWND   hwnd,
                                USHORT msg,
                                MPARAM mp1,
                                MPARAM mp2 );

Description:
     This procedure is the Window Procedure used to Subclass the
WC_ENTRYFIELD window.

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
     The DAYFIELD class is used to allow the user to enter Monday -
Sunday in an entry field.  All other values are not allowed or cause
the focus to shift to other windows.  This is done by subclassing the
default WC_ENTRYFIELD window class and only passing the allowed WM_CHAR
msgs. This procedure is the procedure that does the filtering of the
WM_CHAR messages.

References: 
     Charles Petzolds Programming the OS/2 Presentation Manager.

See Also: WinSubclassWindow
.ref  WinSubclassWindow

Development History: 
  Date         Programmer          Description of modification   
  07/11/1989   Paul Montgomery     Initial development           
-------------------------------------------------------------------- */
#define INCL_PM
#include <os2.h>

#include "day.h"
#include "crmenu.h"

MRESULT EXPENTRY DaySubWinProc( HPS hwnd,
                               USHORT msg,
                               MPARAM mp1,
                               MPARAM mp2 )
   {
   WNDPARAMS wp;
   CHAR      buf[12];  // size of largest text + room for  '\0' and '~'
   HWND      hMenu;
   USHORT    item;
   BOOL      move;
   INT       i;
   PFNWP     pfentry;
   HWND      parent;
   HMODULE   hmod;
   RECTL     rc;

   pfentry = (PFNWP) WinQueryWindowULong(hwnd, QWL_USER); 
   switch ( msg )
      {
      case WM_COMMAND:
         if (COMMANDMSG(&msg)->source != CMDSRC_MENU)
            {
            return ((pfentry)(hwnd, msg, mp1, mp2));
            }
         // a message from the menu window
         item = COMMANDMSG(&msg)->cmd;
         hMenu = WinWindowFromID(hwnd,FID_MENU);

         // get the selected text
         WinSendMsg(hMenu, MM_QUERYITEMTEXT,
                    MPFROM2SHORT(item, (USHORT)sizeof(buf)), (MPARAM)buf);
         
         // get rid of the '~' if there is one
         move == FALSE;
         for (i=0;i < (sizeof(buf) - 1);i++)
            {
            if ((buf[i] == '~') || (move == TRUE))
               {
               // move all of the rest of the characters to the left one
               buf[i] = buf[i+1];
               move = TRUE;
               }
            }

         // set the WC_ENTRYFIELD to the value from the menu
         wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
         wp.cchText = sizeof(buf);
         wp.pszText = buf;
         ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                          (MPARAM) &wp, 0));

         // move the focus to the next window,  This really only works
         // in the case of this window being used in a Dialog Box
         WinSetFocus ( HWND_DESKTOP,
            WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                             hwnd,
                             EDI_NEXTTABITEM, FALSE ));
         return TRUE;
         break;

      case WM_CHAR:
         if (CHARMSG(&msg)->fs & KC_VIRTUALKEY)
            {
            switch (CHARMSG(&msg)->vkey)
               {
               case VK_BACKTAB:
               case VK_UP:
               case VK_LEFT:
                  if (!(CHARMSG(&msg)->fs & KC_KEYUP))
                     {
                     WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_PREVTABITEM, FALSE ));
                     }
                  return 0L;
                  break;
               case VK_TAB:
               case VK_DOWN:
               case VK_RIGHT:
                  if (!(CHARMSG(&msg)->fs & KC_KEYUP))
                     {
                     WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                     }
                  return 0L;
                  break;
               case VK_BACKSPACE:
               case VK_SPACE:
                  break;
               default:
                  return ((pfentry)(hwnd, msg, mp1, mp2));
               }
            }
         if (CHARMSG(&msg)->fs & KC_CHAR)
            {
            switch (CHARMSG(&msg)->chr)
               {
               case '\x008':
                  // on a backspace clear out the entire text
                  buf[0] = '\0';
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'M':
               case 'm':
               case '1':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"MONDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'T':
               case 't':
               case '2':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"TUESDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'W':
               case 'w':
               case '3':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"WEDNESDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'H':
               case 'h':
               case '4':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"THURSDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'F':
               case 'f':
               case '5':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"FRIDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'S':
               case 's':
               case '6':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"SATURDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               case 'U':
               case 'u':
               case '7':
               case '0':
                  WinSetFocus ( HWND_DESKTOP,
                        WinEnumDlgItem ( WinQueryWindow( hwnd,QW_OWNER,FALSE),
                              hwnd,
                              EDI_NEXTTABITEM, FALSE ));
                  strcpy(buf,"SUNDAY");
                  wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
                  wp.cchText = sizeof(buf);
                  wp.pszText = buf;
                  return ((pfentry)(hwnd, WM_SETWINDOWPARAMS,
                                    (MPARAM) &wp, 0));
                  break;

               default:
                  parent = WinQueryWindow(hwnd, QW_PARENT, FALSE );
                  hmod = (HMODULE)WinQueryWindowULong(parent,DAYHMOD_OFFSET);
                  WinQueryWindowRect(hwnd, &rc);
                  CreateMenu(hwnd, hmod, 100, rc.xRight, rc.yTop);
                  DosBeep(600,40);
                  return TRUE;
               }
            }
         else
            {
            return ((pfentry)(hwnd, msg, mp1, mp2));
            }
         break;

      default:
         return ((pfentry)(hwnd, msg, mp1, mp2));
      }
   return 0L;
   }


