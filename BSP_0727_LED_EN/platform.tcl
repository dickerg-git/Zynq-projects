# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSP_0727_LED_EN\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSP_0727_LED_EN\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {BSP_0727_LED_EN}\
-hw {C:\Users\roger.dickerson\Projects\Xilinx\workspace\Platform_0701_Z7\Z7_CPU_0_wrapper_0727.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/roger.dickerson/Projects/Xilinx/workspace}

platform write
platform generate -domains 
platform active {BSP_0727_LED_EN}
bsp reload
bsp config stdout "ps7_coresight_comp_0"
bsp config stdin "ps7_coresight_comp_0"
bsp write
bsp reload
catch {bsp regenerate}
domain active {zynq_fsbl}
bsp reload
bsp reload
platform generate
platform clean
platform generate
platform clean
platform generate
platform clean
platform generate
