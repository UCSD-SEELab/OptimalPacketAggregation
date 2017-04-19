//
//  SinkManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "SinkManager.hpp"
#include "StatisticsManager.hpp"

NS_LOG_COMPONENT_DEFINE("SinkManager");

NS_OBJECT_ENSURE_REGISTERED(SinkManager);

ns3::TypeId
SinkManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "SinkManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<SinkManager> ()
    ;
    
    return ( tid );
}

void
SinkManager::SetSinkAddress( void )
{
    this->m_receivingSocket = ns3::Socket::CreateSocket( this->m_installedNode, ns3::TypeId::LookupByName( "ns3::UdpSocketFactory" ) );
    TSocketAddress localSocketAddress = TSocketAddress( ns3::Ipv4Address::GetAny(), portNumber );
    this->m_receivingSocket->Bind( localSocketAddress );
    this->m_receivingSocket->SetRecvCallback( ns3::MakeCallback( &SinkManager::ReceivePacket, this ) );
}

void
SinkManager::InstallOnNode( const TNodePtr & node )
{
    this->m_installedNode = node;
    this->SetSinkAddress();
}

void
SinkManager::ReceivePacket( TSocketPtr socket )
{
    ns3::Ptr<ns3::Packet> packet = socket->Recv();
    unsigned int size = packet->GetSize();
    unsigned char* buffer = new unsigned char[size];
    packet->CopyData( ( uint8_t* )buffer, size );
    
    MeasurementQueue allMeasurements;
    allMeasurements.ReadFromBuffer( buffer, size );
    delete[] buffer;
    
    StatisticsManager::GetStatisticsManager().PacketReceived();
    
    for ( auto i = allMeasurements.Begin(); i != allMeasurements.End(); ++i )
    {
        ( *i )->MarkReceived();
        StatisticsManager::GetStatisticsManager().MeasurementReceived( *i );
    }
}
