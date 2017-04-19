//
//  EnergyGainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef EnergyGainFunction_hpp
#define EnergyGainFunction_hpp

#include "GainFunction.hpp"

/**
 Implements the Energy consumption minimization gain function.
**/
class EnergyGainFunction : public GainFunction
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
    
        /** Transmission time type **/
        typedef GainFunction::TTransmissionTime TTransmissionTime;
        
    public:
        /**
         Returns the energy gain value.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
         **/
        TGain
        GetGain( const TTransmissionTime & x ) const;
        
        /**
         Returns the energy gain derivative value.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
         **/
        TGain
        GetGainDerivative( const TTransmissionTime & x ) const;
};

#endif /* EnergyGainFunction_hpp */
