// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>


#include "base/stats/uniform.h"
#include "base/base/base.h"
#include "base/base/interpolate.h"
#include "base/base/cumsum.h"

#include "base/ms/utilities/parabolafit.h"


BOOST_AUTO_TEST_SUITE(ParabolafitTest)


BOOST_AUTO_TEST_CASE(testApproxLinear)
{

  //    std::vector<double> x, y, ys, xout, yout;
  //    ralab::base::base::seq(-20.,20.,1., x);
  //    y.resize(x.size());
  //    //double (*p)(double, double) = pow;

  //    ralab::base::stats::runif(x.size(), y ,-2.,2. );
  //    ralab::base::cumsum(y.begin(),y.end(),ys);


  //    ralab::base::base::seq(-30.,30.,.1, xout);

  //    ralab::base::base::interpolate_linear(ys,xout,yout,-20);
  //    ralab::base::base::interpolate_cosine(ys,xout,yout,-20);

  //    ralab::base::base::interpolate_cubic(ys,xout,yout,-20);


  //    ////// constant approximation //////
  //    ralab::base::base::interpolate_Hermite(ys , xout,yout,1.,0.,-20);
}


BOOST_AUTO_TEST_CASE(testApproxLinearSequence)
{
  std::vector<double> x, y, ys, xout, yout;
  ralab::base::base::seq(-20.,20.,1., x);
  y.resize(x.size());
  //double (*p)(double, double) = pow;

  ralab::base::stats::runif(x.size(), y ,-2.,2. );
  ralab::base::cumsum(y.begin(),y.end(),ys);

  ralab::base::base::seq(-30.,30.,.1, xout);

  yout.resize(xout.size());
  ralab::base::base::interpolate_linear(
        ys.begin(),
        ys.end(),
        xout.begin(),
        xout.end(),
        yout.begin()
        ,-20
        );
  yout.resize(xout.size());
  ralab::base::base::interpolate_cosine(ys.begin(),ys.end(),
                                        xout.begin(),xout.end(),yout.begin(),-20);

  yout.resize(xout.size());
  ralab::base::base::interpolate_cubic(ys.begin(),ys.end(),
                                       xout.begin(),xout.end(),yout.begin(),-20);
  ////// constant approximation //////
  yout.resize(xout.size());
  ralab::base::base::interpolate_Hermite(ys.begin(),ys.end() ,
                                         xout.begin(),xout.end(),yout.begin(),1.,0.,-20);
}
BOOST_AUTO_TEST_SUITE_END()
