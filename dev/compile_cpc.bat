@echo off

SET game=AbabolNESOM

..\utils\mkts_om.exe platform=cpc mode=pals in=..\ports\cpc\gfx\pal.png prefix=my_inks out=assets\pal.h silent

echo ### COMPILING ###
zcc +cpc -vn -O3 -unsigned -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c > nul 
rem zcc +cpc -vn -O3 -unsigned -m -notemp -zorg=1024 -lcpcrslib -DCPC -o %game%.bin tilemap_conf.asm mk3.c

echo ### MAKING DSK ###
copy %game%.bin game.bin > nul 
copy ..\ports\cpc\base.dsk %game%.dsk > nul 
copy ..\ports\cpc\arkos_sfx.c.bin arkos.bin > nul 
copy ..\ports\cpc\bin\loading.bin loading.bin > nul
..\utils\CPCDiskXP\CPCDiskXP.exe -File game.bin -AddAmsDosHeader 400 -AddToExistingDsk %game%.dsk
..\utils\CPCDiskXP\CPCDiskXP.exe -File arkos.bin -AddAmsDosHeader 7DFA -AddToExistingDsk %game%.dsk
..\utils\CPCDiskXP\CPCDiskXP.exe -File loading.bin -AddAmsDosHeader C000 -AddToExistingDsk %game%.dsk
del game.bin  > nul 
del arkos.bin > nul 
del loading.bin > nul
del zcc_opt.def  > nul 
