module lab1(
input  G1, G2A,G2B,
    [2:0] S,
     output [7:0] Y
    );
   
   
    assign Y[0] =(G1&~G2A&~G2B)?( S[0]|S[1]|S[2]) :~(G1&~G2A&~G2B);
    assign Y[1] =(G1&~G2A&~G2B)? (~S[0]|S[1]|S[2]):~(G1&~G2A&~G2B);
    assign Y[2] =(G1&~G2A&~G2B)? (S[0]| ~S[1]|S[2]) :~(G1&~G2A&~G2B);
    assign Y[3] =(G1&~G2A&~G2B)?  (~S[0]| ~S[1]|S[2]) :~(G1&~G2A&~G2B);
    assign Y[4] =(G1&~G2A&~G2B)? (S[0]|S[1]| ~S[2]) :~(G1&~G2A&~G2B);
    assign Y[5] =(G1&~G2A&~G2B)? (~ S[0]|S[1]| ~S[2] ):~(G1&~G2A&~G2B);
    assign Y[6] =(G1&~G2A&~G2B)? (S[0]| ~S[1]| ~S[2] ):~(G1&~G2A&~G2B);
    assign Y[7] =(G1&~G2A&~G2B)?  (~S[0]| ~S[1]| ~S[2]) :~(G1&~G2A&~G2B);   

 
    
endmodule
