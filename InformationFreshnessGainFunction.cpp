//
//  InformationFreshnessGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "InformationFreshnessGainFunction.hpp"

InformationFreshnessGainFunction::TGain
InformationFreshnessGainFunction::GetGain( const TTransmissionTime & x ) const
{
    return ( ( this->m_deadlineProcess->GetExpectedDeadline() - x / 2 ).GetSeconds() * x.GetSeconds() * this->m_generationProcess->GetMeanGenerationRate() );
}

InformationFreshnessGainFunction::TGain
InformationFreshnessGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    return ( ( this->m_deadlineProcess->GetExpectedDeadline() - x ).GetSeconds() * this->m_generationProcess->GetMeanGenerationRate() );
}
