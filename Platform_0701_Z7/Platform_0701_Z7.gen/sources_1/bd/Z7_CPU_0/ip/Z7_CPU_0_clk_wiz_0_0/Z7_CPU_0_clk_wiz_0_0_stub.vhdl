-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Tue Jul  6 19:44:31 2021
-- Host        : FTC-48JVN53 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/roger.dickerson/Projects/Xilinx/workspace/Platform_0701_Z7/Platform_0701_Z7.gen/sources_1/bd/Z7_CPU_0/ip/Z7_CPU_0_clk_wiz_0_0/Z7_CPU_0_clk_wiz_0_0_stub.vhdl
-- Design      : Z7_CPU_0_clk_wiz_0_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Z7_CPU_0_clk_wiz_0_0 is
  Port ( 
    clk_out1 : out STD_LOGIC;
    reset : in STD_LOGIC;
    locked : out STD_LOGIC;
    clk_in1 : in STD_LOGIC
  );

end Z7_CPU_0_clk_wiz_0_0;

architecture stub of Z7_CPU_0_clk_wiz_0_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "clk_out1,reset,locked,clk_in1";
begin
end;
