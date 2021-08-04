-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Tue Jul 27 11:18:26 2021
-- Host        : FTC-48JVN53 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/Users/roger.dickerson/Projects/Xilinx/workspace/Platform_0701_Z7/Platform_0701_Z7.gen/sources_1/bd/Z7_CPU_0/ip/Z7_CPU_0_led_control_0_4/Z7_CPU_0_led_control_0_4_stub.vhdl
-- Design      : Z7_CPU_0_led_control_0_4
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity Z7_CPU_0_led_control_0_4 is
  Port ( 
    led_state : in STD_LOGIC_VECTOR ( 3 downto 0 );
    led_en : in STD_LOGIC_VECTOR ( 3 downto 0 );
    led_out : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );

end Z7_CPU_0_led_control_0_4;

architecture stub of Z7_CPU_0_led_control_0_4 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "led_state[3:0],led_en[3:0],led_out[3:0]";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "led_control,Vivado 2020.2";
begin
end;
