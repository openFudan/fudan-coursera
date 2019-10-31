`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:27:31
// Design Name: 
// Module Name: lab5_4
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

module lab5_4(   input R,input A1,input A0,input SI,input [3:0]D,input mclk,
                   output reg [3:0]Q
    );
     wire clka;
             
             clkdiv clk1(mclk,clka);
    always @(posedge clka)
    if(!R) Q<=4'b0000;
    else case({A1,A0})
      2'b00:;
      2'b01:Q<={SI,Q[3:1]};
      2'b10:Q<={Q[2:0],SI};
      2'b11:Q<=D;
    endcase
endmodule
