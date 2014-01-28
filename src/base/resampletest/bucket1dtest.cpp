// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hello

#include <boost/test/unit_test.hpp>
#include "base/resample/bucket1d.h"
#include "base/resample/bin1d.h"

#include <algorithm>
#include <boost/timer.hpp>
#include "base/stats/uniform.h"
#include "base/resample/breakspec.h"
#include "base/resample/masscomparefunctors.h"


BOOST_AUTO_TEST_SUITE(Bucket1DTest)


BOOST_AUTO_TEST_CASE(testBin1D){
  double ref [] = {2., 2.1 , 5. , 5.1 , 7.1 , 7.15 , 10. , 10.1};
  std::vector<double> breaks;
  breaks.assign(ref , ref + sizeof(ref)/sizeof(double));

  ralab::base::resample::Bin1D bin(breaks);
  BOOST_CHECK_EQUAL(bin(2.-1e-8) , 0);
  BOOST_CHECK_EQUAL(bin(2.+1e-8) , 1);
  BOOST_CHECK_EQUAL(bin(2.1) ,1);
  BOOST_CHECK_EQUAL(bin(2.1 + 1e-9) , 2);
}

BOOST_AUTO_TEST_CASE(testBin1D2){
  double ref [] = {2., 2.1 , 5. , 5.1 , 7.1 , 7.15 , 10. , 10.1};
  std::vector<double> breaks;
  breaks.assign(ref , ref + sizeof(ref)/sizeof(double));

  ralab::base::resample::Bin1D bin(breaks);
  std::vector<int32_t> idx;
  std::vector<double> dist;
  bin(2. -1e-8 , 2. + 2e-4,  idx, dist ) ;
  BOOST_CHECK_EQUAL(idx[0],-1);
  BOOST_CHECK_EQUAL(idx[1],0);
  BOOST_CHECK_SMALL(dist[0] - 1e-8,1e-10);
  BOOST_CHECK_SMALL(dist[1] - 2e-4,1e-10);

  bin(2. -1e-8 , 2.1 + 2e-4,  idx, dist ) ;
  BOOST_CHECK_EQUAL(idx[0],-1);
  BOOST_CHECK_EQUAL(idx[1],0);
  BOOST_CHECK_EQUAL(idx[2],1);
  BOOST_CHECK_SMALL(dist[0] - 1e-8,1e-10 );
  BOOST_CHECK_SMALL(dist[1] - 0.1,1e-10 );
  BOOST_CHECK_SMALL(dist[2] - 2e-4,1e-10 );

  bin(2. -1e-8 , 5.1 + 2e-4,  idx, dist ) ;
  double resd [] = {1e-8, 0.1, 2.9, 0.1, 2e-4};
  int  idxr[] = {-1,0,1,2,3};
  bool x = std::equal(idxr , idxr + sizeof(idxr)/sizeof(int), idx.begin());
  BOOST_CHECK(x);
  x = std::equal(resd , resd + sizeof(resd)/sizeof(double), dist.begin(), ralab::base::resample::DaCompFunctor<double>(1e-8));
  BOOST_CHECK(x);

  bin(2. - 2e-4 , 2. - 1e-4,  idx, dist ) ;
  BOOST_CHECK_EQUAL(idx[0],-1);
  BOOST_CHECK_SMALL(dist[0]- 1e-4,1e-14);
  bin(2.1 - 2e-4 , 2.1 - 1e-4,  idx, dist ) ;
  BOOST_CHECK_EQUAL(idx[0],0);
  BOOST_CHECK_SMALL(dist[0]- 1e-4,1e-14);
  bin(2.1 - 1e-4 , 7.1 + 2e-4,  idx, dist ) ;

  //testing end span
  bin(10.1 - 1e-4 , 10.1 + 2e-4,  idx, dist ) ;
  std::cout << breaks[idx[0]] << std::endl;
  std::cout << breaks[idx[1]] << std::endl;

  bin(5.1 - 1e-4 , 10.1 + 2e-4,  idx, dist ) ;
  std::cout << idx[0] << std::endl;

  bin(10.1 + 1e-4 , 10.1 + 2e-4,  idx, dist ) ;
  std::cout << idx[0] << std::endl;


}


BOOST_AUTO_TEST_CASE(testHist)
{
  std::vector<double> breaks;
  std::vector<uint32_t> indicator;
  //                 0     1     2    3     4      5     6
  double ref [] = {2., 2.1 , 5. , 5.1 , 7.1 , 7.15 , 10. , 10.1};
  // We cover 0.1+0.1+0.05+0.1 = 0.35 //
  breaks.assign(ref , ref + sizeof(ref)/sizeof(double));

  /*!\brief length indic is length(ref) - 1
                                */
  //                   0   1   2   3   4   5   6
  uint32_t indic[] = { 1 , 0 , 1 , 0 , 1 , 0 , 1};

  indicator.assign(
        indic
        ,indic + sizeof(indic)/sizeof(uint32_t)
        );

  ralab::base::resample::Bucket1D b1d( breaks, indicator);
  std::vector<double> sample;
  std::pair< size_t , bool > rb;
  rb = b1d.operator()( 1. );
  rb = b1d.operator()( 2. );
  rb = b1d.operator()( 2.05 );
  rb = b1d.operator()( 2.1 );
  rb = b1d.operator()( 4. );
  rb = b1d.operator()( 5. );
  rb = b1d.operator()( 5.01 );
  rb = b1d.operator()( 5.1 );
  rb = b1d.operator()(6.);
  rb = b1d.operator()(7.);
  rb = b1d.operator()(7.12); // 4,true
  rb = b1d.operator()(8.);
  rb = b1d.operator()( 10.1 );
  rb = b1d.operator()( 13. );

  sample.push_back( 1. );//false
  sample.push_back( 2. );//false
  sample.push_back( 2.05 );//#2 -> 0
  sample.push_back( 2.1 );//#3 -> 0
  sample.push_back( 4. );//false
  sample.push_back( 5. );//false
  sample.push_back( 5.01 );//#6 -> 2
  sample.push_back( 5.1 );//#7 -> 2
  sample.push_back( 10.1 );//#8 -> 6
  sample.push_back( 13. );//false

  std::vector< std::pair< size_t , size_t > > res;
  b1d( sample.begin() , sample.end() , res );
  BOOST_CHECK(res[0].first == 0 && res[0].second == 2);
  BOOST_CHECK(res[1].first == 0 && res[1].second == 3);
}

BOOST_AUTO_TEST_SUITE_END()




