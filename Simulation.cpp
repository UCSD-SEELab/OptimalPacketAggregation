//
//  Simulation.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 9/25/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "Simulation.hpp"

void
Simulation::ParseCommandLine( int argc, char * argv[] )
{
    ns3::CommandLine cmd;
    
    TNumberOfNodes numberOfNodes                = this->m_numberOfNodes;
    TSimulationTime simSeconds                  = this->m_simSeconds;
    TTransmissionManagerName transmissionManagerName = this->m_transmissionManagerName;
    TNumberOfHops numberOfHops                  = this->m_numberOfHops;
    TCommunicationRadius communicationRadius    = this->m_communicationRadius;
    TSimulationTime routingUpdateRate           = this->m_routingUpdateRate;
    TTopologyType topologyType                  = this->m_topologyType;
    TRXGain rxGain                              = this->m_rxGain;
    std::string logFileName                     = this->m_logFileName;
    bool timeSeries                             = false;
    
    cmd.AddValue( "numNodes", "Number of Nodes, including sink", numberOfNodes );
    cmd.AddValue( "tmName", "Transmission Manager Name", transmissionManagerName );
    cmd.AddValue( "simSec", "Simulation Length in Seconds", simSeconds );
    cmd.AddValue( "numHops", "Number of Hops, (N-1) divisible by H(H+1)/2", numberOfHops );
    cmd.AddValue( "radius", "Radius from sink node", communicationRadius );
    cmd.AddValue( "updateRate", "Routing Update Rate", routingUpdateRate );
    cmd.AddValue( "topType", "Topology Type", topologyType );
    cmd.AddValue( "rxGain", "Reception Gain", rxGain );
    cmd.AddValue( "logName", "Log File Name", logFileName );
    cmd.AddValue( "timeSeries", "Write the Timeseries", timeSeries );
    
    cmd.Parse( argc, argv );
    
    this->m_numberOfNodes           = numberOfNodes;
    this->m_simSeconds              = simSeconds;
    this->m_transmissionManagerName = transmissionManagerName;
    this->m_numberOfHops            = numberOfHops;
    this->m_communicationRadius     = communicationRadius;
    this->m_routingUpdateRate       = routingUpdateRate;
    this->m_rxGain                  = rxGain;
    this->m_topologyType            = topologyType;
    
    std::cout << "Topology " << topologyType << " ";
    this->m_logFileName             = logFileName;
    
    StatisticsManager::GetStatisticsManager().SetLogFileName( this->m_logFileName );
    StatisticsManager::GetStatisticsManager().SetTimeseriesPreference( timeSeries );
}

void
Simulation::CreateNodes( void )
{
    std::ofstream log( this->m_logFileName, std::ios::app );
    log << this->m_transmissionManagerName << ","
        << this->m_numberOfNodes << ","
        << this->m_simSeconds << std::endl;
    log.close();
    
    std::cout << this->m_transmissionManagerName << " - Number of Nodes: "
              << this->m_numberOfNodes << ", Hops: "
              << this->m_numberOfHops << std::endl;
    
    this->m_sinkNodeContainer.Create( 1 );
    this->m_sinkNode = this->m_sinkNodeContainer.Get ( 0 );
    this->m_sensorNodesContainer.Create( this->m_numberOfNodes - 1 );

    this->m_allNodesContainer.Add( this->m_sinkNodeContainer );
    this->m_allNodesContainer.Add( this->m_sensorNodesContainer );
}

