`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:26:40
// Design Name: 
// Module Name: lab5_3
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



module lab5_3(  output  [3:0]Q, output [3:0]unq,
                input clr,input [3:0]D,input mclk
    );
            
    DFF DFF1(Q[0],unq[0],D[0],mclk,clr),
        DFF2(Q[1],unq[1],D[1],mclk,clr),
        DFF3(Q[2],unq[2],D[2],mclk,clr),
        DFF4(Q[3],unq[3],D[3],mclk,clr);
    
    
endmodule
