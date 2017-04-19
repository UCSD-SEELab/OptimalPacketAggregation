//
//  SinkManagerHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef SinkManagerHelper_hpp
#define SinkManagerHelper_hpp

#include <ns3/node.h>
#include <ns3/node-container.h>
#include "SinkManager.hpp"


class SinkManager;

/**
 This class helps the SinkManager class to be installed and aggregated to nodes.
**/
class SinkManagerHelper
{
    public:
        /** Smart pointer to a Node **/
        typedef SinkManager::TNodePtr TNodePtr;
    
    public:
        /**
         Installs and aggregates SinkManager onto a node.
         \param node Node to be installed on.
        **/
        void
        Install( TNodePtr node ) const;
    
        /**
         Installs SinkManager on multiple nodes.
         \param c Container of nodes to be installed on.
        **/
        void
        Install( ns3::NodeContainer c ) const;
};

#endif /* SinkManagerHelper_hpp */