void
Simulation::CreateLinearTopology( void )
{
    ns3::MobilityHelper mobilityHelper;
    ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<ns3::ListPositionAllocator>();
    
    /* Sink at the center */
    positionAlloc->Add( ns3::Vector( 0, 0, 0 ) );
    
    std::vector<TCoordinate> xList;
    std::vector<TCoordinate> yList;
    
    for ( TNumberOfHops hopIndex = 1; hopIndex <= this->m_numberOfHops; ++hopIndex )
    {
        TAngle nodeAngle = 0;
        TCommunicationRadius hopRadius = this->m_communicationRadius * ( TCommunicationRadius )hopIndex;
        TCoordinate x = cos( nodeAngle ) * hopRadius;
        TCoordinate y = sin( nodeAngle ) * hopRadius;
        xList.push_back( x );
        yList.push_back( y );
        positionAlloc->Add( ns3::Vector( x, y, 0.0 ) );
    }
    
    mobilityHelper.SetPositionAllocator( positionAlloc );
    mobilityHelper.Install( this->m_allNodesContainer );
}

void
Simulation::CreateRadialTopology( void )
{
    ns3::MobilityHelper mobilityHelper;
    ns3::Ptr<ns3::ListPositionAllocator> positionAlloc = ns3::CreateObject<ns3::ListPositionAllocator>();
    
    /* Sink at the center */
    positionAlloc->Add( ns3::Vector( 0, 0, 0 ) );
    
    std::vector<TCoordinate> xList;
    std::vector<TCoordinate> yList;

    TNumberOfNodes nodePerHop = std::ceil( 2.0 * ( double )( this->m_numberOfNodes - 1 ) / ( double )( this->m_numberOfHops * ( this->m_numberOfHops + 1 ) ) );
    std::cout << "Nodes per hop: " << nodePerHop << std::endl;
    for ( TNumberOfHops hopIndex = 1; hopIndex <= this->m_numberOfHops; ++hopIndex )
    {
        TCommunicationRadius hopRadius = this->m_communicationRadius * ( TCommunicationRadius )hopIndex;
        TNumberOfNodes nodesInThisHop = nodePerHop * hopIndex;
        for ( TNumberOfNodes nodeIndex = 0; nodeIndex < nodesInThisHop; ++nodeIndex )
        {
            TAngle nodeAngle = 2 * M_PI * ( double )nodeIndex / ( double )nodesInThisHop;
            TCoordinate x = cos( nodeAngle ) * hopRadius;
            TCoordinate y = sin( nodeAngle ) * hopRadius;
            xList.push_back( x );
            yList.push_back( y );
            positionAlloc->Add( ns3::Vector( x, y, 0.0 ) );
        }
    }
    
    mobilityHelper.SetPositionAllocator( positionAlloc );
    mobilityHelper.Install( this->m_allNodesContainer );
}

void
Simulation::CreateDowntownTopology( void )
{
    DowntownTopologyHelper downtownHelper;
    downtownHelper.Configure( this->m_sinkNode, this->m_sensorNodesContainer );
}

void
Simulation::CreateTopology( void )
{
    if ( this->m_topologyType == LinearTopology )
    {
        this->CreateLinearTopology();
    }
    else if ( this->m_topologyType == RadialTopology )
    {
        this->CreateRadialTopology();
    }
    else if ( this->m_topologyType == DowntownTopology )
    {
        this->CreateDowntownTopology();
    }
}

void
Simulation::InstallDSDV( void )
{
    ns3::DsdvHelper dsdv;
    dsdv.Set( "PeriodicUpdateInterval",
              ns3::TimeValue( ns3::Seconds( this->m_routingUpdateRate ) ) );
    
    ns3::InternetStackHelper internetStack;
    internetStack.SetRoutingHelper( dsdv );
    internetStack.Install( this->m_allNodesContainer );
}

void
Simulation::InstallAODV( void )
{
    ns3::AodvHelper aodv;    
    ns3::InternetStackHelper internetStack;
    internetStack.SetRoutingHelper( aodv );
    internetStack.Install( this->m_allNodesContainer );
}

