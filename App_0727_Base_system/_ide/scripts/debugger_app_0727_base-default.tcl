# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_0727_Base_system\_ide\scripts\debugger_app_0727_base-default.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_0727_Base_system\_ide\scripts\debugger_app_0727_base-default.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Arty Z7 003017B300C9A" && level==0 && jtag_device_ctx=="jsn-Arty Z7-003017B300C9A-23727093-0"}
fpga -file C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0727_Base/_ide/bitstream/Z7_Zynq_base_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/roger.dickerson/Projects/Xilinx/workspace/BSP_0709_Base_Z7/export/BSP_0709_Base_Z7/hw/Z7_Zynq_base_wrapper.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0727_Base/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0727_Base/Debug/App_0727_Base.elf
configparams force-mem-access 0
targets -set -nocase -filter {name =~ "*A9*#0"}
con
