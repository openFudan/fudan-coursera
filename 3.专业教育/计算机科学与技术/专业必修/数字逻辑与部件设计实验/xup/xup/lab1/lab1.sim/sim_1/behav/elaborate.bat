@echo off
set xv_path=D:\\Vivado\\2015.2\\bin
call %xv_path%/xelab  -wto 85019bb5cc5b4e799039907e6e4918d9 -m64 --debug typical --relax --mt 2 -L xil_defaultlib -L unisims_ver -L unimacro_ver -L secureip --snapshot lab1_tb_behav xil_defaultlib.lab1_tb xil_defaultlib.glbl -log elaborate.log
if "%errorlevel%"=="0" goto SUCCESS
if "%errorlevel%"=="1" goto END
:END
exit 1
:SUCCESS
exit 0
