`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/10/31 09:08:27
// Design Name: 
// Module Name: lab2
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
module lab2(
input  A,B,C,D,
     output a,b,c,d,e,f,g,[7:0]AN
    );
   
   
    assign a =((~D)&(~C)&(~B)&(A))|((~D)&(C)&(~B)&(~A));
    assign b =((~D)&(C)&(~B)&(A))|((~D)&(C)&(B)&(~A));
    assign c =((~D)&(~C)&(B)&(~A));
    assign d =(A&(~B)&(~C))|(C&(~D)&((A&B)|((~A)&(~D))));
    assign e =(((A&B)|(~B))&C&(~D))|((A&~C)&(~D|(~B&D)));
    assign f =((~C&~D)&(B|~B&A))|((~D)&(C)&(B)&(A));
    assign g =(~B&~C&~D)|((~D)&(C)&(B)&(A));  
   assign AN[0]=1'b0;
   assign AN[1]=1'b1;
    assign AN[2]=1'b0;
     assign AN[3]=1'b1;
      assign AN[4]=1'b0;
       assign AN[5]=1'b1;
        assign AN[6]=1'b0;
         assign AN[7]=1'b1;
/*assign a =((~D)&(~C)&(~B)&(A))|((~D)&(C)&(~B)&(~A));
       assign b =((~D)&(C)&(~B)&(A))|((~D)&(C)&(B)&(~A));
       assign c =((~D)&(~C)&(B)&(~A));
       assign d =((~D)&(~C)&(~B)&(A))|((~D)&(C)&(~B)&(~A))|((~D)&(C)&(B)&(A))|((D)&(~C)&(~B)&(A));
       assign e =((~D)&(~C)&(~B)&(A))|((~D)&(~C)&(B)&(A))|((~D)&(C)&(~B)&(~A))|((~D)&(C)&(~B)&(A))|((~D)&(C)&(B)&(A))|((D)&(~C)&(~B)&(A));
       assign f =((~D)&(~C)&(~B)&(A))|((~D)&(~C)&(B)&(~A))|((~D)&(~C)&(B)&(A))|((~D)&(C)&(B)&(A));
       assign g =((~D)&(~C)&(~B)&(~A))|((~D)&(~C)&(~B)&(A))|((~D)&(C)&(B)&(A));
 */
    
endmodule
