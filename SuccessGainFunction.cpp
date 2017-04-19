//
//  SuccessGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "SuccessGainFunction.hpp"

SuccessGainFunction::TGain
SuccessGainFunction::GetGain( const TTransmissionTime & x ) const
{
    if ( this->m_deadlineProcess->GetExpectedDeadline() > x )
    {
        return ( x.GetSeconds() * this->m_generationProcess->GetMeanGenerationRate() );
    }
    return ( this->m_deadlineProcess->GetExpectedDeadline().GetSeconds() * this->m_generationProcess->GetMeanGenerationRate() );
}

SuccessGainFunction::TGain
SuccessGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    if ( this->m_deadlineProcess->GetExpectedDeadline() > x )
    {
        return ( this->m_generationProcess->GetMeanGenerationRate() );
    }
    return ( 0 );
}