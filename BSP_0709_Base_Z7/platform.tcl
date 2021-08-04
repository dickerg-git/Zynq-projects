# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSP_0709_Base_Z7\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSP_0709_Base_Z7\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {BSP_0709_Base_Z7}\
-hw {C:\Users\roger.dickerson\Projects\Xilinx\workspace\Platform_0709_Base_Z7\Z7_Zynq_base_wrapper.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/roger.dickerson/Projects/Xilinx/workspace}

platform write
platform generate -domains 
platform active {BSP_0709_Base_Z7}
platform generate
bsp reload
bsp config stdout "ps7_uart_0"
bsp reload
bsp config stdin "ps7_coresight_comp_0"
bsp config stdout "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
bsp write
platform generate -domains standalone_domain 
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
platform active {BSP_0709_Base_Z7}
platform config -updatehw {C:/Users/roger.dickerson/Projects/Xilinx/workspace/Platform_0709_Base_Z7/Z7_Zynq_base_wrapper.xsa}
platform generate -domains 
bsp reload
bsp write
platform generate -domains 
