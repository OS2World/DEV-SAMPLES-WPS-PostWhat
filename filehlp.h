#ifndef __FILEHLP_H__
#define __FILEHLP_H__

#define INCL_BASE
#define INCL_PM
#include <os2.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)
typedef struct _EADEF
{
    USHORT      usEAType;
    USHORT      usEALen;
    CHAR        szEA[1];
} EADEF, *PEADEF;
#pragma pack()

APIRET WriteFileFromMLEBuffer(PSZ filename,PSZ filetype,HWND hwndMLE);
APIRET WriteMLEBufferFromFile(HWND hwndMLE, PSZ filename);

#endif
