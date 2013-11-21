// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/base/diff.h"
#include "base/resample/masscomparefunctors.h"

BOOST_AUTO_TEST_SUITE(DiffTest)

BOOST_AUTO_TEST_CASE( testdiff){

  double epsilon = 0.00001;
  std::vector<double> tmp, res, ref; // res- result, ref-reference
  double numbers_[] = {   2,  3,  4,  5,  6,  7,  8,  9, 10, 11 };
  const int N = sizeof( numbers_ ) / sizeof( double );
  tmp.assign( numbers_ , numbers_ + N ) ;
  ref.assign( 10 , 1 );

  ralab::base::base::diff(tmp.begin() , tmp.end() , std::back_inserter(res) , 1 );
  bool bb = std::equal( res.begin(), res.end(), ref.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon) ) ;
  BOOST_CHECK( bb );

  res.clear();
  ref.assign(10,2);
  ralab::base::base::diff(tmp.begin() , tmp.end() , std::back_inserter(res) , 2 );
  bb = std::equal( res.begin(), res.end(), ref.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon) ) ;
  BOOST_CHECK( bb );

  std::vector<double> xxx(tmp);
  std::transform( xxx.begin() , xxx.end() , xxx.begin(), xxx.begin() , std::multiplies<double>() );

  std::vector<double>::iterator itmp =
      ralab::base::base::diff
      (
        xxx.begin(),
        xxx.end(),
        3,
        3
        );
  //long long xt = std::distance(xxx.begin(),itmp);
  //xt;
  BOOST_CHECK_CLOSE( *xxx.begin(),0.,  epsilon);
  BOOST_CHECK_EQUAL(std::distance(xxx.begin(),itmp) ,1);
}

BOOST_AUTO_TEST_SUITE_END()
