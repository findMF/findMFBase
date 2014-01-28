// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT


#ifndef BIN1D_H
#define BIN1D_H

#include <vector>
#include <algorithm>
#include <functional>
#include <vector>
#include <utility>
#include <stdexcept>

namespace ralab
{
  namespace base
  {
    namespace resample
    {

      //Class returns the index a value belongs too given breaks
      struct Bin1D
      {
        std::vector<double> breaks_; // boundaries
        double * begbreaks_;
        double * endbreaks_;
      public:
        Bin1D():breaks_(),begbreaks_(0),endbreaks_(0){}
        /*!\brief CTor*/
        Bin1D(
            std::vector<double> & breaks // breaks
            ):breaks_(), begbreaks_(0), endbreaks_(0)
        {
          this->setBreaks(breaks);
        }

        /// CTor
        Bin1D(
            const Bin1D & rhs // breaks
            ):breaks_(), begbreaks_(0), endbreaks_(0)
        {
          this->setBreaks(rhs.breaks_);
        }


        /// set the breaks
        void setBreaks(const std::vector<double> & breaks){
          breaks_.assign( breaks.begin(), breaks.end() );
          std::sort(breaks_.begin(),breaks_.end());
          reset();
        }

        /// if you modify the breaks member you must call this.
        /// TODO - change the api to remove this function
        void reset(){
          begbreaks_ = &breaks_[0];
          endbreaks_ = begbreaks_ + breaks_.size();
        }

        /// get the breaks used to split the massrange
        void getBreaks(std::vector<double> & breaks) const{
          breaks.assign(begbreaks_,endbreaks_);
        }

        /// get the breaks used to split the massrange
        const std::vector<double> & getBreaks() const{
          return breaks_;
        }

        /// the size_t indicates to which bucket dat belongs too.
        /// The bool indicates if a new bucket is of interest
        bool inRange(double dat) const{
          return (dat > breaks_.front() && dat < breaks_.back());
        }

        /// determine the bin of a datapoint
        std::size_t operator()(double dat) const
        {
          double * it2 = std::lower_bound(begbreaks_,endbreaks_,dat);
          size_t ub = std::distance(begbreaks_,it2);
          return ub;
        }

        /// determine the bin of a datapoint
        void operator()(double dat1, //!< [in] start mass
                        double dat2, //!< [in] end mass
                        std::vector<int32_t> & idx, //!< [out] bins to add to
                        std::vector<double> & dist //!< [out] weights to use
                        ) const
        {
          double * it1 = std::lower_bound(begbreaks_,endbreaks_,dat1);
          double * it2 = std::lower_bound(begbreaks_,endbreaks_,dat2);

          // the reason for the -1
          // is to shift the output signal 1 pixel to the left.
          size_t signalshift = 1;

          size_t ub1 = std::distance(begbreaks_,it1);
          size_t ub2 = std::distance(begbreaks_,it2);


          // this must not be zero because of the signalshift of -1
//          if(ub1 == 0)
//            ub1 =1;
//          if(ub2 == 0)
//            ub2 =1;

          // than you can't shift the signal to the left therefore no shift
          //if(ub1 == 0){
          //  signalshift = 0;
          //}
          int64_t n = static_cast<int64_t>(ub2-ub1)+1;
          idx.resize(n);
          dist.resize(n);


          if(ub1 == ub2){
            idx[0] = ub1 - signalshift;
            dist[0] = dat2 - dat1;
            return;
          }
          else{
            for(int64_t i = 0; it1 != (it2+1) ; i++, it1++){
              idx[i] = ub1 + i - signalshift;
              if(i == 0)
              {
                dist[i] = *(it1) - dat1;
              }
              else if( i < n - 1 )
              {
                dist[i] = *(it1) - *(it1-1);
              }
              else
              {
                dist[i] = dat2 - *(it1-1);
              }
            }
          }


        }
      };

    }//resample
  }//base
}//ralab



#endif // BUCKET1D_H

