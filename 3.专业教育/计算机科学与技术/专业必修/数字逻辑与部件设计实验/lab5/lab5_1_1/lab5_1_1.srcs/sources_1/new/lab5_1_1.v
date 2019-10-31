`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:18:36
// Design Name: 
// Module Name: lab5_1_1
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module clkdiv(
    input mclk,
   // input clr,
    output clka
  //  output clkb
    );
    reg [28:0]q;
    always@(posedge mclk)
    begin
       q<=q+1;
    end
    assign clka=q[26];
 //   assign clkb=q[24];          
endmodule

module DFF ( output reg q,  wire unq, 
                       input      D, mclk,  clr);
          wire clka;
          assign unq=~q;
          clkdiv clk1(mclk,clka);
                       
  always @ (posedge clka,  negedge clr)
   
     if (!clr)
    q <= 1'b0;
    else
        q <= D;
        
endmodule
/*
module D_FF (output q,                        input  clk, D, set, clr);
   wire f1, f2, f3, f4, f5, f6;
  assign #5 f1 = ~(f1 & f5 & ~set);
  assign #5 f2 = ~(f1 & f5 & ~clr);
  assign #5 f3 = ~(f6 & f4 & ~set);
  assign #5 f4 = ~(f3 & Clk & ~clr);
  assign #5 f5 = ~(f4 & Clk & f6 & ~set);
  assign #5 f6 = ~(f5 & D & ~clr);
  assign #5    q = f1;
 
endmodule

*/
