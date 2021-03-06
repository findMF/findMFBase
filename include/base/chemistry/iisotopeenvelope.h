#ifndef IISOTOPEENVELOPE_H
#define IISOTOPEENVELOPE_H

#include <vector>

namespace ralab
{
  namespace base
  {
    namespace chemistry
    {

      //std::pair first is mass second is relative abundance
      //typedef std::vector< std::pair< double , double> > MassAbundance;
      typedef std::vector<double> MassAbundance;
      //
      struct IIsotopeEnvelope{
        // given a mass returns the MassAbundance (isotope envelope).
        virtual ~IIsotopeEnvelope(){}
        virtual MassAbundance isotopeEnvelope(double mass) const = 0;
      };
    }//end ms
  }//end base
}//ralab

#endif // IISOTOPEENVELOPE_H
