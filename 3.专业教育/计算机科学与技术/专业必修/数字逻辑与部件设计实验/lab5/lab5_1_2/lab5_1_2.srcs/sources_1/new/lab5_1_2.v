`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:07:49
// Design Name: 
// Module Name: lab5_1_2
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

module JK_FF ( input J, K, mclk,clr, output reg Q,wire unq);
 
         wire clka;
          assign unq=~Q;
          clkdiv clk1(mclk,clka);
                       
  always @ ( posedge clka, negedge clr)
     if (!clr)
     Q<= 1'b0;

     else case ({J,K})
      2'b00: Q <= Q;
      2'b01: Q <= 1'b0;
      2'b10: Q <= 1'b1;
      2'b11: Q <= !Q;
  endcase
endmodule

