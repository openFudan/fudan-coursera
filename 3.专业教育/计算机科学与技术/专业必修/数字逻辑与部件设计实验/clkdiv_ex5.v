`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/08 09:54:05
// Design Name: 
// Module Name: clkdiv
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
    output clk190,
    output clk48,
    output clk1_4hz
    );
    reg [27:0]q;
    always@(posedge mclk)
  //  begin
   // if(!clr)
   //      q<=0;
  //  else
         q<=q+1;
  //  end
    assign clk190=q[18];//190hz
    assign clk48=q[20];//47.7 
    assign clk1_4hz=q[24];         
endmodule
