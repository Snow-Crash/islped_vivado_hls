############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
open_project hls
set_top neuron
add_files neuron.cpp
add_files neuron.h
add_files -tb CSVparser.cpp -cflags "-std=c++0x"
add_files -tb CSVparser.hpp -cflags "-std=c++0x"
add_files -tb neuron_test.cpp
add_files -tb tb_inputspike.csv
add_files -tb tb_outputspike.csv
add_files -tb tb_potential.csv
add_files -tb tb_weight.csv
open_solution "solution2"
set_part {xc7a100tcsg324-1}
create_clock -period 100MHz -name default
source "./hls/solution2/directives.tcl"
csim_design -clean
csynth_design
cosim_design -trace_level port -tool modelsim
export_design -rtl verilog -format ip_catalog
