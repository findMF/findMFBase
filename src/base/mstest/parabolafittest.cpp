// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#include "base/ms/utilities/parabolafit.h"
#include <gtest/gtest.h>


namespace{
  // The fixture for testing class Foo.
  class ParabolafitTest : public ::testing::Test {
  public:
    ParabolafitTest() {
      // You can do set-up work for each test here.
    }

    // Objects declared here can be used by all tests in the test case for Foo.
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(ParabolafitTest, testparabola) {
    double epsilon = 1e-7;
    ralab::base::ms::utilities::Parabolafit<double> pft;
    bool t = pft(3,5,3);
    ASSERT_DOUBLE_EQ(5.,pft.heigth_);
    ASSERT_DOUBLE_EQ(0.,pft.position_);
    ASSERT_DOUBLE_EQ(1.1775 ,pft.width_);

    bool x = pft(3,10,3);
    ASSERT_DOUBLE_EQ(10.,pft.heigth_);
    ASSERT_DOUBLE_EQ(0.,pft.position_);
    ASSERT_NEAR(0.62940022470375945,pft.width_,epsilon);
    bool r = pft(3,5,4);
    ASSERT_NEAR(5.041666666666667,pft.heigth_,epsilon);
    ASSERT_NEAR(0.166666666666667,pft.position_,epsilon);

    bool s = pft(3,10,9);
    ASSERT_NEAR(10.5625,pft.heigth_,epsilon);
    ASSERT_NEAR(0.375,pft.position_,epsilon);
    ASSERT_NEAR(0.8326182348471598,pft.width_,epsilon);
  }
}//end namespace


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

