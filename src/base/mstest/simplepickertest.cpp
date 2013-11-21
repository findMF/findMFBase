// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/ms/simplepicker.h"

BOOST_AUTO_TEST_SUITE(SimplePickerTest)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE(testpicker){
  ralab::base::ms::SimplePicker<double> sp;
  double epsilon = 0.01;
  std::vector<double> zerocross(10,0.);
  //lag2 at 5
  //lag2 at
  double data2[] = {1.,2.,3.,4.,5.,6.,5.,3.,2.,1.,0.};
  size_t x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),2);
  BOOST_CHECK_CLOSE(zerocross[0],5.,epsilon);
  x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),4);
  BOOST_CHECK_CLOSE(zerocross[0],4.6666,epsilon);
  x = sp(data2,data2+sizeof(data2)/sizeof(double),zerocross.begin(),zerocross.size(),6);
  BOOST_CHECK_CLOSE(zerocross[0],4.5,epsilon);


  double data3[] = {0.,1.,2.,3.,5.,6.,5.,4.,3.,2.,1.};
  x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),2);
  x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),4);
  BOOST_CHECK_CLOSE(zerocross[0],5.3333,epsilon);
  x = sp(data3,data3+sizeof(data3)/sizeof(double),zerocross.begin(),zerocross.size(),6);
  BOOST_CHECK_CLOSE(zerocross[0],5.5,epsilon);


  double data[] = {1.,2.,3.,4.,5.,6.,5.,4.,3.,2.,1.};

  // for lag 2
  // zero cross at 5

  x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),2);
  BOOST_CHECK_CLOSE(zerocross[0],5.,epsilon);
  x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),4);
  BOOST_CHECK_CLOSE(zerocross[0],5.,epsilon);
  x = sp(data,data+sizeof(data)/sizeof(double),zerocross.begin(),6);
  BOOST_CHECK_CLOSE(zerocross[0],5.,epsilon);

}

BOOST_AUTO_TEST_SUITE_END()

