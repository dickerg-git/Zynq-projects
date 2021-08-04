-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.2 (win64) Build 3064766 Wed Nov 18 09:12:45 MST 2020
-- Date        : Tue Jul 27 11:18:26 2021
-- Host        : FTC-48JVN53 running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               c:/Users/roger.dickerson/Projects/Xilinx/workspace/Platform_0701_Z7/Platform_0701_Z7.gen/sources_1/bd/Z7_CPU_0/ip/Z7_CPU_0_led_control_0_4/Z7_CPU_0_led_control_0_4_sim_netlist.vhdl
-- Design      : Z7_CPU_0_led_control_0_4
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity Z7_CPU_0_led_control_0_4_led_control is
  port (
    led_out : out STD_LOGIC_VECTOR ( 3 downto 0 );
    led_state : in STD_LOGIC_VECTOR ( 3 downto 0 );
    led_en : in STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of Z7_CPU_0_led_control_0_4_led_control : entity is "led_control";
end Z7_CPU_0_led_control_0_4_led_control;

architecture STRUCTURE of Z7_CPU_0_led_control_0_4_led_control is
begin
\led_out[0]_INST_0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => led_state(0),
      I1 => led_en(0),
      O => led_out(0)
    );
\led_out[1]_INST_0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => led_state(1),
      I1 => led_en(1),
      O => led_out(1)
    );
\led_out[2]_INST_0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => led_state(2),
      I1 => led_en(2),
      O => led_out(2)
    );
\led_out[3]_INST_0\: unisim.vcomponents.LUT2
    generic map(
      INIT => X"2"
    )
        port map (
      I0 => led_state(3),
      I1 => led_en(3),
      O => led_out(3)
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity Z7_CPU_0_led_control_0_4 is
  port (
    led_state : in STD_LOGIC_VECTOR ( 3 downto 0 );
    led_en : in STD_LOGIC_VECTOR ( 3 downto 0 );
    led_out : out STD_LOGIC_VECTOR ( 3 downto 0 )
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of Z7_CPU_0_led_control_0_4 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of Z7_CPU_0_led_control_0_4 : entity is "Z7_CPU_0_led_control_0_4,led_control,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of Z7_CPU_0_led_control_0_4 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of Z7_CPU_0_led_control_0_4 : entity is "module_ref";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of Z7_CPU_0_led_control_0_4 : entity is "led_control,Vivado 2020.2";
end Z7_CPU_0_led_control_0_4;

architecture STRUCTURE of Z7_CPU_0_led_control_0_4 is
begin
inst: entity work.Z7_CPU_0_led_control_0_4_led_control
     port map (
      led_en(3 downto 0) => led_en(3 downto 0),
      led_out(3 downto 0) => led_out(3 downto 0),
      led_state(3 downto 0) => led_state(3 downto 0)
    );
end STRUCTURE;
