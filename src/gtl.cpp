#include "gtl.h"
#include "cuts.h"

void output_t::reset()
{
	#pragma HLS ARRAY_PARTITION variable=algorithms complete dim=1
	#pragma HLS INTERFACE ap_ctrl_none port=return

	for (size_t i = 0; i < config::ALGO_COUNT; ++i)
	{
		#pragma HLS UNROLL
		algorithms[i] = false;
	}

	final = false;
}

void output_t::update_final()
{
	#pragma HLS ARRAY_PARTITION variable=algorithms complete dim=1
	#pragma HLS INTERFACE ap_ctrl_none port=return

	final = false;

	for (size_t i = 0; i < config::ALGO_COUNT; ++i)
	{
		#pragma HLS UNROLL
		final |= algorithms[i];
	}
}

void gtl(const input_t& input, output_t& output)
{
	#pragma HLS ARRAY_PARTITION variable=input.eg_objects complete dim=1
	#pragma HLS ARRAY_PARTITION variable=input.tau_objects complete dim=1
	#pragma HLS ARRAY_PARTITION variable=input.jet_objects complete dim=1
	#pragma HLS ARRAY_PARTITION variable=input.muon_objects complete dim=1

	#pragma HLS ARRAY_PARTITION variable=output.algorithms complete dim=1

	#pragma HLS INTERFACE ap_none port=input
	#pragma HLS INTERFACE ap_none port=output
	#pragma HLS INTERFACE ap_ctrl_none port=return

	// Define cuts

	const calo_cut_t calo_cut_01 = {0};

	const eg_cut_t eg_cut_01 = {2};
	const tau_cut_t tau_cut_01 = {4, false};
	const jet_cut_t jet_cut_01 = {8};

	const muon_cut_t muon_cut_01 = {42, false};

	// Skipping condition implementation...

	// Clear output
	output.reset();

	// Calculate triggers

	output.algorithms[0] = muon_cut_01.match(input.muon_objects[0])
						 & muon_cut_01.match(input.muon_objects[1])
						 & muon_cut_01.match(input.muon_objects[2])
						 & muon_cut_01.match(input.muon_objects[3]);

	output.algorithms[1] = jet_cut_01.match(input.jet_objects[0])
					     & tau_cut_01.match(input.tau_objects[1]);

	output.algorithms[2] = calo_cut_01.match(input.eg_objects[0])
						 & calo_cut_01.match(input.tau_objects[1]);

	// Calculate final OR
	output.update_final();

}
