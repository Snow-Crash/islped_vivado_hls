#include "neuron.h"
#include "CSVparser.hpp"


ap_uint<NEURON_NUM> neuron (ap_uint<64> input_spike_127_64, ap_uint<64> input_spike_63_0, hls::stream<ap_fixed<32,20> > &voltage,
		data_t weight[NEURON_NUM][INPUT_DIM], hls::stream<ap_fixed<32,20> > &psp, int reset_neuron, int test_var,
		hls::stream<ap_fixed<32,20> > &test_out)
{
	int neuron_idx;
	int synapse_idx;

	static data_t k1[INPUT_DIM];
	static data_t k2[INPUT_DIM];

	ap_uint<NEURON_NUM> output_spike = 0;

	if (reset_neuron == 1)
	{
		for (int i = 0; i != INPUT_DIM; i++)
		{
			k1[i] = 0;
			k2[i] = 0;
		}
		return output_spike;
	}

	//static data_t tau_m = 10;
	//static data_t tau_s = 2.5;
	static data_t decay_tau_m = 0.9048374;
	static data_t decay_tau_s = 0.67032;
	static data_t norm_factor = 2.1165;

	data_t new_k[INPUT_DIM];

	ap_uint<INPUT_DIM> input_spike = (input_spike_127_64, input_spike_63_0);

	loop_spike : for (synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
	{
		ap_fixed<32,20> new_k1 = k1[synapse_idx] * decay_tau_m + input_spike[synapse_idx];
		ap_fixed<32,20> new_k2 = k2[synapse_idx] * decay_tau_s + input_spike[synapse_idx];
		new_k[synapse_idx] = new_k1 - new_k2;
		psp.write(new_k1 - new_k2);
		k1[synapse_idx] = new_k1;
		k2[synapse_idx] = new_k2;
	}

	loop_neuron : for(neuron_idx = 0; neuron_idx != NEURON_NUM; neuron_idx++)
	{
		data_t acc_voltage = 0;

		loop_syn : for(synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
		{
			data_t new_psp = new_k[synapse_idx] * weight[neuron_idx][synapse_idx] * norm_factor;

			acc_voltage = acc_voltage + new_psp;
		}

		voltage.write(acc_voltage);

		if (acc_voltage > THRESHOLD)
			output_spike[neuron_idx] = 1;
	}

	for(int i = 0; i != 10; i++)
	{
		test_out.write(i+test_var);
	}


	return output_spike;
}
