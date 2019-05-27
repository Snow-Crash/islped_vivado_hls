############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_interface -mode ap_none "neuron" input_spike
set_directive_interface -mode ap_memory "neuron" voltage
set_directive_interface -mode ap_memory "neuron" weight
set_directive_interface -mode ap_memory "neuron" k1
set_directive_interface -mode ap_memory "neuron" k2
set_directive_pipeline "neuron/loop_spike"
set_directive_pipeline "neuron/loop_syn"
set_directive_interface -mode ap_ctrl_hs "neuron"
