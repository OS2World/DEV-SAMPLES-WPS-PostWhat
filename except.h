#ifndef __EXCEPT_H__
#define __EXCEPT_H__

#define INCL_BASE
#include <os2.h>
#include <setjmp.h>

typedef struct _PEXCEPTIONREPORTRECORD2
{
    EXCEPTIONREPORTRECORD       rep;
    CHAR                        modName[CCHMAXPATH];
} EXCEPTIONREPORTRECORD2, *PEXCEPTIONREPORTRECORD2;

typedef struct _EXCEPTIONREGISTRATIONRECORD2
{
    EXCEPTIONREGISTRATIONRECORD reg;
    EXCEPTIONREPORTRECORD2      repRec;
    jmp_buf                     jmp;
} EXCEPTIONREGISTRATIONRECORD2, *PEXCEPTIONREGISTRATIONRECORD2;

extern ULONG APIENTRY ExceptionHandler(
                                    PEXCEPTIONREPORTRECORD pRep,
                                    PEXCEPTIONREGISTRATIONRECORD2 pReg,
                                    PCONTEXTRECORD pCtx,
                                    PVOID pDispCtx);

#define TRY(except)                                                                                                 \
    {                                                                                                               \
        if (somIsObj(somSelf))                                                                                      \
        {                                                                                                           \
            EXCEPTIONREGISTRATIONRECORD2 except={0};                                                                \
                                                                                                                    \
            except.reg.ExceptionHandler = (ERR)ExceptionHandler;                                                    \
            DosSetExceptionHandler((PEXCEPTIONREGISTRATIONRECORD)&except);                                          \
            if (setjmp(except.jmp) == 0)                                                                            \
            {                                                                                                       \
                if (somSelf->wpAssertObjectMutexSem() || !somSelf->wpRequestObjectMutexSem(SEM_INDEFINITE_WAIT))    \
                {

#define CATCH(except)                                                                                               \
                }                                                                                                   \
            }                                                                                                       \
            else                                                                                                    \
            {                                                                                                       \
                if (setjmp(except.jmp) == 0)                                                                        \
                {

#define ENDTRY()                                                                                                    \
                }                                                                                                   \
            }                                                                                                       \
            if (somSelf->wpAssertObjectMutexSem())                                                                  \
            {                                                                                                       \
                somSelf->wpReleaseObjectMutexSem();                                                                 \
            }                                                                                                       \
            DosUnsetExceptionHandler((PEXCEPTIONREGISTRATIONRECORD)&except);                                        \
        }                                                                                                           \
    }

#endif
