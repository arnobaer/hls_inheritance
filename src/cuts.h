#ifndef cuts_h
#define cuts_h

#include "objects.h"

struct cut_t
{
	cut_t() {}

	ap_uint<1> match(const object_t& object) const
	{
		return true;
	}
};

struct calo_cut_t : cut_t
{
	calo_object_t::et_t et_threshold;

	calo_cut_t(calo_object_t::et_t et_threshold)
	: cut_t(),
	  et_threshold(et_threshold)
	{}

	ap_uint<1> match_et(const calo_object_t& object) const
	{
		return object.et >= et_threshold;
	}

	ap_uint<1> match(const calo_object_t& object) const
	{
		return cut_t::match(object)
		     & match_et(object);
	}
};

struct eg_cut_t : calo_cut_t
{
	eg_cut_t(calo_object_t::et_t et_threshold)
	: calo_cut_t(et_threshold)
	{}
};

struct tau_cut_t : calo_cut_t
{
	tau_object_t::foobar_t foobar;

	tau_cut_t(calo_object_t::et_t et_threshold,
			  tau_object_t::foobar_t foobar)
	: calo_cut_t(et_threshold),
	  foobar(foobar)
	{}

	ap_uint<1> match_foobar(const tau_object_t& object) const
	{
		return object.foobar == foobar;
	}

	ap_uint<1> match(const tau_object_t& object) const
	{
		return calo_cut_t::match(object)
		     & match_foobar(object);
	}
};

struct jet_cut_t : calo_cut_t
{
	jet_cut_t(calo_object_t::et_t et_threshold)
	: calo_cut_t(et_threshold)
	{}
};

struct muon_cut_t : cut_t
{
	muon_object_t::pt_t pt_threshold;
	muon_object_t::corr_t corr;

	muon_cut_t(muon_object_t::pt_t pt_threshold,
			   muon_object_t::corr_t corr)
	: cut_t(),
	  pt_threshold(pt_threshold),
	  corr(corr)
	{}

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
		return cut_t::match(object)
			 & match_et(object)
			 & match_corr(object);
	}
};

#endif
