//
//  Simulation.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 9/25/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef Simulation_hpp
#define Simulation_hpp

#include <math.h>
#include <iostream>
#include <string>

#include <ns3/core-module.h>
#include <ns3/wifi-module.h>
#include <ns3/mobility-module.h>
#include <ns3/ipv4-global-routing-helper.h>
#include <ns3/dsdv-module.h>
#include <ns3/aodv-module.h>
#include <ns3/csma-module.h>
#include <ns3/propagation-module.h>

#include "TransmissionManagerHelper.hpp"
#include "SinkManagerHelper.hpp"

#include "StatisticsManager.hpp"

#include "DowntownTopologyHelper.hpp"

/**
 Main simulation class implementing all ns3 related connections and
 configurations.
**/
class Simulation
{
    private:
        /** Smart pointer to a Node **/
        typedef TransmissionManagerHelper::TNodePtr TNodePtr;
    
        /** Name of the transmission manager type **/
        typedef TransmissionManagerHelper::TTransmissionManagerName TTransmissionManagerName;
    
        /** Number of Nodes type **/
        typedef unsigned int TNumberOfNodes;
    
        /** Number fo hops type **/
        typedef unsigned int TNumberOfHops;
    
        /** Total simulation time type **/
        typedef double TSimulationTime;
    
        /** Coordinate type definition **/
        typedef double TCoordinate;
    
        /** Angle type definition **/
        typedef double TAngle;
    
        /** Communication radius type **/
        typedef TCoordinate TCommunicationRadius;
    
        /** Topology type **/
        typedef unsigned int TTopologyType;
    
        /** Implemented topology types */
        enum TopologyTypes
        {
            /** Linear topology type on a single line **/
            LinearTopology = ( TTopologyType )0,
            
            /** Radial topology type, radially expanding **/
            RadialTopology = ( TTopologyType )1,
            
            /** Downtown special topology type **/
            DowntownTopology = ( TTopologyType )2
        };
    
        /** Reception gain value type **/
        typedef double TRXGain;
    
        /** Number of building blocks type **/
        typedef DowntownTopologyHelper::TNumberOfBlocks TNumberOfBlocks;
    
    private:
        /** Number of nodes in the simulation **/
        TNumberOfNodes m_numberOfNodes = 10;
    
        /** Total amount of simulation seconds **/
        TSimulationTime m_simSeconds = 3600;
    
        /** The transmission manager to be used **/
        TTransmissionManagerName m_transmissionManagerName = "FiveGTransmissionManager";
    
        /** Number of Hops in the topology **/
        TNumberOfHops m_numberOfHops = 1;
    
        /** Communication radius of a node **/
        TCommunicationRadius m_communicationRadius = 300;
    
        /** Routing algorithm update rate for DSDV **/
        TSimulationTime m_routingUpdateRate = 360;
    
        /** Type of the topology used **/
        TTopologyType m_topologyType = DowntownTopology;
    
        /** Reception antenna gain in dB **/
        TRXGain m_rxGain = 20;
    
        /** Node container for the Sink Node. **/
        ns3::NodeContainer m_sinkNodeContainer;
    
        /** Node container for the sensor nodes **/
        ns3::NodeContainer m_sensorNodesContainer;
    
        /** Node container containing all nodes including the sink **/
        ns3::NodeContainer m_allNodesContainer;
    
        /** All Wireless Devices container for configuration in ns3 **/
        ns3::NetDeviceContainer m_allWirelessDevices;
    
        /** Pointer to the sink node **/
        TNodePtr m_sinkNode;
    
        /** IP address of the Sink Node **/
        TransmissionManagerHelper::TAddress m_sinkIPAddress;
    
        /** Name of log file **/
        std::string m_logFileName = "results.txt";
    
    private:
        /**
         Parses the command line for the options.
         \param argc Number of arguments.
         \param argv All arguments.
        **/
        void
        ParseCommandLine( int argc, char * argv[] );
    
        /**
         Creates ns3 Nodes and fills the containers.
        **/
        void
        CreateNodes( void );
    
        /**
         Creates a linear topology.
        **/
        void
        CreateLinearTopology( void );
    
        /**
         Creates a radially expanding topology
        **/
        void
        CreateRadialTopology( void );
    
        /**
         Creates a special downtown topology
        **/
        void
        CreateDowntownTopology( void );
    
        /**
         Creates the topology type selected in the command line argument
        **/
        void
        CreateTopology( void );
    
        /**
         Installs the DSDV routing algorithm
        **/
        void
        InstallDSDV( void );
    
        /**
         Installs the AODV routing algorithm
        **/
        void
        InstallAODV( void );
    
        /**
         Installs WiFi to all devices along with the channel.
        **/
        void
        InstallWiFi( void );
    
        /**
         Installs the IP v4 Addresses.
        **/
        void
        InstallIPAddresses( void );
    
        /**
         Configures all Nodes with the selected transmission manager.
        **/
        void
        ConfigureNodes( void );
    
        /**
         Starts the simulation and holds until it ends.
        **/
        void
        StartSimulation( void );
    
        /**
         A command line progress update information function.
        **/
        void
        SimulationProgress( void );
    
    public:
        /**
         Configures the simulation with the given command line options.
         \param argc Number of arguments.
         \param argv All arguments.
        **/
        void
        Configure( int argc, char * argv[] );
    
        /**
         Runs the simulation.
        **/
        void
        Run( void );
};

#endif /* Simulation_hpp */
