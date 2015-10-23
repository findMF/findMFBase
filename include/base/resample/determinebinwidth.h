#ifndef DETERMINEBINWIDTH_H
#define DETERMINEBINWIDTH_H


#include <base/resample/utilities/determinebinwidth.h>

#include <vector>
#include <cmath>
#include <boost/assert.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <boost/bind.hpp>
#include <algorithm>

#include <base/base/diff.h>

namespace ralab
{
  namespace base
  {
    namespace resample
    {
      /// determine vendor spectrum sampling with
      struct SamplingWith{
        std::vector<double> diff_;
        std::vector<double> summ_;
        std::vector<double> am_;

        //expects a sorted sequence
        template<typename TRealI>
        double operator()(TRealI begin, TRealI end)
        {
          double am;
          //BOOST_ASSERT(!boost::range::is_sorted(begin,end));
          std::size_t N = std::distance(begin,end);
          if(N > 1){
          diff_.resize(N-1);
          summ_.resize(N-1);
          am_.resize(N-1);
          // compute differences
          ralab::base::base::diff(begin,end,diff_.begin(),1);

          // compute average
          utilities::summ( begin , end,summ_.begin());
          //square the sum
          // square root averages
          // std::transform(summ_.begin(),summ_.end(),summ_.begin(), boost::bind(sqrt,_1));
          
		  // compute diff/averages
          std::transform(diff_.begin(),diff_.end(),summ_.begin(),am_.begin(),std::divides<double>());
          // sort averages
          std::sort(am_.begin(),am_.end());
          // determine am
          am = utilities::determine(am_.begin(),am_.end());
          }
          else{
          am = 0.;
          }
          return am;
        }
      };

    }
  }
}


#endif // DETERMINEBINWIDTH_H
