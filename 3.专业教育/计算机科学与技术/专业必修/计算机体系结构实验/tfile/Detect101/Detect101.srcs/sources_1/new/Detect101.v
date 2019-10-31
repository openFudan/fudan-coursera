`timescale 1ns / 100ps
////////////////////////////////////
//功能：检测101序列，Moore状态机。
//     当检测到输入序列为 101 时，
//     当前状态值变为d，输出z值为1。
////////////////////////////////////
module Detect101(
    input x,
    input rst,
    input clk,
    output z   );
    
    parameter [1:0] a=0, b=1, c=2, d=3;
    reg        [1:0] current;
  
    always @( posedge clk ) begin
      if( rst )
        current = a;
      else
        case( current )
          a: current = x ? b : a;
          b: current = x ? b : c;
          c: current = x ? d : a;
          d: current = x ? b : c;
          default: current = a;
        endcase
      end
  
    assign z = (current==d) ? 1'b1 : 1'b0;    
endmodule