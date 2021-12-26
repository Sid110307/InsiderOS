@echo off

cd gnu-efi
make bootloader -s
cd ../kernel/
make kernel -s
make buildimg -s
make run -s
cd ../