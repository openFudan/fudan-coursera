`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/04 11:26:09
// Design Name: 
// Module Name: lab4_2
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
   // output clk190,
    //output clk48,
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
    //assign clk190=q[18];//190hz
    //assign clk48=q[20];//47.7 
    assign clk1_4hz=q[24];         
endmodule

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

module ls377(   input clk,input en,input [3:0]d,
                output reg [3:0]q
              );
          always@(posedge clk,negedge en)
            if(en) 
            q<=d;
endmodule

module    u521(    input swi,input [3:0]a,input [3:0]b,    
                   output  reg [3:0] q
               );
              always@(swi,a,b)
               if(!swi)  q=a;
               else q=b; 

endmodule

module  u621(  input [1:0]s,input  [3:0]a,input  [3:0]b,input [3:0]c,input [3:0]d,
                 output  reg [3:0]q
              );
              always@(s,a,b,c,d)begin 
          if(~s[1]&~s[0])  begin q=a;end
          if(~s[1]&s[0]) begin q=b; end
          if(s[1]&~s[0])  begin q=c; end
          if(s[1]&s[0])  begin q=d; end
          end
endmodule

module topp( input clk,input [14:0]s,
             output  [15:0]q
                     );
         wire clka;    
         wire [3:0]a;
         wire [3:0]b; 
         wire [15:0]qq;
         assign q=qq;
         clkdiv clk1(clk,clka);             
         ls377 lab1(clka,s[7],a,qq[11:8]),
               lab2(clka,s[6],b,qq[3:0]),
               lab3(clka,s[5],b,qq[7:4]);
               
         ram2     lab4(clka,s[0],s[4:1],b,qq[15:12]);
         u521  lab5(s[12],s[11:8],b,a);
         u621  lab6(s[14:13],qq[11:8],qq[3:0],qq[7:4],qq[15:12],b);
         
endmodule
           

