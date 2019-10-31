`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/20 22:24:50
// Design Name: 
// Module Name: lab6_22
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
module tengo(input clk,input [3:0]a,
             output cin,output reg [3:0]q
              );
        assign    cin=a[3]   
      always@(posedge clk)  
         if(a[])  q<=4'b0000; 
         else q<=q+1'b1;    
endmodule


module lab6_22(
        input go,clk,
        output reg [6:0]g,output reg [3:0]an
    );
    
    always@(posedge clk)
        if(go)
        begin
           
        
        end
    
endmodule
