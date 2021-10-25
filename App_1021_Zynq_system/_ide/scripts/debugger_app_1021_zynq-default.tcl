# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_1021_Zynq_system\_ide\scripts\debugger_app_1021_zynq-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_1021_Zynq_system\_ide\scripts\debugger_app_1021_zynq-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent JTAG-HS3 210299B14C2B" && level==0 && jtag_device_ctx=="jsn-JTAG-HS3-210299B14C2B-23727093-0"}
fpga -file C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_1021_Zynq/_ide/bitstream/scorpius13MDlp7z020_debug.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/roger.dickerson/Projects/Xilinx/workspace/Platform_0629_Arm/export/Platform_0629_Arm/hw/scorpius13MDlp7z020_debug.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_1021_Zynq/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_1021_Zynq/Debug/App_1021_Zynq.elf
configparams force-mem-access 0
bpadd -addr &main
