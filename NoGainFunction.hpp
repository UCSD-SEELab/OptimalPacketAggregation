//
//  NoGainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef NoGainFunction_hpp
#define NoGainFunction_hpp

#include "GainFunction.hpp"

/**
 Provides unity gain function.
**/
class NoGainFunction : public GainFunction
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
        
        /** Transmission time type **/
        typedef GainFunction::TTransmissionTime TTransmissionTime;
        
    public:
        /**
         Returns unity.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
         **/
        TGain
        GetGain( const TTransmissionTime & x ) const;
        
        /**
         Returns zero.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
         **/
        TGain
        GetGainDerivative( const TTransmissionTime & x ) const;
};

#endif /* NoGainFunction_hpp */
