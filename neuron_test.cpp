
#include <stdio.h>
#include "neuron.h"

//https://github.com/rsylvian/CSVparser
#include "CSVparser.hpp"

int main()
{

	//read reference membrane potential
	float ref_potential[NEURON_NUM][WINDOW];
	csv::Parser potentialfile = csv::Parser("tb_potential.csv");
	int row_num = potentialfile.rowCount();
	int col_num = potentialfile.columnCount();

	for (int i = 0; i != row_num; i++)
	{
		for (int j = 0; j != col_num; j++)
		{
			ref_potential[i][j] = atof(potentialfile[i][j].c_str());
			//std::cout << file[i][j].c_str() << ",";
			//std::cout << weight[i][j] << "\n";
		}
	}

	//read input spike
	int input_spike[INPUT_DIM][WINDOW];
	csv::Parser inputspikefile = csv::Parser("tb_inputspike.csv");
	row_num = inputspikefile.rowCount();
	col_num = inputspikefile.columnCount();
	for (int i = 0; i != row_num; i++)
	{
		for (int j = 0; j != col_num; j++)
		{
			input_spike[i][j] = atoi(inputspikefile[i][j].c_str());
			//std::cout << spikefile[i][j].c_str() << ",";
			//std::cout << input_spike[i][j] << "\n";
		}
	}

	//  read reference output spike
	int ref_output_spike[NEURON_NUM][WINDOW];
	csv::Parser outputspikefile = csv::Parser("tb_outputspike.csv");
	row_num = outputspikefile.rowCount();
	col_num = outputspikefile.columnCount();
	for (int i = 0; i != row_num; i++)
	{
		for (int j = 0; j != col_num; j++)
		{
			ref_output_spike[i][j] = atoi(outputspikefile[i][j].c_str());
			//std::cout << spikefile[i][j].c_str() << ",";
			//std::cout << input_spike[i][j] << "\n";
		}
	}

	// read weight
	data_t weight[NEURON_NUM][INPUT_DIM];
	csv::Parser file = csv::Parser("tb_weight.csv");
	row_num = file.rowCount();
	col_num = file.columnCount();

	for (int i = 0; i != row_num; i++)
	{
		for (int j = 0; j != col_num; j++)
		{
			weight[i][j] = atof(file[i][j].c_str());
			//std::cout << file[i][j].c_str() << ",";
			//std::cout << weight[i][j] << "\n";
		}
	}

	ap_uint<NEURON_NUM> output_spike[WINDOW];

	// initialize memory as 0
	data_t k1[INPUT_DIM];
	data_t k2[INPUT_DIM];
	data_t voltage[NEURON_NUM];

	for (int i = 0; i != NEURON_NUM; i++)
	{
		voltage[i] = 0;
	}

	for (int i = 0; i != INPUT_DIM; i++)
	{
		k1[i] = 0;
		k2[i] = 0;
	}

	int output_spike_error_count = 0;
	int voltage_error_count = 0;

	for (int t = 0; t != WINDOW; t++)
	{
		std::cout << "step: " << t << "\n";
		ap_uint<INPUT_DIM> in_spike = 0;
		ap_uint<NEURON_NUM> out_spike = 0;

		// assign value to input spike
		for (int i = 0; i != INPUT_DIM; i++)
		{
			in_spike[i] = input_spike[i][t];
			std::cout << in_spike[i];
		}

		std::cout << "\n";
		out_spike = neuron (in_spike, voltage, weight, k1, k2);

		for(int i = 0; i != NEURON_NUM; i++)
			std::cout << voltage[i] << ",";

		std::cout << "\n";

		for(int i = 0; i != NEURON_NUM; i++)
			std::cout << ref_potential[i][t] << ",";

		//compare the difference of python model and hardware model
		for(int i = 0; i != NEURON_NUM; i++)
		{
			float diff = ref_potential[i][t]-voltage[i].to_float();
			if (abs(diff) > abs(ref_potential[i][t]*0.1))
				voltage_error_count++;
		}

		std::cout << "\n";

		//print reference output
		for (int i = 0; i != NEURON_NUM; i++)
			std::cout << ref_output_spike[i][t];

		std::cout << "\n";
		//print actual output
		for (int i = 0; i != NEURON_NUM; i++)
			std::cout << out_spike[i];

		//compare reference output spike and hardware model output
		for (int i = 0; i != NEURON_NUM; i++)
		{
			if (out_spike[i] != ref_output_spike[i][t])
				output_spike_error_count++;
		}
		std::cout << "\n";
	}

	std::cout << "spike error count: " << output_spike_error_count << "\n";
	std::cout << "voltage error count: " << voltage_error_count << "\n";

	return 0;
}
