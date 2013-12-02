/* REXX script */

if RxFuncQuery('SysLoadFuncs') then do
       rc = RxFuncAdd('SysLoadFuncs','REXXUTIL','SysLoadFuncs')
       rc = SysLoadFuncs()
end

Path = SysIni('USER','XWorkplace','XFolderPath')
if (Path <> "ERROR:") then do
   Path = strip(Path,'T','0'x)
   '@'||Path||'\BIN\repclass.exe PostWhat PostWhatRep PWHATREP.DLL'
end
else do
	say 'Could not determine XWorkplace Folder Path !'
end
return rc
