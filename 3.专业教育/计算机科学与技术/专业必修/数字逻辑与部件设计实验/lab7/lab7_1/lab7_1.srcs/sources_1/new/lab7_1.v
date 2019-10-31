`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/26 19:08:22
// Design Name: 
// Module Name: lab7_1
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

module lab7_1(
                  input reset,a,b,CLK,
                  output reg [2:0]N,output reg [2:0]S,output reg [2:0]E,output reg [2:0]W
    );
    wire aclk;//get aclk
    reg [1:0]s;
    reg [1:0]ns;
    clkdiv clk1(CLK,aclk);
   reg A;
   reg B;
   reg [3:0]aa;
   reg [1:0]bb;
   
    always @(posedge aclk,negedge reset)
    
    if(!reset) 
    begin s[1]<=1'b0; s[0]<=1'b0;aa=4'b0000;bb=2'b00;end
    
    else   
    begin
     s<=ns;   
     begin
      if(bb[1]&bb[0]&b)  begin B=1'b1;bb=2'b00;end    
      else   begin B=1'b0;bb=bb+1'b1;end
      end
      begin
      if(aa[3]&~aa[2]&~aa[1]&aa[0]&a) begin  A=1'b1;aa=4'b0000; end
      else begin A=1'b0;aa=aa+1'b1;end
      end
      
      end
    
    
    
     always @(s,a,b)
      case(s[1:0])
      2'b00:begin
       begin S=3'b100;N=3'b100;W=3'b001;E=3'b001;end   
       if(B) begin ns=2'b01;end 
       end
      2'b01:begin
       begin S=3'b010;N=3'b010;W=3'b001;E=3'b001;end
       if(A) begin ns=2'b10;end 
       end
      2'b10:begin
      begin S=3'b001;N=3'b001;W=3'b100;E=3'b100;end
       if(B) begin ns=2'b11;end 
       end
       
      2'b11:begin 
       begin S=3'b001;N=3'b001;W=3'b010;E=3'b010;end
      if(A) begin ns=2'b00;end 
      end
      
      endcase
   
    
  
endmodule
