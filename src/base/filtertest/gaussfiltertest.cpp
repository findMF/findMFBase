// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>


#include "base/filter/gaussfilter.h"


#include <boost/timer.hpp>
#include "base/base/base.h"
#include "base/stats/uniform.h"
#include "base/stats/normal.h"
#include "base/base/cumsum.h"
#include "base/resample/masscomparefunctors.h"

// The fixture for testing class Foo.
struct GaussFilterHelp  {
protected:
  std::vector<double> data , dcumsum , res , res2;

  GaussFilterHelp() {
  }
  virtual ~GaussFilterHelp() {
  }
};

BOOST_FIXTURE_TEST_SUITE(GaussFilterTest,GaussFilterHelp)

BOOST_AUTO_TEST_CASE( testGaussian)
{
  std::vector<double> x;
  std::vector<double> y;
  double epsilon = 5e-5;
  //generate x values
  ralab::base::base::seq(-10.,10.,1.,x);
  std::transform(x.begin(),x.end(),std::back_inserter(y),ralab::base::filter::utilities::Gauss<double>(0.,1.));
  double result[21] ={ 7.694599e-23, 1.027977e-18, 5.052271e-15, 9.134720e-12, 6.075883e-09,
                       1.486720e-06, 1.338302e-04, 4.431848e-03, 5.399097e-02, 2.419707e-01,
                       3.989423e-01, 2.419707e-01, 5.399097e-02, 4.431848e-03, 1.338302e-04,
                       1.486720e-06, 6.075883e-09, 9.134720e-12, 5.052271e-15, 1.027977e-18,
                       7.694599e-23};

  BOOST_CHECK(std::equal(y.begin(),y.end(),result,ralab::base::resample::DaCompFunctor<double>(epsilon)));
  double sumfilter = std::accumulate(y.begin(),y.end(),0.);
  std::pair<double,double> tmp;
  ralab::base::stats::scale(y.begin(),y.end(),tmp,true);
  std::transform(y.begin(),y.end(),y.begin(),std::bind2nd(std::plus<double>(),( 1./x.size() ) ) );
  sumfilter = std::accumulate(y.begin(),y.end(),0.);
  BOOST_CHECK_CLOSE(sumfilter,1.,epsilon);
}

BOOST_AUTO_TEST_CASE(testGauss_1deriv)
{
  //code to compare goes here
  std::vector<double> x;
  std::vector<double> y;
  double epsilon = 5e-5;
  //generate x values
  ralab::base::base::seq(-10.,10.,1.,x);
  std::transform(x.begin(),x.end(),std::back_inserter(y),ralab::base::filter::utilities::Gauss_1deriv<double>(.0,1.));
  double firstderiv[21] = {
    7.694599e-22,  9.251796e-18,  4.041817e-14,  6.394304e-11,  3.645530e-08,  7.433598e-06,  5.353209e-04 , 1.329555e-02,  1.079819e-01,  2.419707e-01,
    0.000000e+00, -2.419707e-01, -1.079819e-01, -1.329555e-02, -5.353209e-04, -7.433598e-06, -3.645530e-08, -6.394304e-11 -4.041817e-14 -9.251796e-18,
    -7.694599e-22
  };

  // std::vector<double> fristderivV(firstderiv,firstderiv+21);
  BOOST_CHECK(std::equal(y.begin(),y.end(),firstderiv,ralab::base::resample::DaCompFunctor<double>(epsilon)));
  std::pair<double,double> tmp;
  ralab::base::stats::scale(y.begin(),y.end(),tmp,true);
  double sumfilter = std::accumulate(y.begin(),y.end(),0.0);
  BOOST_CHECK_SMALL(sumfilter,epsilon);
  double t = ralab::base::filter::getGaussian1DerFilter(x);
  sumfilter = std::accumulate(x.begin(),x.end(),0.0);
  t;
}

BOOST_AUTO_TEST_CASE(testGetGaussian)
{
  std::vector<double> xx;
  ralab::base::filter::getGaussianFilter(xx,30.);
  BOOST_CHECK(xx.size() == 121);
  BOOST_CHECK_CLOSE(std::accumulate(xx.begin(),xx.end(),0.),1.,1e-6);
  ralab::base::filter::getGaussianFilterQuantile(xx,30.);
}

BOOST_AUTO_TEST_SUITE_END()


