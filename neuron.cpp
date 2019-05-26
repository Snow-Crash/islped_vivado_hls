#include "neuron.h"
#include "CSVparser.hpp"


#define TWO_D_INPUT
#define WEIGHT_AS_ROM


//
//void init_weight(data_t weight[NEURON_NUM][INPUT_DIM])
//{
//	csv::Parser file = csv::Parser("weight.csv");
//	int row_num = file.rowCount();
//	int col_num = file.columnCount();
//
//	for (int i = 0; i != row_num; i++)
//		for (int j = 0; j != col_num; j++)
//		{
//			weight[i][j] = std::stof()
//		}
//
//}
//
//void neuron (ap_uint<INPUT_DIM> input_spike,ap_uint<NEURON_NUM> output_spike,
//		data_t voltage[NEURON_NUM], data_t k1[INPUT_DIM],data_t k2[INPUT_DIM])
//{
//	int neuron_idx;
//	int synapse_idx;
//
//	static data_t tau_m = 10;
//	static data_t tau_s = 2.5;
//	static data_t decay_tau_m = 0.9048374;
//	static data_t decay_tau_s = 0.67032;
//	static data_t norm_factor = 2.1165;
//
//	static data_t weight[NEURON_NUM][INPUT_DIM];
//
//	data_t new_k[INPUT_DIM];
//
//	loop_spike : for (synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
//	{
//		data_t new_k1 = k1[synapse_idx] * decay_tau_m + input_spike[synapse_idx];
//		data_t new_k2 = k2[synapse_idx] * decay_tau_s + input_spike[synapse_idx];
//		new_k[synapse_idx] = new_k1 - new_k2;
//
//		k1[synapse_idx] = new_k1;
//		k2[synapse_idx] = new_k2;
//	}
//
//	int weight_address = 0;
//	loop_neuron : for(neuron_idx = 0; neuron_idx != NEURON_NUM; neuron_idx++)
//	{
//		data_t acc_voltage = 0;
//
//		loop_syn : for(synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
//		{
//			data_t new_psp = new_k[synapse_idx] * weight[neuron_idx][synapse_idx] * norm_factor;
//
//			acc_voltage = acc_voltage + new_psp;
//			weight_address++;
//		}
//
//		voltage[neuron_idx] = acc_voltage;
//
//		if (acc_voltage > THRESHOLD)
//			output_spike[neuron_idx] = 0;
//		else
//			output_spike[neuron_idx] = 1;
//	}
//}

#ifdef TWO_D_INPUT



void neuron (ap_uint<INPUT_DIM> input_spike, ap_uint<NEURON_NUM> output_spike,
		data_t voltage[NEURON_NUM], data_t weight[NEURON_NUM][INPUT_DIM],
		data_t k1[INPUT_DIM],data_t k2[INPUT_DIM])
{
	int neuron_idx;
	int synapse_idx;

	static data_t tau_m = 10;
	static data_t tau_s = 2.5;
	static data_t decay_tau_m = 0.9048374;
	static data_t decay_tau_s = 0.67032;
	static data_t norm_factor = 2.1165;

	data_t new_k[INPUT_DIM];

	loop_spike : for (synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
	{
		data_t new_k1 = k1[synapse_idx] * decay_tau_m + input_spike[synapse_idx];
		data_t new_k2 = k2[synapse_idx] * decay_tau_s + input_spike[synapse_idx];
		new_k[synapse_idx] = new_k1 - new_k2;

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

		voltage[neuron_idx] = acc_voltage;

		if (acc_voltage > THRESHOLD)
			output_spike[neuron_idx] = 0;
		else
			output_spike[neuron_idx] = 1;
	}
}


#else

void neuron (ap_uint<INPUT_DIM> input_spike,ap_uint<NEURON_NUM> output_spike,
		data_t voltage[NEURON_NUM], data_t weight[NEURON_NUM * INPUT_DIM],
		data_t k1[INPUT_DIM],data_t k2[INPUT_DIM])
{
	int neuron_idx;
	int synapse_idx;

	static data_t tau_m = 10;
	static data_t tau_s = 2.5;
	static data_t decay_tau_m = 0.9048374;
	static data_t decay_tau_s = 0.67032;
	static data_t norm_factor = 2.1165;

	data_t new_k[INPUT_DIM];

	loop_spike : for (synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
	{
		data_t new_k1 = k1[synapse_idx] * decay_tau_m + input_spike[synapse_idx];
		data_t new_k2 = k2[synapse_idx] * decay_tau_s + input_spike[synapse_idx];
		new_k[synapse_idx] = new_k1 - new_k2;

		k1[synapse_idx] = new_k1;
		k2[synapse_idx] = new_k2;

	}

	int weight_address = 0;
	loop_neuron : for(neuron_idx = 0; neuron_idx != NEURON_NUM; neuron_idx++)
	{
		data_t acc_voltage = 0;

		loop_syn : for(synapse_idx = 0; synapse_idx != INPUT_DIM; synapse_idx++)
		{
			//data_t new_psp = new_k[synapse_idx] * weight[neuron_idx*NEURON_NUM + synapse_idx] * NORM_FACTOR;
			data_t new_psp = new_k[synapse_idx] * weight[weight_address] * norm_factor;

			acc_voltage = acc_voltage + new_psp;
			weight_address++;
		}

		voltage[neuron_idx] = acc_voltage;

		if (acc_voltage > THRESHOLD)
			output_spike[neuron_idx] = 0;
		else
			output_spike[neuron_idx] = 1;
	}
}

#endif
