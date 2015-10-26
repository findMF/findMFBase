// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/stats/quantiles.h"

#include "base/stats/momentsW.h"
#include "base/stats/moments.h"

#include "base/base/base.h"
#include "base/resample/masscomparefunctors.h"
#include "base/stats/uniform.h"


BOOST_AUTO_TEST_SUITE(QuantilesTest)

BOOST_AUTO_TEST_CASE(testQuantileSval){
  double epsilon(1e-10);
  std::vector<double> values, suffle ;
  ralab::base::base::seq(1.,20.,0.3,values);
  suffle.assign(values.begin(),values.end());
  std::random_shuffle(suffle.begin(),suffle.end());

  double q1 = ralab::stats::quantile(values.begin(),values.end(),0.5);
  double q2 = ralab::stats::quantile(suffle.begin(),suffle.end(),0.5);

  BOOST_CHECK_CLOSE( q1 , q2, epsilon);
  q1 = ralab::stats::quantile(values.begin(),values.end(),0.6);
  q2 = ralab::stats::quantile(suffle.begin(),suffle.end(),0.6);
  BOOST_CHECK_CLOSE( q1 , q2, epsilon);

  q1 = ralab::stats::quantile(values.begin(),values.end(),0.3);
  q2 = ralab::stats::quantile(suffle.begin(),suffle.end(),0.3);
  BOOST_CHECK_CLOSE( q1 , q2, epsilon);

  q1 = ralab::stats::quantile(values.begin(),values.end(),1.);
  q2 = ralab::stats::quantile(suffle.begin(),suffle.end(),1.);
  BOOST_CHECK_CLOSE( q1 , q2, epsilon);

  q1 = ralab::stats::quantile(values.begin(),values.end(),0.);
  q2 = ralab::stats::quantile(suffle.begin(),suffle.end(),0.);
  BOOST_CHECK_CLOSE( q1 , q2, epsilon);

}


BOOST_AUTO_TEST_CASE(quantileStats3){
	double epsilon(0.01);
	std::vector<double> values;
	ralab::base::stats::runif(10000, values, 0., 1.);
	//Test Quantiles
	std::vector<double> probs;
	probs.push_back(0.0);
	probs.push_back(0.15);
	probs.push_back(0.25);
	probs.push_back(0.35);
	probs.push_back(0.5);
	probs.push_back(0.76);
	probs.push_back(0.9);
	probs.push_back(1);
	std::vector<double> quantiles;
	//ralab::stats::fivenum(values, quantiles);

	ralab::stats::quantileFromVec(values, probs, quantiles);
	//BOOST_CHECK(std::equal(probs.begin(), probs.end(), quantiles.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon)));
}

BOOST_AUTO_TEST_CASE(testQuantileStats2){
  double epsilon(1e-10);
  std::vector<double> values ;
  ralab::base::base::seq(1.,20.,values);

  //Test Median
  double median = ralab::stats::median(values.begin(),values.end());
  BOOST_CHECK_CLOSE( median , 10.5, epsilon);

  //Test Five numbers
  std::vector<double> quantiles;
  ralab::stats::fivenum(values,quantiles);

  std::vector<double> probs;
  probs.clear();
  probs.push_back(1.0);
  probs.push_back(5.5);
  probs.push_back(10.5);
  probs.push_back(15.5);
  probs.push_back(20);
  BOOST_CHECK( std::equal(probs.begin(), probs.end(), quantiles.begin(), ralab::base::resample::DaCompFunctor<double>(0.01) ) );

  //Test Quantiles
  probs.clear();
  probs.push_back(0.0);
  probs.push_back(0.15);
  probs.push_back(0.25);
  probs.push_back(0.35);
  probs.push_back(0.5);
  probs.push_back(0.76);
  probs.push_back(0.9);
  probs.push_back(1);
  
  std::vector<double> ref;
  ref.push_back(1.00); // 1.00  3.85  5.75  7.65 10.50 15.44 18.10 20.00
  ref.push_back(3.5);
  ref.push_back(5.5);
  ref.push_back(7.5);
  ref.push_back(10.50);
  ref.push_back(15.5);
  ref.push_back(18.5);
  ref.push_back(20.00);

  ralab::stats::quantileFromVec(values, probs, quantiles);

  BOOST_CHECK(std::equal(ref.begin(), ref.end(), quantiles.begin(), ralab::base::resample::DaCompFunctor<double>(0.01)) );
  //Test Range
  std::pair<double, double> range;
  ralab::base::base::Range(values, range );
  BOOST_CHECK_SMALL(range.first - 1 , 1e-10 );
  BOOST_CHECK_SMALL(range.second - 20 , 1e-10 );

}

BOOST_AUTO_TEST_CASE( quantileStats){
  double epsilon(0.01) ;
  std::vector<double> values ;
  ralab::base::stats::runif(100000,values, 0.,1.) ;
  //Test Median
  double median = ralab::stats::median(values.begin(),values.end());
  BOOST_CHECK_SMALL( median - 0.5, epsilon );
  //Test Quantiles
  std::vector<double> probs;
  probs.push_back(0.0);
  probs.push_back(0.15);
  probs.push_back(0.25);
  probs.push_back(0.35);
  probs.push_back(0.5);
  probs.push_back(0.76);
  probs.push_back(0.9);
  probs.push_back(1);
  std::vector<double> quantiles;
  ralab::stats::quantileFromVec(values, probs, quantiles);
  BOOST_CHECK(std::equal(probs.begin(), probs.end(), quantiles.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon) ));

  //Test Five numbers
  ralab::stats::fivenum(values,quantiles);
  probs.clear();
  probs.push_back(0);
  probs.push_back(0.25);
  probs.push_back(0.5);
  probs.push_back(0.75);
  probs.push_back(1);
  BOOST_CHECK( std::equal(probs.begin(), probs.end(), quantiles.begin(), ralab::base::resample::DaCompFunctor<double>(epsilon) ) );
  //Test Range
  std::pair<double, double> range;
  ralab::base::base::Range(values, range );
  BOOST_CHECK_SMALL(range.first  , 0.05 );
  BOOST_CHECK_SMALL(range.second - 1 , 0.05 );
}

BOOST_AUTO_TEST_SUITE_END()
