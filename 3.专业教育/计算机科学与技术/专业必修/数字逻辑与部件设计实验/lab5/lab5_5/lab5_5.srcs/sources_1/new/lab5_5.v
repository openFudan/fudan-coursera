`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/11/13 12:28:19
// Design Name: 
// Module Name: lab5_5
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

module lab5_4(   input R,A1,A0,SI,
                   output reg [7:0]Q
    );
    always @(R,A1,A0)
    if(!R) Q<=8'b00000000;
    else case({A1,A0})
      2'b00:;
      2'b01:Q<={SI,Q[6:0]};
      2'b10:Q<={Q[7:1],SI};
      2'b11:Q<=8'b11111111;
    endcase
endmodule


module lab5_5(
                  input R,A1,A0,SI,
                   output  [15:0]Q
    );
     always @(R,A1,A0)
     if(!R)
        lab5_4 lab5_4_1(R,A1,A0,SI,Q[15:8]),
             lab5_4_2(R,A1,A0,Q[8],Q[7:0]);//diao yong problem
   /*  else case({A1,A0})
                   2'b00:;
                   2'b01: lab5_4 lab5_4_1(R,A1,A0,SI,Q[15:8]),
                               lab5_4_2(R,A1,A0,Q[8],Q[7:0]);
                   2'b10: lab5_4 lab5_4_1(R,A1,A0,Q[7],Q[15:8]),
                                    lab5_4_2(R,A1,A0,SI,Q[7:0]);
                   2'b11: lab5_4 lab5_4_1(R,A1,A0,SI,Q[15:8]),
                               lab5_4_2(R,A1,A0,Q[8],Q[7:0]);
                 endcase
    */
    
endmodule
