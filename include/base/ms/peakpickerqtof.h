// Copyright : ETH Zurich
// License   : three-clause BSD license
// Authors   : Witold Wolski
// for full text refer to files: LICENSE, AUTHORS and COPYRIGHT

#ifndef PEAKPICKER_H
#define PEAKPICKER_H

#include <stdint.h>
#include <boost/math/special_functions.hpp>
#include "base/resample/convert2dense.h"
#include "base/filter/filter.h"
#include "base/ms/simplepicker.h"
#include "base/filter/gaussfilter.h"
#include "base/base/interpolate.h"
#include "base/resample/determinebinwidth.h"
#include "base/utils/copyif.h"


namespace ralab{
  namespace base{
    namespace ms{

      /// resamples spectrum, apply smoothing,
      /// determines zero crossings,
      /// integrates peaks.

      template<typename TReal>
      struct SimplePeakArea{
        TReal integwith_;

        SimplePeakArea(TReal integwith):integwith_(integwith){}

        /// intagrates the peak intesnities
        template<typename Tzerocross, typename Tintensity, typename Tout>
        void operator()( Tzerocross beginZ,
                         Tzerocross endZ,
                         Tintensity intensity,
                         Tintensity resmpled,
                         Tout area)const
        {
          typedef typename std::iterator_traits<Tout>::value_type AreaType;
          for( ; beginZ != endZ ; ++beginZ , ++area )
            {
              size_t idx = static_cast<size_t>( *beginZ );
              size_t start = static_cast<size_t>( boost::math::round( idx - integwith_ ) );
              size_t end = static_cast<size_t>( boost::math::round( idx + integwith_ + 2.) );
              AreaType aread = 0.;
              for( ; start != end ; ++start )
                {
                  aread += *(resmpled + start);
                }
              *area = aread;
            }
        }
      };

      /// extends peak to the left and to the right to the next local minimum or a predefined threshol
      /// or a maximum allowed extension.
      template<typename TReal>
      struct LocalMinPeakArea{
        typedef TReal value_type;
        TReal integwith_;
        TReal threshold_;

        LocalMinPeakArea(TReal integwith,//!<maximal allowed peak width +- in pixel
                         TReal threshold = .1// minimum intensity
            ):integwith_(integwith),threshold_(threshold){}



        /// intagrates the peak intesnities
        template< typename Tzerocross, typename Tintensity, typename Tout >
        void operator()( Tzerocross beginZ,
                         Tzerocross endZ,
                         Tintensity intensity,
                         Tintensity resampled,
                         Tout area) const
        {
          typedef typename std::iterator_traits<Tout>::value_type AreaType;
          for( ; beginZ != endZ ; ++beginZ , ++area )
            {
              size_t idx = static_cast<size_t>( *beginZ );
              size_t start = static_cast<size_t>( boost::math::round( idx - integwith_ ) );
              size_t end = static_cast<size_t>( boost::math::round( idx + integwith_ + 2) );

              Tintensity st = intensity + start;
              Tintensity en = intensity + end;
              Tintensity center = intensity + idx;
              std::ptrdiff_t x1 = std::distance(st, center);
              std::ptrdiff_t y1 = std::distance(center,en);
              mextend(st , en , center);
              std::ptrdiff_t x2 = std::distance(intensity,st);
              std::ptrdiff_t y2 = std::distance(intensity,en);
              std::ptrdiff_t pp = std::distance(st,en);
              AreaType areav = std::accumulate(resampled+x2,resampled+y2,0.);
              *area = areav;
            }
        }

      private:
        ///exend peak to left and rigth
        template<typename TInt >
        void mextend( TInt &start, TInt &end, TInt idx) const
        {
          typedef typename std::iterator_traits<TInt>::value_type Intensitytype;
          //
          for(TInt intens = idx ; intens >= start;  --intens){
              Intensitytype val1 = *intens;
              Intensitytype val2 = *(intens-1);
              if(val1 > threshold_){
                  if(val1 < val2 ){
                      start = intens;
                      break;
                    }
                }
              else{
                  start = intens;
                  break;
                }
            }

          for(TInt intens = idx ; intens <= end;  ++intens){
              Intensitytype val1 = *intens;
              Intensitytype val2 = *(intens+1);
              if(val1 > threshold_){
                  if(val1 < val2 ){
                      end = intens;
                      break;
                    }
                }
              else{
                  end = intens;
                  break;
                }
            }
        }
      };

      /// resamples spectrum, apply smoothing,
      /// determines zero crossings,
      /// integrates peaks.
      template<typename TReal, template <typename B> class TIntegrator >
      struct PeakPicker{
        typedef TReal value_type;
        typedef TIntegrator<value_type> PeakIntegrator;

