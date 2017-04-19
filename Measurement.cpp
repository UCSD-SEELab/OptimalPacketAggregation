//
//  Measurement.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "Measurement.hpp"

Measurement::TMeasurement Measurement::measurementCounter = 0;

Measurement::Measurement( void ) : m_id( InvalidId ),
                                   m_value( 0 )
{
    this->m_generationTime = ns3::Now().GetSeconds();
    this->m_receptionTime = 0;
}

Measurement::Measurement( const Measurement & copy ) : m_id( copy.m_id ),
                                                       m_value( copy.m_value ),
                                                       m_generationTime( copy.m_generationTime ),
                                                       m_receptionTime( copy.m_receptionTime )
{
}

Measurement::Measurement( const TId id,
                          const TMeasurement value ) : m_id( id ),
                                                       m_value( value )
{
    this->m_generationTime = ns3::Now().GetSeconds();
    this->m_receptionTime = 0;
    ++measurementCounter;
}

void*
Measurement::ReadFromBuffer( void* buffer )
{
    char* currentBuffer = ( char* )buffer;
    memcpy( &( this->m_id ), currentBuffer, IdSize );
    currentBuffer += IdSize;
    memcpy( &( this->m_value ), currentBuffer, MeasurementSize );
    currentBuffer += MeasurementSize;
    memcpy( &( this->m_generationTime ), currentBuffer, GenerationTimeSize );
    currentBuffer += GenerationTimeSize;
    memcpy( &( this->m_receptionTime ), currentBuffer, ReceptionTimeSize );
    currentBuffer += ReceptionTimeSize;
    memcpy( &( this->m_deadline ), currentBuffer, DeadlineSize );
    currentBuffer += DeadlineSize;
    
    return ( currentBuffer );
}

void*
Measurement::WriteToBuffer( void* buffer )
{
    char* currentBuffer = ( char* )buffer;
    memcpy( currentBuffer, &( this->m_id ), IdSize );
    currentBuffer += IdSize;
    memcpy( currentBuffer, &( this->m_value ), MeasurementSize );
    currentBuffer += MeasurementSize;
    memcpy( currentBuffer, &( this->m_generationTime ), GenerationTimeSize );
    currentBuffer += GenerationTimeSize;
    memcpy( currentBuffer, &( this->m_receptionTime ), ReceptionTimeSize );
    currentBuffer += ReceptionTimeSize;
    memcpy( currentBuffer, &( this->m_deadline ), DeadlineSize );
    currentBuffer += DeadlineSize;
    
    return ( currentBuffer );
}

void
Measurement::MarkReceived( void )
{
    this->m_receptionTime = ns3::Now().GetSeconds();
}

void
Measurement::Print( void )
{
    std::cout << "Id: " << this->m_id
              << " Value: " << this->m_value << std::endl
              << "Sent: " << ns3::Seconds( this->m_generationTime ) << std::endl
              << "Received: " << ns3::Seconds( this->m_receptionTime ) << std::endl;
}