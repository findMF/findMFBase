// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/base/cumsum.h"

#include <vector>
#include <algorithm>

#include "base/base/base.h"


BOOST_AUTO_TEST_SUITE(CumSumTest)

BOOST_AUTO_TEST_CASE(testCumSum)
{
  unsigned int resC[]={ 1 , 3 , 6 ,10 ,15 ,21 ,28 ,36 ,45 ,55};

  std::vector<unsigned int> res;
  ralab::base::base::seq(static_cast<unsigned int>(1),static_cast<unsigned int>(10),res);
  std::vector<unsigned int> res2;
  ralab::base::cumsum(res.begin(),res.end() , res2);
  std::equal(res2.begin(),res2.end(),resC);
  //test the in place version.
  ralab::base::cumsum(res.begin(),res.end());
  BOOST_CHECK(std::equal(res.begin(),res.end(),resC));
}

BOOST_AUTO_TEST_CASE(testCumProd)
{
  unsigned int resC[]={1,2,6,24,120,720,5040,40320,362880,3628800};

  std::vector<unsigned int> res;
  ralab::base::base::seq(static_cast<unsigned int>(1),static_cast<unsigned int>(10),res);
  std::vector<unsigned int> res2;
  ralab::base::cumprod(res,res2);
  BOOST_CHECK(std::equal(res2.begin(),res2.end(),resC));
}

BOOST_AUTO_TEST_CASE(testCumMin)
{
  unsigned int data[] ={ 3 ,2 ,1 ,2 ,1 ,0 ,4 ,3 ,2};
  unsigned int resC[]={3 , 2 , 1 , 1 , 1 , 0 , 0 , 0 , 0};

  std::vector<unsigned int> res;
  res.assign(data, data + 9);
  std::vector<unsigned int> res2;
  ralab::base::cummin(res,res2);
  BOOST_CHECK(std::equal(res2.begin(),res2.end(),resC));
}

BOOST_AUTO_TEST_CASE(testCumMax)
{
  unsigned int data[] ={ 3 ,2 ,1 ,2 ,1 ,0 ,4 ,3 ,2};
  unsigned int resC[]={ 3, 3, 3, 3, 3, 3, 4, 4, 4};
  std::vector<unsigned int> res;
  res.assign(data, data + 9);
  std::vector<unsigned int> res2;
  ralab::base::cummax(res,res2);
  BOOST_CHECK(std::equal(res2.begin(),res2.end(),resC));
}

BOOST_AUTO_TEST_SUITE_END()



