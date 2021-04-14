set CDIR=%~dp0bin
set CDIR=%CDIR:"=%

rmdir d:\ /s/q
copy %CDIR%\kernel.elf d:\
copy %CDIR%\zap-light16.psf d:\
mkdir d:\efi
mkdir d:\efi\boot
copy %CDIR%\..\..\gnu-efi\x86_64\bootloader\main.efi d:\efi\boot\bootx64.efi
