// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/base/base.h"

BOOST_AUTO_TEST_SUITE(FilterUtilsTest)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE( testseq){
  std::vector<double> res;
  ralab::base::base::seq(1.,10.,0.5,res);
  ralab::base::base::seq(10.,2.,res);
  ralab::base::base::seq(2.,10.,res);
  ralab::base::base::seq(10., 2. , -0.5 , res);

  std::vector<int32_t> res2;
  ralab::base::base::seq(10,2,res2);
  ralab::base::base::seq(10,res);
  ralab::base::base::seq(res2,res);

  std::vector<unsigned int> resunsigned;
  ralab::base::base::seq(1u,10u,1u,resunsigned);
  ralab::base::base::seq(1u,10u,resunsigned);

  std::vector<double> resdouble;
  ralab::base::base::seq_length(100. , 1300.,18467,resdouble);
  BOOST_CHECK(resdouble.size() == 18467);
  ralab::base::base::seq_length(100. , 1300.,19467,resdouble);
  BOOST_CHECK(resdouble.size() == 19467);

  ralab::base::base::seq_length(0.,1000.,1000,resdouble);
  BOOST_CHECK(resdouble.size() == 1000);
}

// Tests that Foo does Xyz.
BOOST_AUTO_TEST_CASE( mean) {
  std::vector<double> x;
  x.push_back(1.0);
  x.push_back(1.0);
  x.push_back(1.0);
  x.push_back(1.);
  x.push_back(2.);
  x.push_back(3.);
  x.push_back(5.);
  x.push_back(5.);
  x.push_back(6.);
  x.push_back(7.);
  x.push_back(8.);
  double res = ralab::base::base::mean(x);
  BOOST_CHECK_CLOSE_FRACTION ( 3.636364, res, 1e-4);
  res = ralab::base::base::mean(x, 0.3);
  BOOST_CHECK_CLOSE_FRACTION ( 3.2, res, 1e-4);
  res = ralab::base::base::mean(x, 0.4);
  BOOST_CHECK_CLOSE_FRACTION ( 3.33333, res, 1e-4);
  res = ralab::base::base::mean(x, 0.5);
  BOOST_CHECK_CLOSE_FRACTION ( 3., res, 1e-4);
  res = ralab::base::base::mean(x.begin(),x.end());
  BOOST_CHECK_CLOSE_FRACTION ( 3.636364, res, 1e-4);

}

BOOST_AUTO_TEST_CASE( geometricmean){
  std::vector<double> x;
  x.push_back(1.0);
  x.push_back(2.0);
  x.push_back(3.0);

  double res = ralab::base::base::geometricMean(x.begin(), x.end());
  BOOST_CHECK_CLOSE( 1.817121, res, 1e-4 );
}


BOOST_AUTO_TEST_SUITE_END()
