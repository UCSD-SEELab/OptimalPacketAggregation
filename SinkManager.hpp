//
//  SinkManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef SinkManager_hpp
#define SinkManager_hpp

#include <ns3/network-module.h>
#include <ns3/internet-module.h>

#include "TransmissionManager.hpp"

/**
 This class manages the Sink Node to receive the measurements and process them
 for statistics.
**/
class SinkManager : public ns3::Object
{
    public:
        /** Smart pointer to a Socket **/
        typedef ns3::Ptr< ns3::Socket > TSocketPtr;
    
        /** Smart pointer to a Node **/
        typedef ns3::Ptr< ns3::Node > TNodePtr;
    
        /** IPv4 Address type **/
        typedef ns3::Ipv4Address TAddress;
    
        /** Smart pointer to a Packet **/
        typedef ns3::Ptr< ns3::Packet > TPacketPtr;
    
        /** Internet Socket Address type **/
        typedef ns3::InetSocketAddress TSocketAddress;
    
        /** Special Socket Port values **/
        enum PortValues
        {
            /** Port number used by all Transmission Managers **/
            portNumber = TransmissionManager::portNumber
        };
    
    private:
        /** The receiving socket pointer **/
        TSocketPtr m_receivingSocket;
    
        /** Pointer to the actual sink node **/
        TNodePtr m_installedNode;
    
    private:
        /**
         Receive a packet destined to the sink.
         \param socket Socket of reception
        **/
        void
        ReceivePacket( TSocketPtr socket );
    
        /**
         Sets the socket address of the sink node to the socket
        **/
        void
        SetSinkAddress( void );
    
    public:
        /** 
         ns3 related Type ID definition
         \return Type ID of this class
        **/
        static ns3::TypeId
        GetTypeId( void );

        /**
         Install the sink manager on the given node.
         \param node Node to be installed on.
        **/
        void
        InstallOnNode( const TNodePtr & node );
};

#endif /* SinkManager_hpp */
