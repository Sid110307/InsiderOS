#!/bin/sh

OS_IMG=bin/InsiderOS

if [ "$1" = "-s" ] || [ "$1" = "--silent" ]; then SILENT=-s; fi

cd gnu-efi || exit 2
make bootloader $SILENT

cd ../kernel || exit 2
make clean $SILENT
make kernel $SILENT
make buildimg $SILENT
sudo rm -f $OS_IMG.vdi
VBoxManage convertfromraw --format VDI $OS_IMG.img $OS_IMG.vdi
make run $SILENT
cd ..
