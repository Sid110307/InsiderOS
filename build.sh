#!/bin/sh

if [ "$1" = "-s" ] || [ "$1" = "--silent" ]; then
	cd gnu-efi
	make bootloader -s
	cd ../kernel/
	make kernel -s
	make buildimg -s
	make run -s
	cd ../
else
	cd gnu-efi
	make bootloader
	cd ../kernel/
	make kernel
	make buildimg
	make run
	cd ../
fi

