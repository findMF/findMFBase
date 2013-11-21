// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>

#include "base/filter/scanfilter/backgroundsubtract.h"

#include <boost/timer.hpp>
#include "base/base/base.h"
#include "base/stats/uniform.h"
#include "base/stats/normal.h"
#include "base/base/cumsum.h"


// The fixture for testing class Foo.
class BackgroundsubtractHelp  {
protected:
  std::vector<double> data , dcumsum , res , res2;

  // You can remove any or all of the following functions if its body
  // is empty.
  BackgroundsubtractHelp() {
    SetUp();
    // You can do set-up work for each test here.
  }
  ~BackgroundsubtractHelp() {
    // You can do clean-up work that doesn't throw exceptions here.
  }

  void SetUp() {
    typedef double value_type;
    ralab::base::stats::rnorm( 100000 , data );
    ralab::base::cumsum(data.begin(),data.end() , dcumsum );
  }
};

BOOST_FIXTURE_TEST_SUITE(BackgroundsubtractTest, BackgroundsubtractHelp)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE(testseq) {
  res2.resize(dcumsum.size());
  boost::timer time;
  time.restart();
  ralab::base::filter::scanfilter::BackgroundSubtract<double> bs2(15);
  for(int i = 0; i < 100; ++i){
    bs2(dcumsum,res2);
  }
  std::cout << "openms : " << time.elapsed();
}

BOOST_AUTO_TEST_SUITE_END()
