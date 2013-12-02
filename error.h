#ifndef __ERROR_H__
#define __ERROR_H__
#define INCL_BASE
#include <os2.h>
#define INCL_FFST
#include <ffst.h>
#include <stdlib.h>
#include <string.h>
#include "except.h"

APIRET LogError(ULONG id,HMODULE hmod,PSZ filename,ULONG line,PEXCEPTIONREPORTRECORD2 pRep);
#endif
