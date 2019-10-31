`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/06 11:47:16
// Design Name: 
// Module Name: lab3_3
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
module lab1(input   a,b,
            output  c    );
            
          assign c=(a&~b)|(~a&b);    
            
  endmodule
module lab2(input   [3:0]g,input [3:0]p,input cc,
               output  [2:0]c,output s    );
               
          assign c[0]=g[0]|(p[0]&cc);
          assign c[1]=g[1]|(p[1]&g[0])|(p[1]&p[0]&cc);
          assign c[2]=g[2]|(p[2]&g[1])|(p[2]&p[1]&g[0])|(p[2]&p[1]&p[0]&cc);
          assign s=g[3]|(p[3]&g[2])|(p[3]&p[2]&g[1])|(p[3]&p[2]&p[1]&g[0])|(p[3]&p[2]&p[1]&p[0]&cc);      
                        
      endmodule

module lab3_3(
      output [4:0] s,
      input [3:0]a,input [3:0]b,input cc
    );
    
    wire [3:0]p;wire [3:0]g;wire [2:0]c;
    
    assign p[0]=(a[0]&~b[0])|(~a[0]&b[0]);
    assign p[1]=(a[1]&~b[1])|(~a[1]&b[1]);
    assign p[2]=(a[2]&~b[2])|(~a[2]&b[2]);
    assign p[3]=(a[3]&~b[3])|(~a[3]&b[3]);
    
    assign g[0]=a[0]&b[0];
    assign g[1]=a[1]&b[1];
    assign g[2]=a[2]&b[2];
    assign g[3]=a[3]&b[3];
    
  
         lab2 lab21(g,p,cc,c,s[4]); 
   
     lab1 lab11(p[0],cc,s[0]),
          lab12(p[1],c[0],s[1]),
          lab13(p[2],c[1],s[2]),
          lab14(p[3],c[2],s[3]);
   
     
endmodule