void
Simulation::InstallWiFi( void )
{
    std::string phyMode( "DsssRate11Mbps" );
    ns3::Config::SetDefault( "ns3::WifiRemoteStationManager::RtsCtsThreshold", ns3::UintegerValue( 2200 ) );
    ns3::Config::SetDefault( "ns3::WifiRemoteStationManager::NonUnicastMode", ns3::StringValue( phyMode ) );
    ns3::YansWifiPhyHelper wifiPhyHelper = ns3::YansWifiPhyHelper::Default();
    wifiPhyHelper.Set( "RxGain", ns3::DoubleValue( this->m_rxGain ) );
    
    ns3::YansWifiChannelHelper wifiChannelHelper;
    wifiChannelHelper.SetPropagationDelay( "ns3::ConstantSpeedPropagationDelayModel" );
    
    if ( this->m_topologyType == this->DowntownTopology )
    {
        wifiChannelHelper.AddPropagationLoss( "ns3::HybridBuildingsPropagationLossModel", "Los2NlosThr", ns3::DoubleValue( 1550.0 ) );
    }
    else
    {
        wifiChannelHelper.AddPropagationLoss( "ns3::RangePropagationLossModel",
                                              "MaxRange",
                                              ns3::DoubleValue( this->m_communicationRadius * sqrt( 2 ) ) );
        
        wifiChannelHelper.AddPropagationLoss( "ns3::FriisPropagationLossModel" );
    }
    
    wifiPhyHelper.SetChannel( wifiChannelHelper.Create() );
    
    ns3::WifiHelper wifiHelper;
    wifiHelper.SetStandard( ns3::WIFI_PHY_STANDARD_80211b );
    
    ns3::NqosWifiMacHelper wifiMacHelper = ns3::NqosWifiMacHelper::Default ();
    wifiHelper.SetRemoteStationManager( "ns3::ConstantRateWifiManager",
                                        "DataMode", ns3::StringValue( phyMode ),
                                        "ControlMode", ns3::StringValue( phyMode ) );
    
    wifiMacHelper.SetType( "ns3::AdhocWifiMac" );
    this->m_allWirelessDevices = wifiHelper.Install( wifiPhyHelper, wifiMacHelper, this->m_allNodesContainer );
}

void
Simulation::InstallIPAddresses( void )
{
    ns3::Ipv4AddressHelper ipv4Helper;
    ipv4Helper.SetBase( "10.1.0.0", "255.255.0.0" );
    ns3::Ipv4InterfaceContainer ipInterfaces = ipv4Helper.Assign( this->m_allWirelessDevices );
    
    this->m_sinkIPAddress = ipInterfaces.GetAddress( 0 );
}

void
Simulation::ConfigureNodes( void )
{
    SinkManagerHelper sinkManagerHelper;
    sinkManagerHelper.Install( this->m_sinkNode );
    
    TransmissionManagerHelper transmissionManagerHelper;
    transmissionManagerHelper.Install( this->m_sinkIPAddress,
                                       this->m_sensorNodesContainer,
                                       this->m_transmissionManagerName );
    
    std::cout << "Configuration complete..." << std::endl;
}

void
Simulation::StartSimulation( void )
{
    this->SimulationProgress();
    
    ns3::Simulator::Stop( ns3::Seconds( this->m_simSeconds ) );
    
    auto start = clock();
    ns3::Simulator::Run();
    std::cout << std::endl;
    StatisticsManager::GetStatisticsManager().PrintStatistics();
    std::cout << "Elapsed time: " << ( double )( clock() - start ) / ( double )CLOCKS_PER_SEC << std::endl;
    ns3::Simulator::Destroy();
}

void
Simulation::SimulationProgress( void )
{
    std::cout << 100.0 * ( ns3::Now().GetSeconds() / this->m_simSeconds ) << "%||";
    std::cout.flush();
    ns3::Simulator::Schedule( ns3::Seconds( this->m_simSeconds / 10.0 ) , &Simulation::SimulationProgress, this );
}

void
Simulation::Configure( int argc, char * argv[] )
{
    this->ParseCommandLine( argc, argv );
    this->CreateNodes();
    this->CreateTopology();
    this->InstallDSDV();
    this->InstallWiFi();
    this->InstallIPAddresses();
    this->ConfigureNodes();
}

void
Simulation::Run( void )
{
    this->StartSimulation();
}
