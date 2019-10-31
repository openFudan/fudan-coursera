`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/10/27 12:02:56
// Design Name: 
// Module Name: LABXQSIM
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


module LABXQSIM(  );
    reg  G1, G2A,G2B;
    reg  [2:0] S;
     wire  [7:0] Y;
     lab1 labtext(G1, G2A,G2B,   S,  Y);
    initial 
    begin
    G1=1'b0;   G2A=1'b0;  G2B=1'b0;  S[0]=1'b0;S[1]=1'b0;S[2]=1'b0;
    
    #100 G1=1'b1;   G2A=1'b0;  G2B=1'b0;  S[0]=1'b1;S[1]=1'b1;S[2]=1'b1;
    end
    initial #200 $finish;
endmodule
