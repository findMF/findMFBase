// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/filter/filter.h"
#include <boost/timer.hpp>
#include "base/base/base.h"
#include "base/stats/uniform.h"
#include "base/stats/normal.h"
#include "base/base/cumsum.h"
#include "base/resample/masscomparefunctors.h"

BOOST_AUTO_TEST_SUITE(FilterUtilsTest)

/*! \brief test filter function */
BOOST_AUTO_TEST_CASE( filterTest)
{
  double epsilon = 0.000001;
  epsilon;
  std::vector<double> data;
  ralab::base::base::seq(-500., 500., .1, data);
  std::vector<double> y;
  std::transform(data.begin(), data.end(), std::back_inserter(y), static_cast<double(*)(double)>(sin) );

  std::vector<double> filt3(21,1./21.); // mean filter
  double sumfilt =   std::accumulate(filt3.begin(), filt3.end(), 0.0 );
  BOOST_CHECK_CLOSE(sumfilt, 1.0,epsilon );

  std::vector<double> result;
  ralab::base::filter::filter(
        y,
        filt3,
        result
        );

  ralab::base::filter::filter(
        y,
        filt3,
        result,
        true
        );

  result.resize(y.size());

  ralab::base::filter::filter_sequence(
        y.begin(),
        y.end(),
        filt3.begin(),
        filt3.size(),
        result.begin(),
        true
        );

}

/*! \brief Evaluate data extension */
BOOST_AUTO_TEST_CASE( testExtendData)
{
  std::vector<int> tmp, res;
  ralab::base::base::seq(5,tmp);
  std::vector<int>::iterator it = ralab::base::filter::utilities::prepareData(tmp.begin(),tmp.end(), 5, res);
  res.resize(std::distance(res.begin(),it));
  double ref[] = { 4, 5, 1, 2, 3, 4 ,5, 1, 2};

  /*std::copy(res.begin(),res.end(),std::ostream_iterator<int>(std::cout," "));
                              std::cout << std::endl;
                              */
  bool iseq = std::equal(res.begin(),res.end(),ref);
  BOOST_CHECK(iseq);

  it = ralab::base::filter::utilities::prepareData(tmp.begin(),tmp.end(), 5, res, true);
  res.resize(std::distance(res.begin(),it));

  double ref2[] = {2, 1, 1, 2, 3, 4, 5, 5, 4};
  iseq = std::equal(res.begin(),res.end(),ref2);
  BOOST_CHECK(iseq);
}

BOOST_AUTO_TEST_SUITE_END()






