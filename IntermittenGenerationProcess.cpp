//
//  IntermittenGenerationProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 12/6/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "IntermittenGenerationProcess.hpp"

IntermittentGenerationProcess::IntermittentGenerationProcess( const TMeanRate slowRate,
                                                              const TMeanRate fastRate,
                                                              const TArrivalTime minSlowTime,
                                                              const TArrivalTime maxSlowTime,
                                                              const TArrivalTime minFastTime,
                                                              const TArrivalTime maxFastTime ) : GenerationProcess( slowRate ),
                                                                                                 m_slowStateCurrently( false ),
                                                                                                 m_slowRate( slowRate ),
                                                                                                 m_fastRate( fastRate ),
                                                                                                 m_minimumSlowTime( minSlowTime ),
                                                                                                 m_maximumSlowTime( maxSlowTime ),
                                                                                                 m_minimumFastTime( minFastTime ),
                                                                                                 m_maximumFastTime( maxFastTime )
{
    this->m_uniformGenerator = ns3::CreateObject< ns3::UniformRandomVariable > ();
    this->m_uniformGenerator->SetAttribute( "Min", ns3::DoubleValue ( 0 ) );
    this->m_uniformGenerator->SetAttribute( "Max", ns3::DoubleValue ( 1 ) );
    this->ScheduleSwitch();
    ns3::Simulator::Schedule( this->GetNextTime(), &IntermittentGenerationProcess::ScheduleGeneration, this );
}

void
IntermittentGenerationProcess::ScheduleGeneration( void )
{
    this->CreateMeasurement();
    ns3::Simulator::Schedule( this->GetNextTime(), &IntermittentGenerationProcess::ScheduleGeneration, this );
}

void
IntermittentGenerationProcess::CreateMeasurement( void )
{
    TMeasurementPtr newMeasurement = ns3::Create<Measurement>( this->m_id );
    this->AddMeasurement( newMeasurement );
}

IntermittentGenerationProcess::TArrivalTime
IntermittentGenerationProcess::GetNextTime( void ) const
{
    double poissonTime = -log( 1 - this->m_uniformGenerator->GetValue() ) / this->m_meanRate;
    return ( ns3::Seconds( poissonTime ) );
}

void
IntermittentGenerationProcess::ScheduleSwitch( void )
{
    if ( this->m_slowStateCurrently )
    {
        TArrivalTime endOfFastState = this->m_minimumFastTime +
                                      this->m_uniformGenerator->GetValue() * ( this->m_maximumFastTime - this->m_minimumFastTime );
        this->m_slowStateCurrently = false;
        this->SetMeanGenerationRate( this->m_fastRate );
        ns3::Simulator::Schedule( endOfFastState, &IntermittentGenerationProcess::ScheduleSwitch, this );
    }
    else
    {
        TArrivalTime endOfSlowState = this->m_minimumSlowTime +
        this->m_uniformGenerator->GetValue() * ( this->m_maximumSlowTime - this->m_minimumSlowTime );
        this->m_slowStateCurrently = true;
        this->SetMeanGenerationRate( this->m_slowRate );
        ns3::Simulator::Schedule( endOfSlowState, &IntermittentGenerationProcess::ScheduleSwitch, this );
    }
}
