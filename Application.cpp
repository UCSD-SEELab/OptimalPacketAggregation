//
//  Application.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "Application.hpp"
#include "NoGainFunction.hpp"

Application::TApplicationId Application::globalIdCounter = 0;
Application::TApplicationMap Application::globalApplicationMap;

Application::Application( TGenerationPtr generation, TDeadlinePtr deadline ) : m_id( globalIdCounter ),
                                                                               m_generationProcess( generation ),
                                                                               m_deadlineProcess( deadline )
{
    ++globalIdCounter;
    this->m_measurementQueue = ns3::Create<MeasurementQueue>();
    this->m_generationProcess->SetId( this->m_id );
    this->m_generationProcess->SetMeasurementQueue( this->m_measurementQueue );
    
    this->SetMeasurementGainFunction( ns3::Create< NoGainFunction >() );
    
    globalApplicationMap.insert( std::make_pair( this->m_id, this ) );
}

Application::Application( TGenerationPtr generation,
                          TDeadlinePtr deadline,
                          const TGainFunctionPtr & gainFunction ) : m_id( globalIdCounter ),
                                                                    m_generationProcess( generation ),
                                                                    m_deadlineProcess( deadline )
{
    ++globalIdCounter;
    this->m_measurementQueue = ns3::Create<MeasurementQueue>();
    this->m_generationProcess->SetId( this->m_id );
    this->m_generationProcess->SetMeasurementQueue( this->m_measurementQueue );
    this->SetMeasurementGainFunction( gainFunction );
    
    globalApplicationMap.insert( std::make_pair( this->m_id, this ) );
}

void
Application::SetMeasurementGainFunction( const TGainFunctionPtr & gainFunction )
{
    this->m_gainFunction = gainFunction;
    this->m_gainFunction->SetProcesses( this->m_generationProcess, this->m_deadlineProcess );
}

void
Application::Print( void ) const
{
    std::cout << "Application " << this->m_id << std::endl;
    this->m_measurementQueue->Print();
}

GainFunction::TGain
Application::GetMeasurementGain( const GainFunction::TTransmissionTime & x ) const
{
    return ( this->m_gainFunction->GetGain( x ) );
}

GainFunction::TGain
Application::GetMeasurementGainDerivative( const GainFunction::TTransmissionTime & x ) const
{
    return ( this->m_gainFunction->GetGainDerivative( x ) );
}

void
Application::GetAllMeasurements( TMeasurementQueuePtr & measurementQueue )
{
    for( auto i = this->m_measurementQueue->Begin(); i != this->m_measurementQueue->End(); ++i )
    {
        ( *i )->SetDeadline( this->m_deadlineProcess->GetNextDeadline().GetSeconds() );
    }
    measurementQueue->Add( *( this->m_measurementQueue ) );
    this->m_measurementQueue->Empty();
}

MeasurementQueue::TQueueSize
Application::GetNumberOfQueuedMeasurements( void ) const
{
    return ( this->m_measurementQueue->Count() );
}
