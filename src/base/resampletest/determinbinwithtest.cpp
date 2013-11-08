// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#include "base/resample/determinebinwidth.h"
#include <gtest/gtest.h>



namespace{
  class DetermineBinWidth: public ::testing::Test{
  protected:
    std::vector<double> mass_;
    DetermineBinWidth(){}

    void SetUp(){
      double mass[]= {302.8929, 302.8953, 302.8978, 302.9052, 302.9076, 302.9101, 302.9150, 302.9789, 303.1263, 303.3475, 303.3819, 303.8763,
                      303.9033, 303.9058, 303.9156, 303.9181, 303.9230, 304.1150, 304.1396, 304.3217, 304.4030, 304.4252, 304.8095, 304.8563,
                      304.8859, 305.0436, 305.0683, 305.0757, 305.0978, 305.2409, 305.5689, 305.8157, 305.8379, 305.8848, 305.8922, 305.9070,
                      305.9194, 305.9737, 305.9836, 306.0033, 306.0354, 306.1663, 306.3219, 306.7939, 306.8582, 306.9027, 306.9274, 306.9447,
                      306.9571, 307.3851, 307.8405, 307.8975, 307.9149, 307.9297, 308.1403, 308.1477, 308.8294, 308.8518, 308.8592, 308.8791,
                      308.8890, 308.8914, 308.9212, 308.9560, 309.2165, 309.2339, 309.4052, 309.4523, 309.7976, 309.8597, 309.8622, 309.8746,
                      309.8771, 309.8969, 309.9143, 310.4413, 310.6304, 310.8443, 310.8717, 310.8742, 310.8842, 310.8867, 310.9066, 310.9240,
                      310.9290, 310.9439, 311.0161, 311.0783, 311.1804, 311.3422, 311.3846, 311.4095, 311.6113, 311.8206, 311.8306, 311.8380,
                      311.8430, 311.8455, 311.8505, 311.8580, 311.8605};
      mass_.assign(mass,mass + sizeof(mass)/sizeof(double));

    }
  };

}//end namespace
TEST_F(DetermineBinWidth,testConvert)
{
  ralab::base::resample::SamplingWith sw;
  double bla = sw(mass_.begin(),mass_.end());
  ASSERT_NEAR(bla, 0.00014 ,0.00001);

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
