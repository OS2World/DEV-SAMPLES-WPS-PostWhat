# makefile
# Erstellt von IBM WorkFrame/2 MakeMake um 2:58:23 am 13 Juni 2010
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::Message Compiler

.SUFFIXES:

.SUFFIXES: .msg .txt 

.txt.msg:
	@echo " Compile::Message Compiler "
    mkmsgf.exe "$<" "$@"
    copy "$@" "$(COMSPEC:CMD.EXE=SYSTEM)"

all: postwhat.msg

postwhat.msg: postwhat.txt