        TReal resolution_;
        ralab::base::resample::Convert2Dense c2d_; // resamples spectrum
        std::vector<TReal> resampledmz_, resampledintensity_; // keeps result of convert to dense
        std::vector<TReal> filter_, zerocross_, smoothedintensity_; // working variables
        std::vector<TReal> peakmass_, peakarea_; //results
        TReal smoothwith_;
        TReal integrationWidth_;
        ralab::base::ms::SimplePicker<TReal> simplepicker_;
        ralab::base::resample::SamplingWith sw_;
        PeakIntegrator integrator_;
        TReal intensitythreshold_;
        bool area_;

        PeakPicker(TReal resolution, //!< instrument resolution
                   std::pair<TReal, TReal> & massrange, //!< mass range of spectrum
                   TReal width = 2., //!< smooth width
                   TReal intwidth = 2., //!< integration width used for area compuation
                   TReal intensitythreshold = 10., // intensity threshold
                   bool area = true
            ): resolution_(resolution),smoothwith_(width),
          integrationWidth_(intwidth),sw_(),integrator_(integrationWidth_),
          intensitythreshold_(intensitythreshold),area_(area)
        {
          c2d_.defBreak(massrange,ralab::base::resample::resolution2ppm(resolution));
          c2d_.getMids(resampledmz_);
          ralab::base::filter::getGaussianFilterQuantile(filter_,width);
        }


        template<typename Tmass, typename Tintensity>
        void operator()(Tmass begmz, Tmass endmz, Tintensity begint )
        {
          typename std::iterator_traits<Tintensity>::value_type minint = *std::upper_bound(begint,begint+std::distance(begmz,endmz),0.1);
          //typename std::iterator_traits<Tintensity>::value_type minint =*std::min_element(begint,begint+std::distance(begmz,endmz));
          TReal threshold = static_cast<TReal>(minint) * intensitythreshold_;

          //determine sampling with
          double a = sw_(begmz,endmz);
          //resmpale the spectrum
          c2d_.am_ = a;
          c2d_.convert2dense(begmz,endmz, begint, resampledintensity_);

          //smooth the resampled spectrum
          ralab::base::filter::filter(resampledintensity_ , filter_ , smoothedintensity_ , true);
          //determine zero crossings
          zerocross_.resize( smoothedintensity_.size()/2 );
          size_t nrzerocross = simplepicker_( smoothedintensity_.begin( ) , smoothedintensity_.end() , zerocross_.begin(), zerocross_.size());

          peakmass_.resize(nrzerocross);
          //determine mass of zerocrossing
          ralab::base::base::interpolate_linear( resampledmz_.begin() , resampledmz_.end() ,
                                                 zerocross_.begin(),  zerocross_.begin()+nrzerocross ,
                                                 peakmass_.begin());

          //determine peak area
          if(area_){
              peakarea_.resize(nrzerocross);
              integrator_( zerocross_.begin(), zerocross_.begin() + nrzerocross ,
                           smoothedintensity_.begin(),resampledintensity_.begin(), peakarea_.begin() );
            }else{
              //determine intensity
              peakarea_.resize(nrzerocross);
              ralab::base::base::interpolate_cubic( smoothedintensity_.begin() , smoothedintensity_.end() ,
                                                    zerocross_.begin(),  zerocross_.begin()+nrzerocross ,
                                                    peakarea_.begin());
            }
          if(threshold > 0.01){
              filter(threshold);
            }
        }

        //clean the masses using the threshold
        void filter(TReal threshold){
          typename std::vector<TReal>::iterator a = ralab::base::utils::copy_if(peakarea_.begin(),peakarea_.end(),peakmass_.begin(),
                                                                                peakmass_.begin(),boost::bind(std::greater<TReal>(),_1,threshold));
          peakmass_.resize(std::distance(peakmass_.begin(),a));
          typename std::vector<TReal>::iterator b = ralab::base::utils::copy_if(peakarea_.begin(),peakarea_.end(),
                                                                                peakarea_.begin(),boost::bind(std::greater<TReal>(),_1,threshold));
          peakarea_.resize(std::distance(peakarea_.begin(),b));
          //int x = 1;
        }

        const std::vector<TReal> & getPeakMass(){
          return peakmass_;
        }

        const std::vector<TReal> & getPeakArea(){
          return peakarea_;
        }

        const std::vector<TReal> & getResampledMZ(){
          return resampledmz_;
        }

        const std::vector<TReal> & getResampledIntensity(){
          return resampledintensity_;
        }

        const std::vector<TReal> & getSmoothedIntensity(){
          return smoothedintensity_;
        }


      };
    }//ms
  }//base
}//ralab



#endif // PEAKPICKER_H
