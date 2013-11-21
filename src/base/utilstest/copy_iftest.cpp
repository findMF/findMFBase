// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/utils/copyif.h"

#include "base/resample/masscomparefunctors.h"
#include <boost/bind.hpp>


BOOST_AUTO_TEST_SUITE(Copy_iftest)



BOOST_AUTO_TEST_CASE(copyif)
{
  double x[] = {1,3,5,1,3,5,1,3,5,1,3,5};
  double y[] = {2,4,6,2,4,6,2,4,6,2,4,6};

  std::vector<double> res;

  ralab::base::utils::copy_if(x,x+sizeof(x)/sizeof(double),std::back_inserter(res),boost::bind(std::less<double>(), _1, 2 ) );
  BOOST_CHECK_EQUAL(res.size(),4);
  res.clear();
  ralab::base::utils::copy_if_not(x,x+sizeof(x)/sizeof(double),std::back_inserter(res),boost::bind(std::less<double>(), _1, 2 ) );
  BOOST_CHECK_EQUAL(res.size(),8);
  res.clear();
}

//tmp
BOOST_AUTO_TEST_CASE(copyif2)
{
  double x[] = {1,3,5,1,3,5,1,3,5,1,3,5};
  double y[] = {2,4,6,2,4,6,2,4,6,2,4,6};

  std::vector<double> res;
  ralab::base::utils::copy_if(x,x+sizeof(x)/sizeof(double),y,
                              std::back_inserter(res),
                              boost::bind(std::less<double>(), _1, 2 ) );
  BOOST_CHECK_EQUAL(res.size(),4);
  BOOST_CHECK_EQUAL(res[0],2);
  res.clear();
  ralab::base::utils::copy_if_not(x,x+sizeof(x)/sizeof(double),y,
                                  std::back_inserter(res),boost::bind(std::less<double>(), _1, 2 ) );
  BOOST_CHECK_EQUAL(res.size(),8);
  BOOST_CHECK_EQUAL(res[0],4);
  res.clear();
}


BOOST_AUTO_TEST_SUITE_END()
