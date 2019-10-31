`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/16 21:45:23
// Design Name: 
// Module Name: lab6_1
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

module lab6_1(
      input [3:0]A,input CLR,input LOAD,input P,input T,input CLK,
      output reg [3:0]Q,output reg RCO
    );
    wire clka;    
   
      clkdiv clka1(CLK,clka);
       
        always@(posedge clka)    
           if(!CLR)           Q<=4'b0000;    
            else if(!LOAD)    
        begin           Q<=A;      end     
           else case({P,T})       
           2'b0x: begin Q<=Q;RCO<=1'b0;end     
           2'bx0: begin Q<=Q;RCO<=1'b0;end   
           2'b11:
            begin        
           if(Q[0]&Q[1]&Q[2]&Q[3]&T) RCO<=1'b1;
           else RCO<=1'b0;
            Q<=Q+1'b1;
            end          
          endcase  
    
endmodule
