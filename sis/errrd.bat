@echo off
echo #{"ErrRd"},(0xEEEEEEEE),1,0,3 >ErrRd.pkg
echo %%{"ErrRd"} >> ErrRd.pkg
echo :"ErrRd" >> ErrRd.pkg
echo [0x101F7961], 0, 0, 0, {"S60 3rd ProductID"} >> ErrRd.pkg
echo [0x1028315F], 0, 0, 0, {"S60 5th ProductID"} >> ErrRd.pkg
echo [0x20022E6D], 0, 0, 0, {"Symbian^3 ProductID"} >> ErrRd.pkg
echo "nul"-"c:\resource\ErrRd" >>ErrRd.pkg
makesis ErrRd.pkg
makekeys -cert  -expdays 3650 -password test -dname "CN=Developer OU=MobileDev" test.key test.cer
signsis ErrRd.sis ErrRd.sisx test.cer test.key test
del test.key
del test.cer
del .rnd
del ErrRd.sis
del ErrRd.pkg
pause
