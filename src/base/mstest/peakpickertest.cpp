// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>

#include "base/ms/peakpickerqtof.h"

#include "base/stats/normal.h"
#include "base/base/cumsum.h"
#include "base/base/base.h"
#include "base/ms/generatesamplespec.h"


// The fixture for testing class Foo.
class PeakPickerHelp {
protected:
  std::vector<double> data , dcumsum , mass, spec;
  // You can remove any or all of the following functions if its body
  // is empty.
  PeakPickerHelp() {
    // You can do set-up work for each test here.
    SetUp();
  }
  virtual void SetUp() {

    typedef double value_type;
    std::size_t specsize=10000;

    ralab::base::stats::rnorm( specsize , data );
    ralab::base::cumsum(data.begin(),data.end() , dcumsum );
    ralab::base::base::seq_length(300.,1000.,dcumsum.size(),mass);
    // Code here will be called immediately after the constructor (right
    // before each test).


    ralab::base::ms::generateSampleSpec(specsize,3.,200,spec);
  }
};


BOOST_FIXTURE_TEST_SUITE(GaussFilterTest,PeakPickerHelp)


// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE( testpicker) {

  double resolution = 10000;
  std::pair<double, double> massrange = std::make_pair(mass.front(),mass.back());
  ralab::base::ms::PeakPicker<double, ralab::base::ms::SimplePeakArea> pp(resolution, massrange);
  pp(mass.begin(),mass.end(),spec.begin());
  std::cout << "nrPeaks" << pp.getPeakArea().size() << std::endl;
}

BOOST_AUTO_TEST_SUITE_END()
