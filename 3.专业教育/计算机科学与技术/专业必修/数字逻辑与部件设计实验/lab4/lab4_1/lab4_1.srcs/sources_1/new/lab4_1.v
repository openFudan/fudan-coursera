`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/04 09:15:47
// Design Name: 
// Module Name: lab4_1
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

module lab3_2_2(input [7:0]a,input [7:0]b,input cc,
                  output  [7:0]s,output co);
        wire [6:0]w;
        lab3_2_1   lab1(a[0],b[0],cc,s[0],w[0]),
                   lab2(a[1],b[1],w[0],s[1],w[1]),
                   lab3(a[2],b[2],w[1],s[2],w[2]),
                   lab4(a[3],b[3],w[2],s[3],w[3]),
                   lab5(a[4],b[4],w[3],s[4],w[4]),
                   lab6(a[5],b[5],w[4],s[5],w[5]),
                   lab7(a[6],b[6],w[5],s[6],w[6]),
                   lab8(a[7],b[7],w[6],s[7],co);                   
  endmodule
module lab322( input [7:0]a,input [7:0]b,input cc,
                    output  [7:0]s,output co      );
         wire [7:0]bb;
         wire [7:0]ss;
         assign bb=(~(b+cc))+1'b1;
         lab3_2_2 lab1(a,bb,1'b0,ss,co);
         if(co)
           begin
             assign co=1'b0;
             assign s=ss;
           end
         else
           begin
             assign co=1'b1;
             assign s=(~ss)+1'b1;
           end       
endmodule                    
                    
module lab4_1(
                input[7:0]A,input[7:0]B,input cn,input s1,input s0,input m,
                output [7:0]F, output co
    );
     
         case({s1,s0})
         2'b00:
           begin
             if(!m) assign F=~A;
             else 
               begin
                
                     lab3_2_2 lab1( A, B, cn,  F, co);    //assign F=A+B;                               
                   //    lab3_2_2 lab2( A, B, cn,  F, co);      // assign F=A+B+1'b1;          
                   //{co,F}=(A+B)+cn;
               end
           end
          2'b01:
            begin
              if(!m) assign F=A&B;
              else
                begin
                lab322  lab2(A,B,cn,F,co);
                 // if(!cn) assign F=A-B;
                  //else assign F=A-B-2'b1;/////////////////////////
                end           
            end
           2'b10:
             begin
               if(!m) assign F=A|B;
             end
           2'b11:
             begin
               if(!m) assign F=A^B;
             end
          endcase
endmodule
