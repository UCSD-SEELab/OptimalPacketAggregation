//
//  OldSimulationMain.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 9/25/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

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

void
UpdateUser( unsigned int total )
{
    std::cout << 100.0 * ( ns3::Now().GetSeconds() / ( double )total ) << "%||";
    std::cout.flush();
    ns3::Simulator::Schedule( ns3::Seconds( ( double )total / 10.0 ) , &UpdateUser, total );
}

int
OldMain( int argc, char * argv[] )
{
    std::cout << "================////////////////=================" << std::endl;
    
    unsigned int numberOfNodes = 3;
    unsigned int simSeconds = 3600;
    std::string transmissionManagerName = "MultihopTransmissionManager";
    unsigned int numberOfHops = 2;
    double radius = 300;
    double updateRate = 360;
    
    ns3::CommandLine cmd;
    
    cmd.AddValue( "numNodes", "Number of Nodes, including sink", numberOfNodes );
    cmd.AddValue( "tmName", "Transmission Manager Name", transmissionManagerName );
    cmd.AddValue( "simSec", "Simulation Length in Seconds", simSeconds );
    cmd.AddValue( "numHops", "Number of Hops, (N-1) divisible by H(H+1)/2", numberOfHops );
    cmd.AddValue( "radius", "Radius from sink node", radius );
    cmd.AddValue( "updateRate", "Routing Update Rate", updateRate );
    
    cmd.Parse( argc, argv );
    
    std::ofstream log( "results.txt", std::ios::app );
    log << transmissionManagerName << "," << numberOfNodes << "," << simSeconds << std::endl;
    log.close();
    
    std::cout << transmissionManagerName << " - Number of Nodes: " << numberOfNodes << ", Hops: " << numberOfHops << std::endl;
    
    ns3::NodeContainer sinkNodeContainer;
    sinkNodeContainer.Create( 1 );
    auto sinkNode = sinkNodeContainer.Get ( 0 );
    
    ns3::NodeContainer sensorNodeContainer;
    sensorNodeContainer.Create( numberOfNodes - 1 );
    
    ns3::NodeContainer allNodes;
    allNodes.Add( sinkNodeContainer );
    allNodes.Add( sensorNodeContainer );
    
    ns3::MobilityHelper mobilityHelper;
    ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<ns3::ListPositionAllocator>();
    
    positionAlloc->Add( ns3::Vector( 0, 0, 0 ) );
    
    std::vector<double> xList;
    std::vector<double> yList;
    
    if ( numberOfNodes == numberOfHops + 1 )
    {
        for ( unsigned int hopIndex = 1; hopIndex <= numberOfHops; ++hopIndex )
        {
            double nodeAngle = 0;
            double hopRadius = radius * ( double )hopIndex;
            double x = cos( nodeAngle ) * hopRadius;
            double y = sin( nodeAngle ) * hopRadius;
            xList.push_back( x );
            yList.push_back( y );
            positionAlloc->Add( ns3::Vector( x, y, 0.0 ) );
        }
    }
    else
    {
        unsigned int nodePerHop = std::ceil( 2.0 * ( double )( numberOfNodes - 1 ) / ( double )( numberOfHops * ( numberOfHops + 1 ) ) );
        std::cout << "Nodes per hop: " << nodePerHop << std::endl;
        for ( unsigned int hopIndex = 1; hopIndex <= numberOfHops; ++hopIndex )
        {
            double hopRadius = radius * ( double )hopIndex;
            unsigned int nodesInThisHop = nodePerHop * hopIndex;
            for ( unsigned int nodeIndex = 0; nodeIndex < nodesInThisHop; ++nodeIndex )
            {
                double nodeAngle = 2 * M_PI * ( double )nodeIndex / ( double )nodesInThisHop;
                double x = cos( nodeAngle ) * hopRadius;
                double y = sin( nodeAngle ) * hopRadius;
                xList.push_back( x );
                yList.push_back( y );
                positionAlloc->Add( ns3::Vector( x, y, 0.0 ) );
            }
        }
    }
    
    
    mobilityHelper.SetPositionAllocator( positionAlloc );
    mobilityHelper.Install( allNodes );
    
    ns3::DsdvHelper dsdv;
    dsdv.Set( "PeriodicUpdateInterval", ns3::TimeValue( ns3::Seconds( updateRate ) ) );
    ns3::AodvHelper aodv;
    
    ns3::InternetStackHelper internetStack;
    internetStack.SetRoutingHelper( dsdv );
    internetStack.Install( allNodes );
    
    std::string phyMode( "DsssRate11Mbps" );
    ns3::Config::SetDefault( "ns3::WifiRemoteStationManager::RtsCtsThreshold", ns3::UintegerValue( 2200 ) );
    ns3::Config::SetDefault( "ns3::WifiRemoteStationManager::NonUnicastMode", ns3::StringValue( phyMode ) );
    ns3::YansWifiPhyHelper wifiPhyHelper = ns3::YansWifiPhyHelper::Default();
    wifiPhyHelper.Set( "RxGain", ns3::DoubleValue( 0 ) );
    
    ns3::YansWifiChannelHelper wifiChannelHelper;
    wifiChannelHelper.SetPropagationDelay( "ns3::ConstantSpeedPropagationDelayModel" );
    wifiChannelHelper.AddPropagationLoss( "ns3::RangePropagationLossModel","MaxRange", ns3::DoubleValue(radius*sqrt(2)) );
    
    wifiPhyHelper.SetChannel( wifiChannelHelper.Create() );
    
    ns3::WifiHelper wifiHelper;
    wifiHelper.SetStandard( ns3::WIFI_PHY_STANDARD_80211b );
    
    
    ns3::NqosWifiMacHelper wifiMacHelper = ns3::NqosWifiMacHelper::Default ();
    wifiHelper.SetRemoteStationManager( "ns3::ConstantRateWifiManager",
                                       "DataMode", ns3::StringValue( phyMode ),
                                       "ControlMode", ns3::StringValue( phyMode ) );
    
    wifiMacHelper.SetType( "ns3::AdhocWifiMac" );
    ns3::NetDeviceContainer wirelessDevices = wifiHelper.Install( wifiPhyHelper, wifiMacHelper, allNodes );
    
    ns3::Ipv4AddressHelper ipv4Helper;
    ipv4Helper.SetBase( "10.1.0.0", "255.255.0.0" );
    ns3::Ipv4InterfaceContainer ipInterfaces = ipv4Helper.Assign( wirelessDevices );
    
    ns3::Ipv4Address sinkAddress = ipInterfaces.GetAddress( 0 );
    
    SinkManagerHelper sinkManagerHelper;
    sinkManagerHelper.Install( sinkNode );
    
    TransmissionManagerHelper transmissionManagerHelper;
    transmissionManagerHelper.Install( sinkAddress, sensorNodeContainer, transmissionManagerName );
    
    std::cout << "Configuration complete..." << std::endl;
    
    UpdateUser( simSeconds );
    
    ns3::Simulator::Stop( ns3::Seconds( simSeconds ) );
    
    auto start = clock();
    ns3::Simulator::Run();
    std::cout << std::endl;
    StatisticsManager::GetStatisticsManager().PrintStatistics();
    std::cout << "Elapsed time: " << ( double )( clock() - start ) / ( double )CLOCKS_PER_SEC << std::endl;
    ns3::Simulator::Destroy();
    
    return ( 0 );
}

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

