//
//  CongestionGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "CongestionGainFunction.hpp"

CongestionGainFunction::TGain
CongestionGainFunction::GetGain( const TTransmissionTime & x ) const
{
    return ( 1 );
}

CongestionGainFunction::TGain
CongestionGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    return ( 1 / ( x.GetSeconds() * x.GetSeconds() ) );
}