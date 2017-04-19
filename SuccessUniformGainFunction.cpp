//
//  SuccessUniformGainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/22/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "SuccessUniformGainFunction.hpp"
#include "UniformDeadlineProcess.hpp"

SuccessUniformGainFunction::TGain
SuccessUniformGainFunction::GetGain( const TTransmissionTime & x ) const
{
    UniformDeadlineProcess::TBoundSeconds xSeconds = x.GetSeconds();
    if ( xSeconds <= this->m_lower )
    {
        return ( this->m_generationProcess->GetMeanGenerationRate() );
    }
    return ( ( this->m_upper - xSeconds ) * this->m_generationProcess->GetMeanGenerationRate() / ( this->m_upper - this->m_lower ) );
}

SuccessUniformGainFunction::TGain
SuccessUniformGainFunction::GetGainDerivative( const TTransmissionTime & x ) const
{
    UniformDeadlineProcess::TBoundSeconds xSeconds = x.GetSeconds();
    if ( xSeconds <= this->m_lower )
    {
        return ( ( this->m_lower - xSeconds ) / xSeconds );
    }
    return ( -this->m_generationProcess->GetMeanGenerationRate() / ( this->m_upper - this->m_lower ) );
}

void
SuccessUniformGainFunction::SetProcesses( const TGenerationPtr & gen,
                                          const TDeadlinePtr & deadline )
{
    auto uniformDeadline = ns3::DynamicCast< UniformDeadlineProcess >( deadline );
    this->m_generationProcess = gen;
    this->m_lower = uniformDeadline->GetLowerBound();
    this->m_upper = uniformDeadline->GetUpperBound();
    if ( this->m_lower >= this->m_upper )
    {
        this->m_upper = this->m_lower + 0.000001;
    }
}