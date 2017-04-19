//
//  StatisticsManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "StatisticsManager.hpp"
#include "BaseStation.hpp"

#include <fstream>

StatisticsManager &
StatisticsManager::GetStatisticsManager( void )
{
    static StatisticsManager sm;
    return ( sm );
}

void
StatisticsManager::MeasurementGenerated( const TMeasurementPtr & measurement )
{
    this->m_generatedMeasurements[measurement->GetId()].Add( measurement );
}

void
StatisticsManager::MeasurementReceived( const TMeasurementPtr & measurement )
{
    this->m_receivedMeasurements[measurement->GetId()].Add( measurement );
}

void
StatisticsManager::PacketTransmitted( TNodePtr & transmittingNode )
{
    ++this->m_txPacketCounts[transmittingNode];
}

void
StatisticsManager::PacketReceived( void )
{
    ++this->m_rxPacketCount;
}

void
StatisticsManager::PrintStatistics( void )
{
    std::ofstream log( this->m_logFileName, std::ios::app );
    std::ofstream timeSeries;
    if ( this->m_writeTimeseries )
    {
        timeSeries.open( "timeSeries.csv", std::ios::out );
    }
    std::cout << "Generated Ids: " << this->m_generatedMeasurements.size() << std::endl;
    std::cout << "Received Ids: " << this->m_receivedMeasurements.size() << std::endl;
    
    if ( this->m_receivedMeasurements.size() == 0 )
    {
        std::cout << "Num Transmitted:      " << this->GetTotalNumberOfTransmitted() << std::endl;
        std::cout << "Num Received:         " << this->m_rxPacketCount << std::endl;
        std::cout << "Nothing received - No man's land" << std::endl;
        return;
    }
    
    log << this->m_generatedMeasurements.size() << "," << this->m_receivedMeasurements.size() << std::endl;
    
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        auto id = i->first;
        
        log << id << ","
            << this->m_generatedMeasurements[id].Count() << ","
            << this->m_receivedMeasurements[id].Count() << ","
            << this->GetAverageDelay( this->m_receivedMeasurements[id] ).GetSeconds() << ","
            << this->GetMaximumDelay( this->m_receivedMeasurements[id] ).GetSeconds() << ","
            << this->GetExpirationRate( this->m_receivedMeasurements[id] ) << ","
            << this->GetTotalInformationFreshness( this->m_receivedMeasurements[id] ).GetSeconds() << ","
            << this->GetAverageInformationFreshness( this->m_receivedMeasurements[id] ).GetSeconds()
            << std::endl;
        
        if ( this->m_writeTimeseries )
        {
            timeSeries << id << "," << this->m_receivedMeasurements[id].Count() << ",0" << std::endl;
            for ( auto j = this->m_receivedMeasurements[id].Begin(); j != this->m_receivedMeasurements[id].End(); ++j )
            {
                timeSeries << ( *j )->GetGenerationTime() << ","
                           << ( *j )->GetGenerationTime() + ( *j )->GetDeadline()<< ","
                           << ( *j )->GetReceptionTime() << std::endl;
            }
        }
        
    }
    
    std::cout << "====== ====== ====== ======" << std::endl;
    std::cout << "Maximum Delay:        " << this->GetMaximumDelay().GetSeconds() << std::endl;
    std::cout << "Average Delay:        " << this->GetAverageDelay().GetSeconds() << std::endl;
    std::cout << "Total Freshness:      " << this->GetTotalInformationFreshness().GetSeconds() << std::endl;
    std::cout << "Freshness per packet: " << this->GetInformationFreshnessPerPacket().GetSeconds() << std::endl;
    std::cout << "Average Freshness:    " << this->GetAverageInformationFreshness().GetSeconds() << std::endl;
    std::cout << "Expiration Rate:      " << this->GetExpirationRate() << std::endl;
    std::cout << "Num Transmitted:      " << this->GetTotalNumberOfTransmitted() << std::endl;
    std::cout << "Num Received:         " << this->m_rxPacketCount << std::endl;
    std::cout << "Num Broadcasts        " << BaseStation::GetBaseStation().GetNumberOfBroadcasts() << std::endl;
    std::cout << "Num Updates           " << BaseStation::GetBaseStation().GetNumberOfUpdateRequests() << std::endl;
    
    log << this->GetMaximumDelay().GetSeconds() << ","
        << this->GetAverageDelay().GetSeconds() << ","
        << this->GetTotalInformationFreshness().GetSeconds() << ","
        << this->GetInformationFreshnessPerPacket().GetSeconds() << ","
        << this->GetAverageInformationFreshness().GetSeconds() << ","
        << this->GetExpirationRate() << ","
        << this->GetTotalNumberOfTransmitted() << ","
        << BaseStation::GetBaseStation().GetNumberOfBroadcasts() << ","
        << BaseStation::GetBaseStation().GetNumberOfUpdateRequests()
        << std::endl;
}

StatisticsManager::TDelay
StatisticsManager::GetTotalDelay( const MeasurementQueue & queue ) const
{
    Measurement::TReceptionTime delay = 0;
    for ( auto i = queue.Begin(); i != queue.End(); ++i )
    {
        delay += ( *i )->GetDelay();
    }
    
    return ( ns3::Seconds( delay ) );
}

