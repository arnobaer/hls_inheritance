#include "gtl.h"

void gtl(const input_t& input, output_t& output)
{
	muon_req_t muon_req_01;
	muon_req_01.pt_threshold = 42;
	muon_req_01.corr = false;

	jet_req_t jet_req_01;
	jet_req_01.et_threshold = 2;

	// Applies on any calorimeter type object
	calo_req_t calo_req_01;
	calo_req_01.et_threshold = 0;

	// Skipping condition implementation...

	output.algorithms[0] = muon_req_01.match(input.muon_objects[0])
						 & muon_req_01.match(input.muon_objects[1]);

	output.algorithms[1] = jet_req_01.match(input.jet_objects[0])
					     & jet_req_01.match(input.jet_objects[1]);

	// Power of inheritance...
	output.algorithms[2] = calo_req_01.match(input.eg_objects[0])
						 & calo_req_01.match(input.tau_objects[1]);

}
