`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:24:51
// Design Name: 
// Module Name: lab5_2_1
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

module D_FF (Q, D, Clk);
  output Q;
  input D, Clk;
  reg Q;
  always @ (posedge Clk)
      Q <= D;
endmodule

module JKFF ( output reg Q, 
                           input J, K, Clk);
  wire JK;
  assign JK = (J & ~Q) | (~K & Q);
    
    DFF JK1 (Q, JK, Clk);
endmodule

