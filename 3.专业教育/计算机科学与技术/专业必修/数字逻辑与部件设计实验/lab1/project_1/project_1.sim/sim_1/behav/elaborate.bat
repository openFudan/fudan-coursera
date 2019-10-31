@echo off
set xv_path=D:\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto 31143b7f3d6f40d9813c4f9befdbf8d9 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab1_behav xil_defaultlib.lab1 xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
