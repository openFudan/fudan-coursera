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
