@echo off
set xv_path=D:\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto a11455b8463c45d6b8a40cb32f8c1b3b -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab6_1_behav xil_defaultlib.lab6_1 xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
