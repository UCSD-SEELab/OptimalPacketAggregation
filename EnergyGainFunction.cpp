//
//  EnergyGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "EnergyGainFunction.hpp"

EnergyGainFunction::TGain
EnergyGainFunction::GetGain( const TTransmissionTime & x ) const
{
    return ( -1 / x.GetSeconds() );
}

EnergyGainFunction::TGain
EnergyGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    double xSeconds = x.GetSeconds();
    return ( 1 / ( xSeconds * xSeconds ) );
}
