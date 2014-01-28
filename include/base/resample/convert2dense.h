#ifndef CONVERT2DENSE_H
#define CONVERT2DENSE_H

#include <vector>
#include <iostream>
#include <boost/assert.hpp>
#include "base/resample/masscomparefunctors.h"
#include "base/resample/breakspec.h"
#include "base/resample/bin1d.h"


namespace ralab
{
  namespace base
  {
    namespace resample
    {
      struct Convert2Dense
      {
        //private:
        ralab::base::resample::Bin1D bin_; //!< binner
      private:
        std::vector<int32_t> idx_;//!< small workder vecs
        std::vector<double> weight_; //!< small worker
        double am_; //!< parameter describing the sampling width

      public:

        // set the sampling with.


        void setAm(double am , bool force = false){
          // some of the spectra in the map might have very few singals
          // and am might be wrongly estimated (unplausible large).
          // in this case keep the old value.
          if(am < 2*am_ || force){
            am_ = am;
          }
        }

        /// initialize am with some unplausible large value.
        Convert2Dense(double am = 0.1):bin_(),idx_(),weight_(),am_(am){
        }

        /// computes split points of an map.
        std::size_t defBreak(std::pair<double, double> & mzrange, double ppm ){
          ralab::base::resample::PPMCompFunctor<double> ppmf(ppm);

          ralab::base::resample::breaks( mzrange.first - 1. , mzrange.second + 1. , ppmf , bin_.breaks_ );
          // must be called because breaks_ was just changed
          bin_.reset();
          return bin_.breaks_.size();
        }


        /// determine the bin
        double getBin(double mass1, double mass2,
                      std::vector<int> & idx, std::vector<double> & weight) const {
          double predmass2 = mass1 + (am_* sqrt(mass1))*1.01;
          if(mass2 > predmass2){
            mass2 = predmass2;
          }

          double deltamass = mass2-mass1;
          double deltamasshalf;
          if(true){
            deltamasshalf= deltamass/2.;
          }
          else{
            deltamasshalf = deltamass;
          }

          bin_(mass1-deltamasshalf,mass2-deltamasshalf,idx,weight);
          double sum = std::accumulate(weight_.begin(),weight_.end(),0.);
          BOOST_ASSERT(fabs(deltamass- sum) < 1e-11);
          return deltamass;
        }

        /// Converts a sparse spec to a dense spec
        template<typename Tmass, typename Tintens, typename Tout >
        void convert2dense(Tmass beginMass,
                           Tmass endMass,
                           Tintens intens,
                           Tout ass
                           )
        {
          for( ; beginMass != (endMass -1) ; ++beginMass, ++intens ){
            double mass1 = *beginMass;
            double mass2 = *(beginMass+1);

            double deltamass = this->getBin(mass1,mass2,idx_,weight_);

            double intensd = static_cast<double>(*intens);

            double check = 0.;
            for(std::size_t i = 0 ; i < idx_.size();++i){
              if((idx_[i]>=0) &(idx_[i] < static_cast<int32_t>(bin_.breaks_.size() - 1)))
              {
                double bb= intensd * weight_[i]/deltamass;
                *(ass + idx_[i])  += bb;
                check += bb;
              }
            }
            BOOST_ASSERT( fabs(check - intensd) < 1e-3 );
          }
        }//convert2dense

        ///
        void getMids(std::vector<double> & mids)
        {
          ralab::base::resample::getMids(bin_.breaks_, mids );
        }

        /// Converts a sparse spec to a dense spec
        template<typename Tmass, typename Tintens >
        void convert2dense(Tmass beginMass, Tmass endMass, Tintens intens,
                           std::vector<typename std::iterator_traits<Tintens>::value_type > & gg
                           ){
          gg.resize(bin_.breaks_.size() - 1);
          convert2dense(beginMass,endMass, intens, gg.begin());
        }
      };


    }
  }
}
#endif // CONVERT2DENSE_H
