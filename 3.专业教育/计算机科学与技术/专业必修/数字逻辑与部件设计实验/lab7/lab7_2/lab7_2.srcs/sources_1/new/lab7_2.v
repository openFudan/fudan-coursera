`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/26 21:34:04
// Design Name: 
// Module Name: lab7_2
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

module counter(input CLK,ST,RESET,
                output TS,TL);
       always @(posedge CLK)
        if(!RESET)  

endmodule

module FSM(input TS,TL,C,CLK,RESET,
          output ST,output [5:0]L);
       reg HG,LG,HY,FY;
    always@(posedge CLK,negedge RESET)
    if(!RESET) 
      
    
endmodule

module TOPMO(input CLK,C,
              output [5:0]L);

endmodule