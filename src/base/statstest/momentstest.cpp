// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Fixtures
#include <boost/test/unit_test.hpp>

#include "base/stats/quantiles.h"

#include "base/stats/momentsW.h"
#include "base/stats/moments.h"

#include "base/base/base.h"
#include "base/resample/masscomparefunctors.h"
#include "base/stats/uniform.h"

// The fixture for testing class Foo.
class MomentsTH  {
protected:
  std::vector<double> m_data;
  std::vector<double> m_weight;

  // You can remove any or all of the following functions if its body
  // is empty.
  MomentsTH() {
    m_data.push_back(2);
    m_data.push_back(4);
    m_data.push_back(8);
    m_data.push_back(10);
    m_data.push_back(99);
    m_data.push_back(1);

    m_weight.push_back(2);
    m_weight.push_back(3);
    m_weight.push_back(4);
    m_weight.push_back(5);
    m_weight.push_back(6);
    m_weight.push_back(1);
    // You can do set-up work for each test here.
  }
};

BOOST_FIXTURE_TEST_SUITE(MomentsTest, MomentsTH)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE(computeStats) {
  double epsilon = 0.01;
  double sum, mean, var, dev, skew, kurt;
  ralab::stats::computeStats(m_data.begin( ), m_data.end( ),
                             sum, mean, var, dev, skew, kurt);
  BOOST_CHECK_CLOSE(sum  ,124.0, epsilon);
  BOOST_CHECK_CLOSE(mean ,20.6667, epsilon);
  BOOST_CHECK_CLOSE(var  ,1237.22222, epsilon);
  BOOST_CHECK_CLOSE(dev  ,35.1742, epsilon );
  BOOST_CHECK_CLOSE(skew ,1.75664, epsilon) ;
  BOOST_CHECK_CLOSE(kurt ,1.14171, epsilon );
}

// Tests that Foo does Xyz.
BOOST_AUTO_TEST_CASE( moments) {
  double res, epsilon = 0.01;
  res = ralab::stats::var( m_data.begin( ), m_data.end( ));
  BOOST_CHECK_CLOSE(res, 1237.222222, epsilon);
  res = ralab::stats::sd( m_data.begin( ) , m_data.end( ));
  BOOST_CHECK_CLOSE(res, 35.1742, epsilon);
  res = ralab::stats::skew( m_data.begin( ), m_data.end( ));
  BOOST_CHECK_CLOSE(res, 1.75664, epsilon);
  res = ralab::stats::kurtosis( m_data.begin( ) , m_data.end( ));
  BOOST_CHECK_CLOSE(res, 1.14171, epsilon);
  //test the unbiased versions.
  res = ralab::stats::varUnbiased( m_data.begin( ), m_data.end( ));
  BOOST_CHECK_CLOSE(res, 1484.66666, epsilon);
  res = ralab::stats::sdUnbiased( m_data.begin( ), m_data.end( ));
  BOOST_CHECK_CLOSE(res, 38.53137, epsilon);
}

BOOST_AUTO_TEST_SUITE_END()
