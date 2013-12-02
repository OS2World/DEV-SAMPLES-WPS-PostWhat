#include <error.h>

#define DMI_PRODUCT_ID                  "PostWhat DLL"
#define DMI_MODIFICATION_LEVEL          "0"
#define DMI_FIX_LEVEL                   "0"
#define DMI_VENDOR_TAG                  "Lars Erdmann"
#define DMI_TAG                         "PostWhat WPS Object Class"
#define DMI_REVISION                    "1.00"
#define TEMPLATE_FILENAME               "postwhat.rep"

APIRET LogError(ULONG id,HMODULE hmod,PSZ filename,ULONG line,PEXCEPTIONREPORTRECORD2 pRep)

{
    CHAR        lineno[256];
    CHAR        modName[CCHMAXPATH];
    PRODUCTDATA prodData={0};
    DMIDATA     dmiData={0};
    PRODUCTINFO prodInfo={0};
    MSGINSDATA  msgInsData={0};
    FFSTPARMS   ffstParms={0};
    APIRET      rc=NO_ERROR;

    _itoa(line,lineno,10);
    rc = DosQueryModuleName(hmod,sizeof(modName),modName);

    dmiData.packet_size                     = sizeof(dmiData);
    dmiData.packet_revision_number          = DMIDATA_ASCII;
    dmiData.DMI_product_ID                  = DMI_PRODUCT_ID;
    dmiData.DMI_modification_level          = DMI_MODIFICATION_LEVEL;
    dmiData.DMI_fix_level                   = DMI_FIX_LEVEL;
    dmiData.template_filename_length        = strlen(TEMPLATE_FILENAME)*sizeof(CHAR);
    dmiData.template_filename               = TEMPLATE_FILENAME;

    prodData.packet_size                    = sizeof(prodData);
    prodData.packet_revision_number         = PRODUCTDATA_ASCII;
    prodData.DMI_vendor_tag                 = DMI_VENDOR_TAG;
    prodData.DMI_tag                        = DMI_TAG;
    prodData.DMI_revision                   = DMI_REVISION;

    prodInfo.pProductData                   = &prodData;
    prodInfo.pDMIData                       = &dmiData;

    msgInsData.no_inserts                   = 2;
    msgInsData.MsgInsTxt[0].insert_number   = 1;
    msgInsData.MsgInsTxt[0].insert_text     = filename;
    msgInsData.MsgInsTxt[1].insert_number   = 2;
    msgInsData.MsgInsTxt[1].insert_text     = lineno;

    ffstParms.packet_size                   = sizeof(ffstParms);
    ffstParms.packet_revision_number        = FFSTPARMS_OS2_ASCII;
    ffstParms.module_name                   = modName;
    ffstParms.probe_ID                      = id;
    ffstParms.severity                      = SEVERITY4;
    ffstParms.template_record_ID            = id;
    ffstParms.pMsgInsData                   = &msgInsData;
    ffstParms.log_user_data_length          = sizeof(*pRep);
    ffstParms.log_user_data                 = pRep;

    rc = FFSTProbe(&prodInfo,&ffstParms);

    return rc;
}
