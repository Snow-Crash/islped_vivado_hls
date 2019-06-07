############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 1986-2017 Xilinx, Inc. All Rights Reserved.
############################################################
set_directive_interface -mode ap_memory "neuron" weight
set_directive_pipeline "neuron/loop_spike"
set_directive_pipeline "neuron/loop_syn"
set_directive_interface -mode s_axilite "neuron"
set_directive_interface -mode ap_ctrl_hs "neuron"
set_directive_interface -mode axis -register "neuron" psp
set_directive_interface -mode axis -register "neuron" voltage
set_directive_interface -mode axis -register "neuron" test_out
set_directive_interface -mode s_axilite "neuron" test_var
set_directive_interface -mode s_axilite "neuron" input_spike_127_64
set_directive_interface -mode s_axilite "neuron" input_spike_63_0
set_directive_interface -mode s_axilite "neuron" reset_neuron
