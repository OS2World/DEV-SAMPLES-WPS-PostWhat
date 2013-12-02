/* REXX script */

if RxFuncQuery('SysLoadFuncs') then do
    rc = RxFuncAdd('SysLoadFuncs','REXXUTIL','SysLoadFuncs')
    rc = SysLoadFuncs()
end
rc = SysCreateObject("PostWhat","TestPostWhat","<WP_DESKTOP>",,"U")

return
