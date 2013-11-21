// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/chemistry/iisotopeenvelope.h"


// a sample implementation of the IisotopeEnvelope interface
namespace ralab{
  struct IsotopeEnvelope : ralab::base::chemistry::IIsotopeEnvelope
  {
    IsotopeEnvelope(){}
    //just a dummy implementation
    ralab::base::chemistry::MassAbundance isotopeEnvelope(double mass) const //override
    {
      ralab::base::chemistry::MassAbundance mab;
      mab.push_back(35.22);
      mab.push_back(33.75);
      mab.push_back(19.21);
      mab.push_back(8.07);
      mab.push_back(2.73);
      mab.push_back(0.78);
      return mab;
    }

  };

}


BOOST_AUTO_TEST_SUITE(IsotopeEnvelopeTest)

// Tests that the Foo::Bar() method does Abc.
BOOST_AUTO_TEST_CASE(testEnvelope)
{
  ralab::base::chemistry::IIsotopeEnvelope * bla = new ralab::IsotopeEnvelope;
  ralab::base::chemistry::MassAbundance blue;
  blue = bla->isotopeEnvelope(1700.);
  BOOST_CHECK_CLOSE(blue[0], 35.22 , 1e-7);
}

BOOST_AUTO_TEST_SUITE_END()


