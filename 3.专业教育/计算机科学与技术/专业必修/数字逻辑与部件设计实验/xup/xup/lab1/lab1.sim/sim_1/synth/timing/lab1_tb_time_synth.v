// Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2015.2 (win64) Build 1266856 Fri Jun 26 16:35:25 MDT 2015
// Date        : Fri Aug 05 15:02:08 2016
// Host        : ta222 running 64-bit major release  (build 9200)
// Command     : write_verilog -mode timesim -nolib -sdf_anno true -force -file
//               F:/xup/lab1/lab1.sim/sim_1/synth/timing/lab1_tb_time_synth.v
// Design      : lab1
// Purpose     : This verilog netlist is a timing simulation representation of the design and should not be modified or
//               synthesized. Please ensure that this netlist is used with the corresponding SDF file.
// Device      : xc7a35tcpg236-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps
`define XIL_TIMING

(* NotValidForBitStream *)
module lab1
   (swt,
    led);
  input [7:0]swt;
  output [7:0]led;

  wire [7:0]led;
  wire [7:0]led_OBUF;
  wire [7:0]swt;
  wire [3:0]swt_IBUF;

initial begin
 $sdf_annotate("lab1_tb_time_synth.sdf",,,,"tool_control");
end
  OBUF \led_OBUF[0]_inst 
       (.I(led_OBUF[0]),
        .O(led[0]));
  LUT1 #(
    .INIT(2'h1)) 
    \led_OBUF[0]_inst_i_1 
       (.I0(swt_IBUF[0]),
        .O(led_OBUF[0]));
  OBUF \led_OBUF[1]_inst 
       (.I(led_OBUF[1]),
        .O(led[1]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT2 #(
    .INIT(4'h2)) 
    \led_OBUF[1]_inst_i_1 
       (.I0(swt_IBUF[1]),
        .I1(swt_IBUF[2]),
        .O(led_OBUF[1]));
  OBUF \led_OBUF[2]_inst 
       (.I(led_OBUF[2]),
        .O(led[2]));
  (* SOFT_HLUTNM = "soft_lutpair0" *) 
  LUT3 #(
    .INIT(8'hAC)) 
    \led_OBUF[2]_inst_i_1 
       (.I0(swt_IBUF[3]),
        .I1(swt_IBUF[1]),
        .I2(swt_IBUF[2]),
        .O(led_OBUF[2]));
  OBUF \led_OBUF[3]_inst 
       (.I(led_OBUF[3]),
        .O(led[3]));
  LUT2 #(
    .INIT(4'h8)) 
    \led_OBUF[3]_inst_i_1 
       (.I0(swt_IBUF[3]),
        .I1(swt_IBUF[2]),
        .O(led_OBUF[3]));
  OBUF \led_OBUF[4]_inst 
       (.I(led_OBUF[4]),
        .O(led[4]));
  OBUF \led_OBUF[5]_inst 
       (.I(led_OBUF[5]),
        .O(led[5]));
  OBUF \led_OBUF[6]_inst 
       (.I(led_OBUF[6]),
        .O(led[6]));
  OBUF \led_OBUF[7]_inst 
       (.I(led_OBUF[7]),
        .O(led[7]));
  IBUF \swt_IBUF[0]_inst 
       (.I(swt[0]),
        .O(swt_IBUF[0]));
  IBUF \swt_IBUF[1]_inst 
       (.I(swt[1]),
        .O(swt_IBUF[1]));
  IBUF \swt_IBUF[2]_inst 
       (.I(swt[2]),
        .O(swt_IBUF[2]));
  IBUF \swt_IBUF[3]_inst 
       (.I(swt[3]),
        .O(swt_IBUF[3]));
  IBUF \swt_IBUF[4]_inst 
       (.I(swt[4]),
        .O(led_OBUF[4]));
  IBUF \swt_IBUF[5]_inst 
       (.I(swt[5]),
        .O(led_OBUF[5]));
  IBUF \swt_IBUF[6]_inst 
       (.I(swt[6]),
        .O(led_OBUF[6]));
  IBUF \swt_IBUF[7]_inst 
       (.I(swt[7]),
        .O(led_OBUF[7]));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    tri1 p_up_tmp;
    tri (weak1, strong0) PLL_LOCKG = p_up_tmp;

    wire PROGB_GLBL;
    wire CCLKO_GLBL;
    wire FCSBO_GLBL;
    wire [3:0] DO_GLBL;
    wire [3:0] DI_GLBL;
   
    reg GSR_int;
    reg GTS_int;
    reg PRLD_int;

//--------   JTAG Globals --------------
    wire JTAG_TDO_GLBL;
    wire JTAG_TCK_GLBL;
    wire JTAG_TDI_GLBL;
    wire JTAG_TMS_GLBL;
    wire JTAG_TRST_GLBL;

    reg JTAG_CAPTURE_GLBL;
    reg JTAG_RESET_GLBL;
    reg JTAG_SHIFT_GLBL;
    reg JTAG_UPDATE_GLBL;
    reg JTAG_RUNTEST_GLBL;

    reg JTAG_SEL1_GLBL = 0;
    reg JTAG_SEL2_GLBL = 0 ;
    reg JTAG_SEL3_GLBL = 0;
    reg JTAG_SEL4_GLBL = 0;

    reg JTAG_USER_TDO1_GLBL = 1'bz;
    reg JTAG_USER_TDO2_GLBL = 1'bz;
    reg JTAG_USER_TDO3_GLBL = 1'bz;
    reg JTAG_USER_TDO4_GLBL = 1'bz;

    assign (weak1, weak0) GSR = GSR_int;
    assign (weak1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;

    initial begin
	GSR_int = 1'b1;
	PRLD_int = 1'b1;
	#(ROC_WIDTH)
	GSR_int = 1'b0;
	PRLD_int = 1'b0;
    end

    initial begin
	GTS_int = 1'b1;
	#(TOC_WIDTH)
	GTS_int = 1'b0;
    end

endmodule
`endif
