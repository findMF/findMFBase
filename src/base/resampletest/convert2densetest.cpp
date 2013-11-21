// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/resample/convert2dense.h"

#include "base/stats/uniform.h"
#include "base/base/base.h"
#include "base/base/interpolate.h"
#include "base/base/cumsum.h"


BOOST_AUTO_TEST_SUITE(Convert2DenseTest)

BOOST_AUTO_TEST_CASE(testConvert)
{
  std::pair<double, double> tmp;
  tmp.first = 1000.;
  tmp.second = 1010;
  double ppm = 100;
  ralab::base::resample::Convert2Dense c2d;
  c2d.defBreak(tmp,ppm);
  std::vector<double> mids;
  c2d.getMids(mids);
  c2d.am_ = 0.1;

  double mz[] = {1001. , 1001.5 , 1001.8 , 1004. , 1005., 1008. , 1009. , 1009.3};
  size_t smz = sizeof(mz)/sizeof(double);
  std::vector<double> intensity( smz, 10.), gg;
  double all = std::accumulate(intensity.begin(),intensity.end(),0.);

  c2d.convert2dense(mz,mz+smz,intensity.begin(),gg);
  std::cout << gg.size() << std::endl;

  double bla = std::accumulate(gg.begin(),gg.end(),0.);
  BOOST_CHECK_CLOSE(bla, all - 10., 1e-10);
  // minus 10 because last intensity isn't added.
}

BOOST_AUTO_TEST_SUITE_END()

