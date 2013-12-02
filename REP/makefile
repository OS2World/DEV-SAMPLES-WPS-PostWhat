# makefile
# Erstellt von IBM WorkFrame/2 MakeMake um 2:58:24 am 13 Juni 2010
#
# Diese Make-Datei enth„lt folgende Aktionen:
#  Compile::Create Error Template

.SUFFIXES:

.SUFFIXES: .rep .txt 

.txt.rep:
	@echo " Compile::Create Error Template "
	mktmpf.exe -q -O"$@" --"$<"
    copy "$@" "$(COMSPEC:CMD.EXE=SYSTEM)"

all: postwhat.rep

postwhat.rep: postwhat.txt
