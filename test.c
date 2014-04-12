#define INCL_PM
#include <os2.h>

#define USERDATASIZE 0L

#include "dayregst.h"

HAB    hanchor;
HWND   hclient;
HWND   hframe;

PFNWP pfentry;
CHAR ClassName[] = "me";
HWND hwndentry;
HWND hMenu;
WNDPARAMS wp;
CHAR      buf[4];

MRESULT EXPENTRY WinProc ( HPS hwnd, USHORT msg, MPARAM mp1, MPARAM mp2 )
   {
   switch ( msg )
      {

      case WM_SIZE:
         hwndentry = WinCreateWindow(hwnd,
            "DAYFIELD",
            "MONDAY",
            WS_VISIBLE, 
            20,20,
            100,15,
            hwnd,
            HWND_TOP,
            1,
            NULL,
            NULL);

         hwndentry = WinCreateWindow(hwnd,
            "DAYFIELD",
            "TUESDAY",
            WS_VISIBLE | ES_MARGIN,
            20,50,
            100,15,
            hwnd,
            HWND_TOP,
            1,
            NULL,
            NULL);
         return TRUE;
         break;

      case WM_ERASEBACKGROUND:
         return TRUE;
         break;

      case WM_BUTTON2DOWN:
         wp.fsStatus = WPM_CCHTEXT | WPM_TEXT;
         wp.cchText = sizeof(buf);
         wp.pszText = buf;
         WinSendMsg(hwndentry,
                  WM_QUERYWINDOWPARAMS,
                  (MPARAM) &wp,
                  0);
         WinMessageBox(HWND_DESKTOP,
            hwnd,                      /* client-window handle  */
            buf,                       /* body of the message   */
            "entry text",              /* title of the message  */
            0,                         /* message box id        */
            MB_OK | MB_ICONHAND);      /* icon and button flags */
         break;

      default:
         return WinDefWindowProc ( hwnd, msg, mp1, mp2 );
      }
   return 0L;
   }


main()

   {
   HMQ    hmqueue;
   QMSG   msg;
   ULONG  fs;

   hanchor = WinInitialize(NULL);
   hmqueue = WinCreateMsgQueue ( hanchor, 0 );
   WinRegisterClass (
                 hanchor,
                 ClassName,
                 WinProc,
                 0L,
                 USERDATASIZE);

    // you must register the day field class
    RegisterDayFieldClass ( hanchor );

    fs = FCF_TITLEBAR
            | FCF_SIZEBORDER
            | FCF_SYSMENU
            | FCF_TASKLIST
            | FCF_MINMAX
            | FCF_SHELLPOSITION
            ;

   hframe = WinCreateStdWindow (
                 HWND_DESKTOP,
                 WS_VISIBLE,
                 &fs,
                 ClassName,
                 "",
                 0L,
                 NULL,
                 0,
                 &hclient);

   while ( WinGetMsg ( hanchor, &msg, NULL, 0, 0 ))
         {
         WinDispatchMsg ( hanchor, &msg );
         }

   WinDestroyWindow ( hframe );
   WinDestroyMsgQueue ( hmqueue );
   WinTerminate ( hanchor );

   return 0;

}
