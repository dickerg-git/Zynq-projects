# 
# Usage: To re-create this platform project launch xsct with below options.
# xsct C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSD_0805_Z7\platform.tcl
# 
# OR launch xsct and run below command.
# source C:\Users\roger.dickerson\Projects\Xilinx\workspace\BSD_0805_Z7\platform.tcl
# 
# To create the platform in a different location, modify the -out option of "platform create" command.
# -out option specifies the output directory of the platform project.

platform create -name {BSD_0805_Z7}\
-hw {C:\Users\roger.dickerson\Projects\Xilinx\GIT Workspace\Zynq-projects\Platform_0709_Base_Z7\Z7_Zynq_base_wrapper_0805a.xsa}\
-proc {ps7_cortexa9_0} -os {standalone} -fsbl-target {psu_cortexa53_0} -out {C:/Users/roger.dickerson/Projects/Xilinx/workspace}

platform write
platform generate -domains 
platform active {BSD_0805_Z7}
platform generate
