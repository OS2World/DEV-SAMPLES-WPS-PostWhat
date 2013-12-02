#include "filehlp.h"

PFEA2LIST CreateEAFromFileType(PSZ filetype)
{
    if (filetype)
    {
        ULONG ulLenName     = strlen(".TYPE");
        ULONG ulLenEA       = strlen(filetype);
        ULONG ulLenValue    = sizeof(EADEF)+ulLenEA;
        ULONG ulLen         = sizeof(FEA2LIST)+ulLenName+ulLenValue;
        PFEA2LIST fpFEA2List = NULL;

        fpFEA2List = (PFEA2LIST)malloc(ulLen);
        if (fpFEA2List)
        {

            memset(fpFEA2List,0,ulLen);
            fpFEA2List->cbList = ulLen;

            PFEA2 pfea2;
            pfea2   = fpFEA2List->list;
            pfea2->cbName                      = ulLenName;
            pfea2->cbValue                     = ulLenValue;
            strcpy(pfea2->szName,".TYPE");

            PEADEF pea;
            pea     = (PEADEF)((ULONG)(pfea2+1) + pfea2->cbName);
            pea->usEAType   = EAT_ASCII;
            pea->usEALen    = ulLenEA;
            strcpy(pea->szEA,filetype);
            return fpFEA2List;
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return NULL;
    }
}

VOID FreeEAFromFileType(PFEA2LIST pfea2)
{
    free(pfea2);
}

APIRET WriteMLEBufferFromFile(HWND hwndMLE, PSZ filename)
{
    APIRET rc;
    HFILE hf = NULLHANDLE;
    ULONG ulAction;

    rc = DosOpen(
                    filename,
                    &hf,
                    &ulAction,
                    0UL,
                    FILE_NORMAL,
                    OPEN_ACTION_OPEN_IF_EXISTS | OPEN_ACTION_FAIL_IF_NEW,
                    OPEN_ACCESS_READONLY | OPEN_SHARE_DENYNONE,
                    NULL);
    if (NO_ERROR == rc)
    {
        FILESTATUS3 fs = {0};

        rc = DosQueryFileInfo(
                                hf,
                                FIL_STANDARD,
                                &fs,
                                sizeof(fs));
        if (NO_ERROR == rc)
        {
            IPT ipt=0UL;
            ULONG ulLen = fs.cbFile;
            PVOID pBuf = malloc(ulLen);
            if (pBuf)
            {
                rc = DosRead(hf,pBuf,ulLen,&ulLen);
                if (NO_ERROR == rc)
                {
                    ULONG ulFormat = MLFIE_CFTEXT; // todo: detect the filetype from EA to correctly set format: CFTEXT for text files, NOTRANS for pwn files !
                    WinSendMsg(hwndMLE,MLM_FORMAT,MPFROMLONG(ulFormat),MPVOID);
                    WinSendMsg(hwndMLE,MLM_SETIMPORTEXPORT,MPFROMP(pBuf),MPFROMLONG(ulLen));
                    ulLen = (ULONG)WinSendMsg(hwndMLE,MLM_IMPORT,MPFROMP(&ipt),MPFROMLONG(ulLen));
                    WinSendMsg(hwndMLE,MLM_FORMAT,MPFROMLONG(MLFIE_NOTRANS),MPVOID);
                }
                free(pBuf);
            }
            else
            {
                rc = ERROR_NOT_ENOUGH_MEMORY;
            }
        }
        rc = DosClose(hf);
    }
    return rc;
}

APIRET WriteFileFromMLEBuffer(PSZ filename,PSZ filetype,HWND hwndMLE)
{
    APIRET rc;
    HFILE hf=NULLHANDLE;
    ULONG ulAction;
    IPT ipt=0UL;
    ULONG ulLen = (ULONG)WinSendMsg(hwndMLE,MLM_QUERYFORMATTEXTLENGTH,MPFROMLONG(ipt),MPFROMLONG(-1));
    PVOID pBuf = malloc(ulLen);
    if (pBuf)
    {
        HFILE hf=NULLHANDLE;
        ULONG ulAction=0UL;
        APIRET rc=NO_ERROR;
        EAOP2 eaop={0};
        WinSendMsg(hwndMLE,MLM_SETIMPORTEXPORT,MPFROMP(pBuf),MPFROMLONG(ulLen));
        ulLen = (ULONG)WinSendMsg(hwndMLE,MLM_EXPORT,MPFROMP(&ipt),MPFROMP(&ulLen));

        eaop.fpFEA2List = CreateEAFromFileType(filetype);
        rc = DosOpen(
                        filename,
                        &hf,
                        &ulAction,
                        ulLen,
                        FILE_NORMAL,
                        OPEN_ACTION_CREATE_IF_NEW | OPEN_ACTION_REPLACE_IF_EXISTS,
                        OPEN_ACCESS_WRITEONLY | OPEN_SHARE_DENYWRITE,
                        &eaop);

        if (NO_ERROR == rc)
        {
            ULONG ulWritten;
            rc = DosWrite(hf,pBuf,ulLen,&ulWritten);
            rc = DosClose(hf);
        }
        FreeEAFromFileType(eaop.fpFEA2List);
    }
    else
    {
        rc = ERROR_NOT_ENOUGH_MEMORY;
    }
    free(pBuf);
    return rc;
}
