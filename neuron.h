#ifndef NEURON_H_
#define NEURON_H_

#include "ap_fixed.h"
#include "ap_int.h"
#include "hls_stream.h"



//#define USE_FLOATING
#define USE_FIXED

#ifdef USE_FLOATING
	typedef float	data_t;
	#define DECAY_TAU_M 0.9048374
	#define DECAY_TAU_S 0.67032
	#define NORM_FACTOR 2.1165
	#define SCALAING_FACTOR 1
	#define THRESHOLD 1
#else
	#ifdef USE_FIXED
		typedef ap_fixed<16,4> data_t;
		#define DECAY_TAU_M 0.9048374
		#define DECAY_TAU_S 0.67032
		#define NORM_FACTOR 1
		#define SCALAING_FACTOR 2.1165
		#define THRESHOLD 1
	#else
		typedef int data_t;
		/* decay factor
		 * use <4,12> fixed point, to convert float n to fixed point
		 * multiply n with 2^12, and keep integer part
		 */
		#define DECAY_TAU_M 3706
		#define DECAY_TAU_S 2745
		// v_norm = eta^(eta/(eta-1))/(eta-1)
		// eta = tau_m - tau_s
		#define NORM_FACTOR 8669
		#define SCALAING_FACTOR 4096
		#define THRESHOLD 4096
	#endif
#endif

#define NEURON_NUM 10
#define INPUT_DIM 110

#define TAU_M 10
#define TAU_S 2.5

#define WINDOW 450


ap_uint<NEURON_NUM> neuron (ap_uint<64> input_spike_127_64,
		ap_uint<64> input_spike_63_0,
		hls::stream<ap_fixed<32,20> > &voltage,
		data_t weight[NEURON_NUM][INPUT_DIM],
		hls::stream<ap_fixed<32,20> > &psp,
		int reset_neuron,
		int test_var,
		int enable_test,
		hls::stream<ap_fixed<32,20> > &test_out);

#endif
