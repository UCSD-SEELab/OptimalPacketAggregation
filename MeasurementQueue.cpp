//
//  MeasurementQueue.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "MeasurementQueue.hpp"

void
MeasurementQueue::Add( const TMeasurementPtr & item )
{
    this->m_queue.push_back( item );
}

void
MeasurementQueue::Add( MeasurementQueue & items )
{
    for ( auto i = items.m_queue.cbegin(); i != items.m_queue.cend(); ++i )
    {
        this->m_queue.push_back( ( *i ) );
    }
}

void
MeasurementQueue::Empty( void )
{
    this->m_queue.clear();
}

Measurement::TMeasurement totalDelay = 0;
unsigned int count = 0;

void
MeasurementQueue::Print( void ) const
{
    for ( auto i = this->m_queue.begin(); i != this->m_queue.end(); ++i )
    {
        ( *i )->Print();
        totalDelay += ns3::Now().GetSeconds() - ( *i )->GetValue();
        ++count;
    }
    
    if ( count != 0 )
    std::cout << "Average Value of Delay: " << ( totalDelay / count ) << std::endl;
}

void*
MeasurementQueue::ReadFromBuffer( void* buffer, const unsigned int bufferSize )
{
    void* currentBuffer = buffer;
    TQueueSize numMeasurements = bufferSize / Measurement::TotalSize;
    for ( TQueueSize index = 0; index < numMeasurements; ++index )
    {
        TMeasurementPtr newMeasurement = ns3::Create<Measurement>();
        currentBuffer = newMeasurement->ReadFromBuffer( currentBuffer );
        this->Add( newMeasurement );
    }
    
    return ( currentBuffer );
}

void*
MeasurementQueue::WriteToBuffer( void* buffer )
{
    void* currentBuffer = buffer;
    for ( auto i = this->m_queue.begin(); i != this->m_queue.end(); ++i )
    {
        currentBuffer = ( *i )->WriteToBuffer( currentBuffer );
    }
    
    return ( currentBuffer );
}
