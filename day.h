typedef struct _DAYINFO {
   HWND     hwndEntry;
   SHORT    xoffset;
   SHORT    yoffset;
   ULONG    flStyle;
   } DAYINFO, *PDAYINFO;

#define PDAYI_OFFSET (0)
#define DAYHMOD_OFFSET (PDAYI_OFFSET + sizeof(PDAYINFO))
#define ID_ENTRY    (1)
#define MODNAME     "DAYFIELD"
#define DATASIZE (DAYHMOD_OFFSET + sizeof(ULONG))
