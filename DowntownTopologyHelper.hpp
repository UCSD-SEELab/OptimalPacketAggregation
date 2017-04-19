//
//  DowntownTopologyHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 9/25/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef DowntownTopologyHelper_hpp
#define DowntownTopologyHelper_hpp

#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/mobility-module.h"
#include "ns3/config-store.h"
#include <ns3/buildings-helper.h>
#include <ns3/hybrid-buildings-propagation-loss-model.h>
#include <ns3/constant-position-mobility-model.h>

#include <iomanip>
#include <string>
#include <vector>

/**
 This class generates a City Downtown topology with multiple building blocks.
 The sizes are measured from San Diego over Google Maps. All units are meters.
**/
class DowntownTopologyHelper
{
    public:
        /** Coordinate type **/
        typedef double TCoordinate;
    
        /** Number of blocks type **/
        typedef unsigned int TNumberOfBlocks;
    
        /** Smart pointer to a node **/
        typedef ns3::Ptr<ns3::Node> TNodePtr;
    
    private:
        /** X-Size of a building wall **/
        TCoordinate m_buildingX = 60;
    
        /** Y-Size of a building wall **/
        TCoordinate m_buildingY = ( TCoordinate )90;
    
        /** Height of a building wall **/
        TCoordinate m_buildingZ = ( TCoordinate )20;
    
        /** X-Size of a building block **/
        TCoordinate m_blockX = ( TCoordinate )78;
    
        /** Y-Size of a building block **/
        TCoordinate m_blockY = ( TCoordinate )104;
    
        /** Unoccupied margin on the block, X-direction **/
        TCoordinate m_marginX = ( TCoordinate )9;
    
        /** Unoccupied margin on the block, Y-direction **/
        TCoordinate m_marginY = ( TCoordinate )7;
    
        /** Height of the base station **/
        TCoordinate m_sinkHeight = 39.3;
    
        /** Height of an end-user **/
        TCoordinate m_sensorHeight = 1;

        /** Number of blocks on the X-dimension **/
        TNumberOfBlocks m_xNumber = 10;
    
        /** Number of blocks on the Y-dimension **/
        TNumberOfBlocks m_yNumber = 10;
    
        /** Pointer to the Sink Node **/
        ns3::Ptr<ns3::Node> m_sinkNode;
    
        /** Container of all the other nodes **/
        ns3::NodeContainer m_sensorNodesContainer;
    
    private:
        /**
         Creates buildings using ns3 building class. This will be used for
         propagation models.
        **/
        void
        CreateBuildings( void );
    
        /**
         Allocates positions for the ns3 mobility class. This represents the
         initial positions of the nodes.
        **/
        void
        AllocatePositions( void );
    
        /**
         Reads configuration file "downtown.txt"
        **/
        void
        ReadConfiguration( void );
    
    public:   
        /**
         Configure the given sink node and rest of the user nodes. Set their
         positions and mobility models.
         \param sinkNode Pointer to the sink node.
         \param sensorNodesContainer Container of the rest of the nodes.
        **/
        void
        Configure( const TNodePtr sinkNode, ns3::NodeContainer & sensorNodesContainer );
};

#endif /* DowntownTopologyHelper_hpp */
