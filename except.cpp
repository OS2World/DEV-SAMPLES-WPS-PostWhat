#include <string.h>
#include "except.h"

VOID convToBigEndian(PVOID dest,PVOID src,ULONG numBytes)
{
    UCHAR temp[sizeof(ULONG)];
    for(int i=0;i<numBytes;i+=sizeof(ULONG))
    {
        temp[0] = *((PUCHAR)src+3);
        temp[1] = *((PUCHAR)src+2);
        temp[2] = *((PUCHAR)src+1);
        temp[3] = *((PUCHAR)src+0);

        *((PULONG)dest) = *((PULONG)temp);

        dest = ((PULONG)dest)+1;
        src  = ((PULONG)src)+1;
    }
    return;
}

ULONG APIENTRY ExceptionHandler(
                                    PEXCEPTIONREPORTRECORD pRep,
                                    PEXCEPTIONREGISTRATIONRECORD2 pReg,
                                    PCONTEXTRECORD pCtx,
                                    PVOID pDispCtx)
{
    if (pRep->fHandlerFlags & (EH_EXIT_UNWIND|EH_UNWINDING|EH_NESTED_CALL))
    {
        return XCPT_CONTINUE_SEARCH;
    }

    switch (pRep->ExceptionNum)
    {
        case XCPT_ACCESS_VIOLATION:
        case XCPT_ILLEGAL_INSTRUCTION:
        case XCPT_PRIVILEGED_INSTRUCTION:
        case XCPT_INVALID_LOCK_SEQUENCE:
        case XCPT_INTEGER_DIVIDE_BY_ZERO:
        case XCPT_INTEGER_OVERFLOW:
        case XCPT_FLOAT_DIVIDE_BY_ZERO:
        case XCPT_FLOAT_OVERFLOW:
        case XCPT_FLOAT_UNDERFLOW:
        case XCPT_FLOAT_INVALID_OPERATION:
        case XCPT_FLOAT_DENORMAL_OPERAND:
        case XCPT_FLOAT_INEXACT_RESULT:
        case XCPT_FLOAT_STACK_CHECK:
            convToBigEndian(&pReg->repRec.rep,pRep,sizeof(*pRep)); // template can only format bytes
            {
                APIRET      rc=NO_ERROR;
                HMODULE     hmod = NULLHANDLE;
                ULONG       ulObjNum = 0;
                ULONG       ulOffset = 0;
                APIRET16    rc16 = NO_ERROR;

                rc = DosQueryModFromEIP(
                                            &hmod,
                                            &ulObjNum,
                                            sizeof(pReg->repRec.modName),
                                            pReg->repRec.modName,
                                            &ulOffset,
                                            pCtx->ctx_RegEip
                                        );
                if (rc != NO_ERROR)
                {
                    QMRESULT    qmresult={0};
                    rc16 = Dos16QueryModFromCS(pCtx->ctx_SegCs,&qmresult);
                    strcpy(pReg->repRec.modName,qmresult.name);
                }
            }
            longjmp(pReg->jmp,1);

        default:
            break;
    }
    return XCPT_CONTINUE_SEARCH;
}

