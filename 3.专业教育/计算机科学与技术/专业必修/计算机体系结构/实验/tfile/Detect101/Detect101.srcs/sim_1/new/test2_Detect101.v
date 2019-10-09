`timescale 1ns / 100ps
// 方案2：输入信号与clock同步
module test2_Detect101( );
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
    initial #24 reset = 1'b0; //24ns后reset=0
  
    always  #5 clock = ~clock;//时钟周期10ns
    //与clock同步
    always forever @(posedge clock) x = ~x; 
endmodule    

//    //每当 current 状态值变化时，就会显示变化后的值
//    initial $monitor("New state is %d and occurs at %t",MUT.current, $time);
//    //每当输出值 z 变化时，就会显示变化后的值
//    always @(z) $display("Output changes at %t to %b", $time, z);

