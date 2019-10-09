`timescale 1ns / 100ps

module test1_Detect101( );
  reg x,reset,clock;//待测模块输入端口变量
  wire z;           //待测模块输出端口变量
  //实例化
  Detect101 MUT(x, reset, clock, z);
  //初始化
  initial begin
    x = 1'b0;
    reset = 1'b1;
    clock = 1'b0;
  end
  //激励信号
  initial
    #24 reset = 1'b0;     //24ns后reset=0

  always #5 clock = ~clock;//时钟周期10ns
  always #7 x = ~x;       //x变化周期14ns
endmodule