using namespace ns3;
using std::vector;

int
PropagaionLossmain (int argc, char *argv[])
{
    
    double hEnb = 39.3;
    double hUe = 1.0;
    
    int buildingX = 60;
    int buildingY = 90;
    int buildingZ = 20;
    int blockX = 78;
    int blockY = 104;
    int marginX = ( blockX - buildingX ) / 2;
    int marginY = ( blockY - buildingY ) / 2;
    
    for ( int xBlock = 0; xBlock < 10; ++xBlock )
    {
        for ( int yBlock = 0; yBlock < 10; ++yBlock )
        {
            Ptr<Building> building1 = CreateObject<Building>();
            building1->SetBoundaries( Box( blockX * xBlock + marginX, blockX * xBlock + marginX + buildingX, blockY * yBlock + marginY, blockY * yBlock + marginY + buildingY, 0.0, buildingZ ) );
            building1->SetBuildingType (Building::Residential);
            building1->SetExtWallsType (Building::ConcreteWithWindows);
        }
    }
    
    std::ofstream of;
    of.open( "pg.csv" );
    
    Ptr<ConstantPositionMobilityModel> mmEnb = CreateObject<ConstantPositionMobilityModel> ();
    mmEnb->SetPosition (Vector (390, 520, hEnb));
    
    Ptr<MobilityBuildingInfo> buildingInfoEnb = CreateObject<MobilityBuildingInfo> ();
    mmEnb->AggregateObject (buildingInfoEnb); // operation usually done by BuildingsHelper::Install
    BuildingsHelper::MakeConsistent (mmEnb);
    
    Ptr<HybridBuildingsPropagationLossModel> propagationLossModel = CreateObject<HybridBuildingsPropagationLossModel> ();
    propagationLossModel->SetAttribute ("Los2NlosThr", DoubleValue (1550.0));
    
    for (uint32_t i = 0; i < 780; i++)
    {
        for ( auto j = 0; j < 1040; ++j )
        {
            Ptr<ConstantPositionMobilityModel> mmUe = CreateObject<ConstantPositionMobilityModel> ();
            mmUe->SetPosition (Vector (i, j, hUe));
            Ptr<MobilityBuildingInfo> buildingInfoUe = CreateObject<MobilityBuildingInfo> ();
            mmUe->AggregateObject (buildingInfoUe); // operation usually done by BuildingsHelper::Install
            BuildingsHelper::MakeConsistent (mmUe);
            double loss = propagationLossModel->GetLoss (mmEnb, mmUe);
            of << loss << ", ";
        }
        of << std::endl;
    }
    
    of.close();
    Simulator::Destroy ();
    return ( 0 );
}
