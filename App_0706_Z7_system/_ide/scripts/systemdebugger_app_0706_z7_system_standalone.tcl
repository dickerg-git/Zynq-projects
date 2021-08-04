# Usage with Vitis IDE:
# In Vitis IDE create a Single Application Debug launch configuration,
# change the debug type to 'Attach to running target' and provide this 
# tcl script in 'Execute Script' option.
# Path of this script: C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_0706_Z7_system\_ide\scripts\systemdebugger_app_0706_z7_system_standalone.tcl
# 
# 
# Usage with xsct:
# To debug using xsct, launch xsct and run below command
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\App_0706_Z7_system\_ide\scripts\systemdebugger_app_0706_z7_system_standalone.tcl
# 
connect -url tcp:127.0.0.1:3121
targets -set -nocase -filter {name =~"APU*"}
rst -system
after 3000
targets -set -filter {jtag_cable_name =~ "Digilent Arty Z7 003017B300C9A" && level==0 && jtag_device_ctx=="jsn-Arty Z7-003017B300C9A-23727093-0"}
fpga -file C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0706_Z7/_ide/bitstream/Z7_CPU_0_wrapper.bit
targets -set -nocase -filter {name =~"APU*"}
loadhw -hw C:/Users/roger.dickerson/Projects/Xilinx/workspace/BSP_0727_LED_EN/export/BSP_0727_LED_EN/hw/Z7_CPU_0_wrapper_0727.xsa -mem-ranges [list {0x40000000 0xbfffffff}] -regs
configparams force-mem-access 1
targets -set -nocase -filter {name =~"APU*"}
source C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0706_Z7/_ide/psinit/ps7_init.tcl
ps7_init
ps7_post_config
targets -set -nocase -filter {name =~ "*A9*#0"}
dow C:/Users/roger.dickerson/Projects/Xilinx/workspace/App_0706_Z7/Debug/App_0706_Z7.elf
configparams force-mem-access 0
bpadd -addr &main
