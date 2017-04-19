//
//  ConstantGenerationProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "ConstantGenerationProcess.hpp"

ConstantGenerationProcess::ConstantGenerationProcess( const TSamplingInterval samplingInterval ) : GenerationProcess( 1 / samplingInterval.GetSeconds() ),
                                                                                                   m_samplingInterval( samplingInterval )
{
    ns3::Simulator::Schedule( this->m_samplingInterval, &ConstantGenerationProcess::ScheduleGeneration, this );
}

void
ConstantGenerationProcess::ScheduleGeneration( void )
{
    this->CreateMeasurement();
    ns3::Simulator::Schedule( this->m_samplingInterval, &ConstantGenerationProcess::ScheduleGeneration, this );
}

void
ConstantGenerationProcess::CreateMeasurement( void )
{
    TMeasurementPtr newMeasurement = ns3::Create<Measurement>( this->m_id );
    this->AddMeasurement( newMeasurement );
}