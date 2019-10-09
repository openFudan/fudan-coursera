module SevenSegmentDisplay(
    input  logic   [3:0] SW,
    output logic  [6:0] A2G); 
    always_comb
    case (SW) 
        4'h0: A2G = 7'b1000000; 
        4'h1: A2G = 7'b1111001; 
        4'h2: A2G = 7'b0100100; 
        4'h3: A2G = 7'b0110000; 
        4'h4: A2G = 7'b0011001; 
        4'h5: A2G = 7'b0010010; 
        4'h6: A2G = 7'b0000010; 
        4'h7: A2G = 7'b1111000; 
        4'h8: A2G = 7'b0000000; 
        4'h9: A2G = 7'b0010000; 
        4'hA: A2G = 7'b0001000; 
        4'hB: A2G = 7'b0000011; 
        4'hC: A2G = 7'b1000110; 
        4'hD: A2G = 7'b0100001; 
        4'hE: A2G = 7'b0000110; 
        4'hF: A2G = 7'b0001110; 
     default: A2G = 7'b1000000; //0
    endcase 
endmodule
