#include "base/stats/scale.h"
#include "base/base/base.h"
#include "base/resample/masscomparefunctors.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(ScaleTest)

BOOST_AUTO_TEST_CASE(testRootMeanSquare)
{
  double epsilon(5e-5);
  std::vector<double> x;
  ralab::base::base::seq(10,x);
  double res = ralab::base::stats::rootMeanSquare(x.begin(),x.end());
  BOOST_CHECK_CLOSE(6.540472, res, epsilon );
}

BOOST_AUTO_TEST_CASE(testScale)
{
  double epsilon(5e-4);
  std::vector<double> x;
  ralab::base::base::seq(10,x);
  std::vector<double> tmp(x);
  std::pair<double,double> scaled;

  ralab::base::stats::scale(x.begin(), x.end(), scaled, false, false);
  bool isequal = std::equal(x.begin(), x.end(), tmp.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon));
  BOOST_CHECK(isequal);

  // test center=false , scale = true.
  //  c(scale(seq(1,10),F,T)) #(in R)
  double scaleFT[10] ={  0.1528942, 0.3057883, 0.4586825, 0.6115766, 0.7644708, 0.9173649, 1.0702591, 1.2231533, 1.3760474, 1.5289416};
  ralab::base::stats::scale(x.begin(),x.end(),scaled, false,true);
  isequal = std::equal(x.begin(), x.end(), scaleFT,ralab::base::resample::DaCompFunctor<double>(epsilon) );
  BOOST_CHECK(isequal);
  BOOST_CHECK( scaled.first != scaled.first); // this is only true if first is NAN - std::numeric_limits<double>::quiet_NaN() );
  BOOST_CHECK_CLOSE( scaled.second, 6.540472, epsilon);
  // test center=true , scale = false.
  //  c(scale(seq(1,10),T,F)) #(in R)
  x.assign(tmp.begin(),tmp.end());
  double scaleTF[10] ={-4.5, -3.5, -2.5, -1.5, -0.5,  0.5,  1.5,  2.5,  3.5,  4.5};
  ralab::base::stats::scale(x.begin(),x.end(),scaled, true,false);
  isequal = std::equal(x.begin(), x.end(), scaleTF,ralab::base::resample::DaCompFunctor<double>(epsilon) );
  BOOST_CHECK(isequal);
  BOOST_CHECK_CLOSE(scaled.first, 5.5, epsilon);
  BOOST_CHECK(scaled.second != scaled.second);
  // test center=true , scale = false.
  //  c(scale(seq(1,10),T,T)) #(in R)
  x.assign(tmp.begin(),tmp.end());
  double scaleTT[10] ={-1.4863011, -1.1560120, -0.8257228, -0.4954337, -0.1651446,  0.1651446,  0.4954337,  0.8257228,  1.1560120,  1.4863011};
  ralab::base::stats::scale(x.begin(),x.end(),scaled, true,true);
  isequal = std::equal(x.begin(), x.end(), scaleTT,ralab::base::resample::DaCompFunctor<double>(epsilon) );
  BOOST_CHECK(isequal);
  BOOST_CHECK_CLOSE(scaled.first, 5.5, epsilon);
  BOOST_CHECK_CLOSE(scaled.second, 3.027650, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
