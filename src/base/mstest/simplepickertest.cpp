// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#include "gtest/gtest.h"
#include "base/ms/simplepicker.h"

namespace {

  // The fixture for testing class Foo.
  class SimplePickerTest : public ::testing::Test {
  protected:
    // You can remove any or all of the following functions if its body
    // is empty.
    SimplePickerTest() {
      // You can do set-up work for each test here.
    }
    virtual ~SimplePickerTest() {
      // You can do clean-up work that doesn't throw exceptions here.
    }
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
      // Code here will be called immediately after the constructor (right
      // before each test).
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right
      // before the destructor).
    }

    // Objects declared here can be used by all tests in the test case for Foo.
  };

  // Tests that the Foo::Bar() method does Abc.
  TEST_F(SimplePickerTest, testpicker) {
    ralab::base::ms::SimplePicker<double> sp;

    std::vector<double> zerocross(10,0.);
    //lag2 at 5
    //lag2 at
    double data2[] = {1.,2.,3.,4.,5.,6.,5.,3.,2.,1.,0.};
    size_t x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),2);
    ASSERT_NEAR(zerocross[0],5.,1e-10);
    x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),4);
    ASSERT_NEAR(zerocross[0],4.6666,1e-4);
    x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),6);
    ASSERT_NEAR(zerocross[0],4.5,1e-4);
    std::cout << x << std::endl;


    double data3[] = {0.,1.,2.,3.,5.,6.,5.,4.,3.,2.,1.};
    x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),2);
    x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),4);
    ASSERT_NEAR(zerocross[0],5.3333,1e-4);
    x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),6);
    ASSERT_NEAR(zerocross[0],5.5,1e-4);
    std::cout << x << std::endl;


    double data[] = {1.,2.,3.,4.,5.,6.,5.,4.,3.,2.,1.};

    // for lag 2
    // zero cross at 5

    x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),2);
    ASSERT_NEAR(zerocross[0],5.,1e-10);
    x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),4);
    ASSERT_NEAR(zerocross[0],5.,1e-10);
    x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),6);
    ASSERT_NEAR(zerocross[0],5.,1e-10);

    std::cout << x << std::endl;
  }
}//end namespace


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