StatisticsManager::TDelay
StatisticsManager::GetAverageDelay( const MeasurementQueue & queue ) const
{
    return ( this->GetTotalDelay( queue ) / ( double )queue.Count() );
}

StatisticsManager::TDelay
StatisticsManager::GetMaximumDelay( const MeasurementQueue & queue ) const
{
    Measurement::TReceptionTime delay = 0;
    for ( auto i = queue.Begin(); i != queue.End(); ++i )
    {
        auto thisDelay = ( *i )->GetDelay();
        if ( thisDelay > delay )
        {
            delay = thisDelay;
        }
    }
    
    return ( ns3::Seconds( delay ) );
}

StatisticsManager::TExpirationRate
StatisticsManager::GetExpirationRate( const MeasurementQueue & queue ) const
{
    return ( ( double )this->GetNumberOfExpired( queue ) / ( double )queue.Count() );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetNumberOfExpired( const MeasurementQueue & queue ) const
{
    MeasurementQueue::TQueueSize expiredNumber = 0;
    for ( auto i = queue.Begin(); i != queue.End(); ++i )
    {
        if ( ( *i )->IsExpired() )
        {
            ++expiredNumber;
        }
    }
    
    return ( expiredNumber );
}

StatisticsManager::TInformationFreshness
StatisticsManager::GetTotalInformationFreshness( const MeasurementQueue & queue ) const
{
    Measurement::TDeadline totalFreshness = 0;
    for ( auto i = queue.Begin(); i != queue.End(); ++i )
    {
        totalFreshness += ( *i )->GetFreshness();
    }
    
    return ( ns3::Seconds( totalFreshness ) );
}

StatisticsManager::TInformationFreshness
StatisticsManager::GetAverageInformationFreshness( const MeasurementQueue & queue ) const
{
    TInformationFreshness totalFreshness = this->GetTotalInformationFreshness( queue );
    return ( totalFreshness / ( double )queue.Count() );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetTotalNumberOfLost( void ) const
{
    return ( this->GetTotalNumberOfSent() - this->GetTotalNumberOfReceived() );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetTotalNumberOfExpired( void ) const
{
    MeasurementQueue::TQueueSize expiredNumber = 0;
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        expiredNumber += this->GetNumberOfExpired( i->second );
    }
    return ( expiredNumber );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetTotalNumberOfSent( void ) const
{
    MeasurementQueue::TQueueSize sentNumber = 0;
    for ( auto i = this->m_generatedMeasurements.begin(); i != m_generatedMeasurements.end(); ++i )
    {
        sentNumber += i->second.Count();
    }
    return ( sentNumber );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetTotalNumberOfTransmitted( void ) const
{
    MeasurementQueue::TQueueSize sentNumber = 0;
    for ( auto i = this->m_txPacketCounts.begin(); i != m_txPacketCounts.end(); ++i )
    {
        sentNumber += i->second;
    }
    return ( sentNumber );
}

MeasurementQueue::TQueueSize
StatisticsManager::GetTotalNumberOfReceived( void ) const
{
    MeasurementQueue::TQueueSize receivedNumber = 0;
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        receivedNumber += i->second.Count();
    }
    return ( receivedNumber );
}

StatisticsManager::TDelay
StatisticsManager::GetAverageDelay( void ) const
{
    TDelay totalDelay = ns3::Seconds( 0 );
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        totalDelay += this->GetTotalDelay( i->second );
    }
    return ( totalDelay / ( double )this->GetTotalNumberOfReceived() );
}

StatisticsManager::TDelay
StatisticsManager::GetMaximumDelay( void ) const
{
    TDelay maximumDelay = ns3::Seconds( 0 );
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        TDelay thisDelay = this->GetMaximumDelay( i->second );
        if ( thisDelay > maximumDelay )
        {
            maximumDelay = thisDelay;
        }
    }
    return ( maximumDelay );
}

StatisticsManager::TInformationFreshness
StatisticsManager::GetTotalInformationFreshness( void ) const
{
    TInformationFreshness totalFreshness = ns3::Seconds( 0 );
    for ( auto i = this->m_receivedMeasurements.begin(); i != m_receivedMeasurements.end(); ++i )
    {
        totalFreshness += this->GetTotalInformationFreshness( i->second );
    }
    
    return ( totalFreshness );
}

StatisticsManager::TInformationFreshness
StatisticsManager::GetAverageInformationFreshness( void ) const
{
    return ( this->GetTotalInformationFreshness() / ( double )this->GetTotalNumberOfReceived() );
}

StatisticsManager::TInformationFreshness
StatisticsManager::GetInformationFreshnessPerPacket( void ) const
{
    return ( this->GetTotalInformationFreshness() / ( double )this->m_rxPacketCount );
}

StatisticsManager::TExpirationRate
StatisticsManager::GetExpirationRate( void ) const
{
    return ( ( double )this->GetTotalNumberOfExpired() / ( double )this->GetTotalNumberOfReceived() );
}
