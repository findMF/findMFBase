// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello
#include <boost/test/unit_test.hpp>

#include "base/utils/readwritelines.h"

#include "base/resample/masscomparefunctors.h"
#include <boost/bind.hpp>


BOOST_AUTO_TEST_SUITE(ReadLines)

BOOST_AUTO_TEST_CASE(writeLines)
{
  std::vector<std::string>  lines;
  lines.push_back("bla da da da");
  lines.push_back("ramba zamba");
  lines.push_back("hello world");
  ralab::base::utils::writeLines(lines,"test.txt");

  std::vector<std::string> readback;
  ralab::base::utils::readLines("test.txt",readback);
  bool test = std::equal(readback.begin(),readback.end(),lines.begin());
  BOOST_CHECK(test);
}

BOOST_AUTO_TEST_SUITE_END()

