# makefile
# Erstellt von IBM WorkFrame/2 MakeMake um 2:58:27 am 13 Juni 2010
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::SOM Compiler
#  Compile::C++ Compiler
#  Link::Linker
#  Bind::Resource Bind
#  Compile::Resource Compiler
#  Misc::DLL with OS2OM30.DLL runtime and replace locked DLL in system directory

!IF [SET SMINCLUDE=$(SMINCLUDE)] || [SET INCLUDE=.;$(CPPMAIN)\INCLUDE;$(SOMBASE)\INCLUDE;$(SOMBASE:som=H)]
!ENDIF

.SUFFIXES:

.SUFFIXES: .cpp .dll .idl .obj .rc .res 

.idl.cpp:
	@echo " Compile::SOM Compiler "
	sc.exe  -C200000 -S200000 -s"xc;xh;xih" "$<"

.cpp.obj:
	@echo " Compile::C++ Compiler "
	icc.exe /Q /Ti /Gm /Gd /Ge- /G5 /C "$<"

.rc.res:
	@echo " Compile::Resource Compiler "
	rc.exe -n -r "$<" "$@"

all: postwhat.dll

postwhat.dll: except.obj filehlp.obj postwhat.obj error.obj postwhat.res {$(LIB)}somtk.lib {$(LIB)}ffst.lib postwhat.def
	@echo " Link::Linker "
	@echo " Bind::Resource Bind "
    @echo " Misc::DLL with OS2OM30.DLL runtime and replace locked DLL in system directory"
	icc.exe @<<
 /Q /B" /de /dbgpack /br /exepack:2 /nobase /packc:0xFFFFFFFF /packd:0xFFFFFFFF /optfunc /noe /m"
 /Fe$@
somtk.lib 
ffst.lib 
postwhat.def
except.obj
filehlp.obj
postwhat.obj
error.obj
<<
	rc.exe -n -x2 postwhat.res "$@"
 	dllrname.exe "$@" CPPOM30=OS2OM30 /Q /N /R
    emxupd.exe "$@" "$(COMSPEC:CMD.EXE=DLL)"

postwhat.cpp: postwhat.idl

except.obj: except.cpp {.;$(INCLUDE);}except.h

error.obj: error.cpp

postwhat.obj: postwhat.cpp {.;$(INCLUDE);}filehlp.h {.;$(INCLUDE);}postwhat.xih {.;$(INCLUDE);}rc.h {.;$(INCLUDE);}except.h {.;$(INCLUDE);}error.h

filehlp.obj: filehlp.cpp {.;$(INCLUDE);}filehlp.h

postwhat.res: postwhat.rc {.;$(INCLUDE)}default.ico

