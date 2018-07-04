#ifndef gtl_h
#define gtl_h

#include "config.h"
#include "objects.h"

#include <ap_int.h>

struct input_t
{
	typedef eg_object_t eg_object_array_t[config::EG_COUNT];
	typedef tau_object_t tau_object_array_t[config::TAU_COUNT];
	typedef jet_object_t jet_object_array_t[config::JET_COUNT];
	typedef muon_object_t muon_object_array_t[config::MUON_COUNT];

	eg_object_array_t eg_objects;
	tau_object_array_t tau_objects;
	jet_object_array_t jet_objects;
	muon_object_array_t muon_objects;
};

struct output_t
{
	typedef ap_uint<1> algorithm_array_t[config::ALGO_COUNT];
	typedef ap_uint<1> final_t;

	algorithm_array_t algorithms;
	final_t final;

	/** Reset algorithms and final OR. */
	void reset();

	/** Calculate final OR from algorithms. */
	void update_final();
};

void gtl(const input_t& input, output_t& output);

#endif
