`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/03 09:46:35
// Design Name: 
// Module Name: ram2
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


module ram2(
    input clk,
    input wen,
    input [3:0] addr,
    input [3:0] din,
    output [3:0] qout
    );
    reg[3:0]ram[0:15];
    always@(posedge clk)
      if(wen)
        ram[addr]<=din;
      assign qout=ram[addr];  
endmodule
