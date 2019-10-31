`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/16 22:19:32
// Design Name: 
// Module Name: LAB6_2
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
// 
module clkdiv(
    input mclk,
   // input clr,
    output clk190,
    output clk48,
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
    assign clk190=q[18];//190hz
    assign clk48=q[20];//47.7 
    assign clk1_4hz=q[24];         
endmodule



module lab6_2(
    output [3:0]A,[3:0]B,[3:0]C,[3:0]D,
    input mclk,
    input P,
    input Q
    );
    
    reg [3:0]A;
    reg [3:0]B;
    reg [3:0]C;
    reg [3:0]D;
    
    wire CLK;
    wire T;   
    wire clk190,clk48,clk_4hz;
    
 
    clkdiv g1(mclk,clk190,clk48,clk_4hz);
    assign CLK=(P==1'b1)?clk48:clk_4hz;
   
    
    
    always@(posedge CLK)
    
    begin
        if(A!=4'b1001)
        begin
        A<=A+1;
        end;
       if(A==4'b1001&&B!=4'b0101)
          begin
            A<=4'b0000;
            B<=B+1;
          end
       else if(A==4'b1001&&B==4'b0101&&
       ((C!=4'b1001&&(D==4'b0001||
       D==4'b0000))||
       (C!=4'b0011&&D==4'b0010)))
           begin 
            C<=C+1;
            A<=4'b0000;
            B<=4'b0000;
           end
        else 
        if(A==4'b1001&&B==4'b0101&&
        (D==4'b0000||D==4'b0001)&&C==4'b1001)
            begin
            C<=4'b0000;
            D<=D+1;
            A<=4'b0000;
            B<=4'b0000;
            end
        else 
        if(A==4'b1001&&B==4'b0101&&
        D==4'b0010&&C==4'b0011)
            begin
            A<=4'b0000;
            B<=4'b0000;
            C<=4'b0000;
            D<=4'b0000;
            end
    end
endmodule