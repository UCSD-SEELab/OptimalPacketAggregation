//
//  SuccessGainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef SuccessGainFunction_hpp
#define SuccessGainFunction_hpp

#include "GainFunction.hpp"

/**
 Implements the expiration minimization gain function.
**/
class SuccessGainFunction : public GainFunction
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
        
        /** Transmission time type **/
        typedef GainFunction::TTransmissionTime TTransmissionTime;
        
    public:
        /**
         Returns the expiration gain value.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
         **/
        TGain
        GetGain( const TTransmissionTime & x ) const;
        
        /**
         Returns the expiration gain derivative value.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
         **/
        TGain
        GetGainDerivative( const TTransmissionTime & x ) const;
    
};

#endif /* SuccessGainFunction_hpp */
