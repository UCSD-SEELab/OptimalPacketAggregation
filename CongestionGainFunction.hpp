//
//  CongestionGainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef CongestionGainFunction_hpp
#define CongestionGainFunction_hpp

#include "GainFunction.hpp"

/**
 Implements the Congestion minimization gain function.
**/
class CongestionGainFunction : public GainFunction
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
        
        /** Transmission time type **/
        typedef GainFunction::TTransmissionTime TTransmissionTime;
        
    public:
        /**
         Returns the congestion gain value.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
         **/
        TGain
        GetGain( const TTransmissionTime & x ) const;
        
        /**
         Returns the congestion gain derivative value.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
         **/
        TGain
        GetGainDerivative( const TTransmissionTime & x ) const;
};

#endif /* CongestionGainFunction_hpp */
