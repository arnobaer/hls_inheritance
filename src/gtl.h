#ifndef gtl_h
#define gtl_h

#include <ap_int.h>
#include <cstddef>

struct object_t
{
};

struct calo_object_t : object_t
{
	typedef ap_uint<12> et_t;
	et_t et;
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
	typedef ap_uint<1> corr_t;

	pt_t pt;
	corr_t corr;
};

struct req_t
{
};

struct calo_req_t : req_t
{
	calo_object_t::et_t et_threshold;

	ap_uint<1> match_et(const calo_object_t& object) const
	{
		return object.et >= et_threshold;
	}

	ap_uint<1> match(const calo_object_t& object) const
	{
		return match_et(object);
	}
};

struct eg_req_t : calo_req_t
{
};

struct tau_req_t : calo_req_t
{
	tau_object_t::foobar_t foobar;

	ap_uint<1> match_foobar(const tau_object_t& object) const
	{
		return object.foobar == foobar;
	}

	ap_uint<1> match(const tau_object_t& object) const
	{
		return calo_req_t::match(object) & match_foobar(object);
	}
};

struct jet_req_t : calo_req_t
{
};

struct muon_req_t : req_t
{
	muon_object_t::pt_t pt_threshold;
	muon_object_t::corr_t corr;

	ap_uint<1> match_et(const muon_object_t& object) const
	{
		return object.pt >= pt_threshold;
	}

	ap_uint<1> match_corr(const muon_object_t& object) const
	{
		return object.corr == corr;
	}

	ap_uint<1> match(const muon_object_t& object) const
	{
		return match_et(object) & match_corr(object);
	}
};

static const size_t N_EG = 12;
static const size_t N_TAU = 12;
static const size_t N_JET = 12;
static const size_t N_MUON = 8;

struct input_t
{
	typedef eg_object_t eg_objects_t[N_EG];
	eg_objects_t eg_objects;

	typedef eg_object_t tau_objects_t[N_TAU];
	tau_objects_t tau_objects;

	typedef jet_object_t jet_objects_t[N_JET];
	jet_objects_t jet_objects;

	typedef muon_object_t muon_objects_t[N_MUON];
	muon_objects_t muon_objects;
};

static const size_t N_ALGORITHM = 512;

struct output_t
{
	typedef ap_uint<1> algorithms_t[N_ALGORITHM];
	algorithms_t algorithms;
};

void gtl(const input_t& input, output_t& output);

#endif
