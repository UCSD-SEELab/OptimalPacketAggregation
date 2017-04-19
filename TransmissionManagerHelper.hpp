//
//  TransmissionManagerHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef TransmissionManagerHelper_hpp
#define TransmissionManagerHelper_hpp

#include <ns3/node.h>
#include <ns3/node-container.h>
#include "TransmissionManager.hpp"

class TransmissionManager;

/**
 This class installs and aggregates TransmissionManager class on nodes.
**/
class TransmissionManagerHelper
{
    public:
        /** Smart pointer to Node type **/
        typedef TransmissionManager::TNodePtr TNodePtr;
    
        /** Socket Address type **/
        typedef TransmissionManager::TAddress TAddress;
    
        /** Transmission Manager implementation name type **/
        typedef std::string TTransmissionManagerName;
    
    public:
        /**
         Installs a transmission manager on a node and configures its sink.
         \param sinkNode The common sink node on the network.
         \param node The node to installed onto.
         \param name Name of the Transmission Manager implementation.
        **/
        void
        Install( const TAddress & sinkNode,
                 TNodePtr node,
                 const TTransmissionManagerName & name ) const;
    
        /**
         Installs transmission managers on multiple nodes at once.
         \param sinkNode The common sink node on the network.
         \param c Node container for multiple nodes.
         \param name Name of the Transmission Manager implementation.
        **/
        void
        Install( const TAddress & sinkNode,
                 ns3::NodeContainer c,
                 const TTransmissionManagerName & name ) const;
};

#endif /* TransmissionManagerHelper_hpp */
