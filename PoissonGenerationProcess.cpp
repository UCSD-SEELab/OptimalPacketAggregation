//
//  PoissonGenerationProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "PoissonGenerationProcess.hpp"

PoissonGenerationProcess::PoissonGenerationProcess( const TMeanRate lambda ) : GenerationProcess( lambda )
{
    this->m_uniformGenerator = ns3::CreateObject< ns3::UniformRandomVariable > ();
    this->m_uniformGenerator->SetAttribute( "Min", ns3::DoubleValue ( 0 ) );
    this->m_uniformGenerator->SetAttribute( "Max", ns3::DoubleValue ( 1 ) );
    
    ns3::Simulator::Schedule( this->GetNextTime(), &PoissonGenerationProcess::ScheduleGeneration, this );
}

void
PoissonGenerationProcess::ScheduleGeneration( void )
{
    this->CreateMeasurement();
    ns3::Simulator::Schedule( this->GetNextTime(), &PoissonGenerationProcess::ScheduleGeneration, this );
}

void
PoissonGenerationProcess::CreateMeasurement( void )
{
    TMeasurementPtr newMeasurement = ns3::Create<Measurement>( this->m_id );
    this->AddMeasurement( newMeasurement );
}

PoissonGenerationProcess::TArrivalTime
PoissonGenerationProcess::GetNextTime( void ) const
{
    double poissonTime = -log( 1 - this->m_uniformGenerator->GetValue() ) / this->m_meanRate;
    return ( ns3::Seconds( poissonTime ) );
}