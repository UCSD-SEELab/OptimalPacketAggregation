//
//  TransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "TransmissionManager.hpp"
#include "NoGainFunction.hpp"
#include "StatisticsManager.hpp"
#include "ApplicationConfigureHelper.hpp"

void
TransmissionManager::InstallApplication( const TApplicationPtr & ptr )
{
    this->m_applications.push_back( ptr );
}

TransmissionManager::TransmissionManager( void )
{
    this->SetMessageGainFunction( ns3::Create< NoGainFunction >() );
}

void
TransmissionManager::Print( void ) const
{
    std::cout << "Transmission Manager Summary:" << std::endl;
    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        ( *i )->Print();
    }
}

void
TransmissionManager::SetSinkAddress( const TAddress & sinkAddress )
{
    ns3::TypeId tId = ns3::TypeId::LookupByName( "ns3::UdpSocketFactory" );
    this->m_sendingSocket = ns3::Socket::CreateSocket( this->m_installedNode, tId );
    TSocketAddress sinkSocket = TSocketAddress( sinkAddress, portNumber );
    this->m_sendingSocket->Connect( sinkSocket );
}

void
TransmissionManager::InstallOnNode( TNodePtr & node )
{
    this->m_installedNode = node;
}

TransmissionManager::TPacketPtr
TransmissionManager::CreatePacketFromMeasurements( void )
{
    auto measurementQueue = ns3::Create< MeasurementQueue >();
    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        ( *i )->GetAllMeasurements( measurementQueue );
    }
    
    unsigned int queueSize = measurementQueue->Size();
    auto queueBuffer = new unsigned char[ queueSize ];
    measurementQueue->WriteToBuffer( queueBuffer );
    
    TPacketPtr newPacket = ns3::Create< ns3::Packet >( queueBuffer, queueSize );
    delete[] queueBuffer;
    
    return ( newPacket );
}

void
TransmissionManager::SendAllMeasurements( void )
{
    TPacketPtr newPacket = this->CreatePacketFromMeasurements();
    this->m_sendingSocket->Send( newPacket );
    StatisticsManager::GetStatisticsManager().PacketTransmitted( this->m_installedNode );
}

MeasurementQueue::TQueueSize
TransmissionManager::GetTotalNumberOfMeasurements( void ) const
{
    MeasurementQueue::TQueueSize totalSize = 0;
    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        totalSize += ( *i )->GetNumberOfQueuedMeasurements();
    }
    return ( totalSize );
}
