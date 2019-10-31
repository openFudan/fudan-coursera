`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2016/12/05 08:48:57
// Design Name: 
// Module Name: lab4_1_1
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

module lab4_1(   input [2:0]f,input [3:0]a,input [3:0]b,
                 output reg [3:0]y,output reg zf,output reg nf,output reg ovf,output reg cf
                         );
   
        always@(f,a,b) begin
        case({f})
        3'b000:
          begin
             y=a;
            cf=1'b0;
            ovf=1'b0; 
           
          end
        3'b001:
          begin
             {cf,y}=a+b;
            
              ovf=(((y[3]^a[3])^b[3])^cf); 
           
          end
        3'b010:
          begin
           {cf,y}=a-b;
       
           ovf=(((y[3]^a[3])^b[3])^cf); 
       
          end
        3'b011:
          begin
          {cf,y}=b-a;
      
          ovf=(((y[3]^a[3])^b[3])^cf); 
         
          end
        3'b100:
          begin
             y=~a;
          
          end
        3'b101:
          begin
           y=a&b;
          
          end
        3'b110:
          begin
           y=a|b;
          
          end
        3'b111:
          begin
           y=a^b;
          
          end
        endcase
        
        if(y[3])  nf=1'b1;
        else  nf=1'b0;
                            
        if(~y[3]&~y[2]&~y[1]&~y[0]) zf=1'b1;
        else  zf=1'b0;
     end   
  endmodule


