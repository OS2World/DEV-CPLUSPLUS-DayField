/* ----------------------------------------------------------------------
.context CreateMenu
.category PM_Support 4
HWND CreateMenu( HWND hWnd,PUCHAR modname, USHORT id,USHORT x,USHORT y)

Description: 
     This Procedure will the load the menu, specified by id, from the
module specified by name, and place it at the location specified by
x, and y;


Parameter     Description
-------------------------------------------------------------------------
hWnd          a window handle for the owner and parent of the menu

modname       32 bit pointer to a zero terminated character string
              specifying the module to get the resource from.  Should
              be the name of the DLL using this call.

id            a USHORT specifing the menu to load

x,y           USHORT's specifying the x and y location for the menu

Returns: 
     a window handle for the new menu

Comments: 

References: 

See Also: 
.ref 

Development History: 
  Date         Programmer          Description of modification   
  07/20/1989   Paul Montgomery     Initial development           
-------------------------------------------------------------------- */

#define INCL_PM
#include <os2.h>
#include <stdlib.h>

HWND CreateMenu( HWND hWnd,HMODULE  hmod, USHORT id,USHORT x,USHORT y)
{
   HWND   hMenu;
   MENUITEM mitem;

   hMenu = WinLoadMenu(hWnd, hmod, id );

   y += (USHORT) WinQuerySysValue(HWND_DESKTOP,SV_CYMENU) + 1;
   x += 1;
   WinSendMsg(hMenu,MM_QUERYITEM,
      MPFROM2SHORT(WinSendMsg(hMenu,MM_ITEMIDFROMPOSITION,0,0),TRUE),
      &mitem);
	WinSetParent(hMenu,hWnd,FALSE);
	WinSetOwner(hMenu,hWnd);
	WinSetWindowPos(hMenu,HWND_TOP,x,y,0,0,
      SWP_MOVE|SWP_SHOW|SWP_SIZE|SWP_ZORDER);

   WinPostMsg(hMenu,MM_STARTMENUMODE,MPFROM2SHORT(TRUE,FALSE),0L);

   return(hMenu);
}

