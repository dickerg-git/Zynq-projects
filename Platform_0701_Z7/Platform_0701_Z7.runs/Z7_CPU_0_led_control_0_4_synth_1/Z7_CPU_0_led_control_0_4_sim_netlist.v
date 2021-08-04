// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
// Date        : Tue Jul 27 11:18:26 2021
// Host        : FTC-48JVN53 running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode funcsim -rename_top decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix -prefix
//               decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_ Z7_CPU_0_led_control_0_4_sim_netlist.v
// Design      : Z7_CPU_0_led_control_0_4
// Purpose     : This verilog netlist is a functional simulation representation of the design and should not be modified
//               or synthesized. This netlist cannot be used for SDF annotated simulation.
// Device      : xc7z020clg400-1
// --------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

(* CHECK_LICENSE_TYPE = "Z7_CPU_0_led_control_0_4,led_control,{}" *) (* DowngradeIPIdentifiedWarnings = "yes" *) (* IP_DEFINITION_SOURCE = "module_ref" *) 
(* X_CORE_INFO = "led_control,Vivado 2020.2" *) 
(* NotValidForBitStream *)
module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix
   (led_state,
    led_en,
    led_out);
  input [3:0]led_state;
  input [3:0]led_en;
  output [3:0]led_out;

  wire [3:0]led_en;
  wire [3:0]led_out;
  wire [3:0]led_state;

  decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_led_control inst
       (.led_en(led_en),
        .led_out(led_out),
        .led_state(led_state));
endmodule

module decalper_eb_ot_sdeen_pot_pi_dehcac_xnilix_led_control
   (led_out,
    led_state,
    led_en);
  output [3:0]led_out;
  input [3:0]led_state;
  input [3:0]led_en;

  wire [3:0]led_en;
  wire [3:0]led_out;
  wire [3:0]led_state;

  LUT2 #(
    .INIT(4'h2)) 
    \led_out[0]_INST_0 
       (.I0(led_state[0]),
        .I1(led_en[0]),
        .O(led_out[0]));
  LUT2 #(
    .INIT(4'h2)) 
    \led_out[1]_INST_0 
       (.I0(led_state[1]),
        .I1(led_en[1]),
        .O(led_out[1]));
  LUT2 #(
    .INIT(4'h2)) 
    \led_out[2]_INST_0 
       (.I0(led_state[2]),
        .I1(led_en[2]),
        .O(led_out[2]));
  LUT2 #(
    .INIT(4'h2)) 
    \led_out[3]_INST_0 
       (.I0(led_state[3]),
        .I1(led_en[3]),
        .O(led_out[3]));
endmodule
`ifndef GLBL
`define GLBL
`timescale  1 ps / 1 ps

module glbl ();

    parameter ROC_WIDTH = 100000;
    parameter TOC_WIDTH = 0;
    parameter GRES_WIDTH = 10000;
    parameter GRES_START = 10000;

//--------   STARTUP Globals --------------
    wire GSR;
    wire GTS;
    wire GWE;
    wire PRLD;
    wire GRESTORE;
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
    reg GRESTORE_int;

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

    assign (strong1, weak0) GSR = GSR_int;
    assign (strong1, weak0) GTS = GTS_int;
    assign (weak1, weak0) PRLD = PRLD_int;
    assign (strong1, weak0) GRESTORE = GRESTORE_int;

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

    initial begin 
	GRESTORE_int = 1'b0;
	#(GRES_START);
	GRESTORE_int = 1'b1;
	#(GRES_WIDTH);
	GRESTORE_int = 1'b0;
    end

endmodule
`endif
