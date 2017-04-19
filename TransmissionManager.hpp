//
//  TransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef TransmissionManager_hpp
#define TransmissionManager_hpp

#include "Application.hpp"
#include <ns3/network-module.h>
#include <ns3/internet-module.h>

/**
 Base Transmission Manager class defining all communication related
 functionalities. The inheriting class must implement the Start and
 configuration functions. The start function enables aggregation time
 determination.
**/
class TransmissionManager : public ns3::Object
{
    private:
        /** Installed Applications List type. **/
        typedef std::list< TApplicationPtr > TApplicationList;
    
        /** Smart Pointer to a Gain Function **/
        typedef ns3::Ptr< GainFunction > TGainFunctionPtr;
    
    public:
        /** Smart Pointer to a Socket **/
        typedef ns3::Ptr< ns3::Socket > TSocketPtr;
    
        /** Smart Pointer to a Node **/
        typedef ns3::Ptr< ns3::Node > TNodePtr;
    
        /** IP v4 Address type **/
        typedef ns3::Ipv4Address TAddress;
    
        /** Smart pointer to a Packet **/
        typedef ns3::Ptr< ns3::Packet > TPacketPtr;
    
        /** Socket Address type **/
        typedef ns3::InetSocketAddress TSocketAddress;
    
        /** Port values used for communication **/
        enum PortValues
        {
            /** Port number used by all applications **/
            portNumber = ( unsigned short ) 4477
        };
    
    protected:
        /** Installed applications list **/
        TApplicationList m_applications;
    
        /** Packet level gain function **/
        TGainFunctionPtr m_messageGainFunction;
    
        /** Sending socket **/
        TSocketPtr m_sendingSocket;
    
        /** Pointer to the installed node **/
        TNodePtr m_installedNode;
    
    public:
        /** Constructor to set the initial values. **/
        TransmissionManager( void );
    
        /**
         Installs a new application.
         \param ptr Pointer to the new application.
        **/
        void
        InstallApplication( const TApplicationPtr & ptr );
    
        /**
         Sets the Packet level gain function applied to all applications.
         \param ptr Gain function pointer.
         \tparam GainFunctionType Any type of gain function implementation.
        **/
        template <typename GainFunctionType>
        void
        SetMessageGainFunction( const ns3::Ptr<GainFunctionType> & ptr )
        {
            this->SetMessageGainFunction( ns3::DynamicCast< GainFunction >( ptr ) );
        }
    
        /**
         Sets the packet level gain function applied to all applications.
         \param ptr Gain function pointer.
        **/
        void
        SetMessageGainFunction( const TGainFunctionPtr & ptr )
        {
            this->m_messageGainFunction = ptr;
        }
    
        /**
         Sets the Sink Address for communication.
         \param sinkAddress Address of the Sink Node.
        **/
        void
        SetSinkAddress( const TAddress & sinkAddress );
    
        /**
         Installs on a Node by aggregating onto the Object.
         \param node Node to be installed on.
        **/
        void
        InstallOnNode( TNodePtr & node );
    
        /**
         Virtual starting function implemented by the inheriting class. This
         function starts the algorithm determining the aggregation time.
        **/
        virtual void
        Start( void ) = 0;
    
        /**
         Prints information on the transmission manager.
        **/
        void
        Print( void ) const;
    
        /**
         Creates a packet from all measurements in byte stream format.
         \return Created packet containing all measurements.
        **/
        TPacketPtr
        CreatePacketFromMeasurements( void );
    
        /**
         Sends all measurements in the aggregation queue.
        **/
        void
        SendAllMeasurements( void );
    
        /**
         Virtual function to read the configuration file.
        **/
        virtual void
        ReadConfiguration( void ) = 0;
    
    protected:
        /**
         Calculates the total number of queued measurements in all applicaitons.
         \return Total number of queued measurements.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfMeasurements( void ) const;
};

#endif /* TransmissionManager_hpp */
