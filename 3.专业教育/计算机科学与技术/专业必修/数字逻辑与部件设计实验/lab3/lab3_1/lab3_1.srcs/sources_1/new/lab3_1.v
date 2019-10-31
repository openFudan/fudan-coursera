`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/07 08:38:28
// Design Name: 
// Module Name: lab3_1
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


module lab1(
    input A,B,C,
     output S,CO
    );
    wire [7:0] w;
    assign w[0]=~(~A&~B&C);
    assign w[1]=~(~A&B&~C);
    assign w[2]=~(A&~B&~C);
    assign w[3]=~(A&B&C);
    assign w[4]=~(B&C);
    assign w[5]=~(A&B);
    assign w[6]=~(A&C);
    nand
      n1(S,w[0],w[1],w[2],w[3]),
      n2(CO,w[4],w[5],w[6]);
endmodule
