#ifndef objects_h
#define objects_h

#include "config.h"

#include <ap_int.h>

struct object_t
{
};

struct calo_object_t : object_t
{
	typedef ap_uint<12> et_t;
	typedef ap_uint<7> eta_t;
	typedef ap_uint<6> phi_t;

	et_t et;
	eta_t eta;
	phi_t phi;
};

struct eg_object_t : calo_object_t
{
};

struct tau_object_t : calo_object_t
{
	typedef ap_uint<1> foobar_t;

	foobar_t foobar;
};

struct jet_object_t : calo_object_t
{
};

struct muon_object_t : object_t
{
	typedef ap_uint<14> pt_t;
	typedef ap_uint<8> eta_t;
	typedef ap_uint<7> phi_t;
	typedef ap_uint<1> corr_t;

	pt_t pt;
	eta_t eta;
	phi_t phi;
	corr_t corr;
};

#endif
