`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:25:44
// Design Name: 
// Module Name: lab5_2_2
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

module JK_T ( input T, Clk,set,clr, output reg Q);
 
  always @ ( posedge Clk,posedge set, posedge clr)
      if (set) 
     Q <= 1'b1; 
    else if (clr)
     Q<= 1'b0;

     else if(T)  
      Q <= !Q;  

endmodule

module  TtoD( input T, Clk,set,clr, output  D     );
        reg q;
       JK_T  tkt1(T, Clk,set,clr,q);
       assign D=T&~q|~T&q;
       
       
endmodule