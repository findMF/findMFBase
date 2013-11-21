// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/ms/utilities/parabolafit.h"


BOOST_AUTO_TEST_SUITE(ParabolafitTest)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE( testparabola) {
  double epsilon = 1e-7;
  ralab::base::ms::utilities::Parabolafit<double> pft;
  bool t = pft(3,5,3);
  BOOST_CHECK_CLOSE(5.,pft.heigth_,epsilon);
  BOOST_CHECK_CLOSE(0.,pft.position_,epsilon);
  BOOST_CHECK_CLOSE(1.1775 ,pft.width_,epsilon);

  bool x = pft(3,10,3);
  BOOST_CHECK_CLOSE(10.,pft.heigth_,epsilon);
  BOOST_CHECK_CLOSE(0.,pft.position_,epsilon);
  BOOST_CHECK_CLOSE(0.62940022470375945,pft.width_,epsilon);
  bool r = pft(3,5,4);
  BOOST_CHECK_CLOSE(5.041666666666667,pft.heigth_,epsilon);
  BOOST_CHECK_CLOSE(0.166666666666667,pft.position_,epsilon);

  bool s = pft(3,10,9);
  BOOST_CHECK_CLOSE(10.5625,pft.heigth_,epsilon);
  BOOST_CHECK_CLOSE(0.375,pft.position_,epsilon);
  BOOST_CHECK_CLOSE(0.8326182348471598,pft.width_,epsilon);
}


BOOST_AUTO_TEST_SUITE_END()
