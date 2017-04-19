//
//  NoGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "NoGainFunction.hpp"

NoGainFunction::TGain
NoGainFunction::GetGain( const TTransmissionTime & x ) const
{
    if ( this->m_generationProcess == nullptr )
    {
        return ( 1 );
    }
    return ( this->m_generationProcess->GetMeanGenerationRate() );
}

NoGainFunction::TGain
NoGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    return ( 0 );
}