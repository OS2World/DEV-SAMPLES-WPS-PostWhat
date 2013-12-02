/* REXX script */

if RxFuncQuery('SysLoadFuncs') then do
    rc = RxFuncAdd('SysLoadFuncs','REXXUTIL','SysLoadFuncs')
    rc = SysLoadFuncs()
end

if SysDeRegisterObjectClass("PostWhat") then do
    say "Klassenderegistierung erfolgreich"
    return 0
end
else
    say "Klassenderegistrierung fehlgeschlagen"
    return 1
