`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name: lab1
//////////////////////////////////////////////////////////////////////////////////


module lab3_2_1(
    input A,B,C,
     output S,CO
    );
    wire [6:0] w;
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

module lab3_2_2(input [3:0]a,input [3:0]b,input cc,
                  output  [4:0]s);
        wire [2:0]w;
        lab3_2_1 lab1(a[0],b[0],cc,s[0],w[0]),
                   lab2(a[1],b[1],w[0],s[1],w[1]),
                   lab3(a[2],b[2],w[1],s[2],w[2]),
                   lab4(a[3],b[3],w[2],s[3],s[4]);        
                  
                  
  endmodule