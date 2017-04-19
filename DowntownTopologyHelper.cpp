//
//  DowntownTopologyHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 9/25/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "DowntownTopologyHelper.hpp"

void
DowntownTopologyHelper::CreateBuildings( void )
{
    for ( TNumberOfBlocks xBlock = 0; xBlock < this->m_xNumber; ++xBlock )
    {
        for ( TNumberOfBlocks yBlock = 0; yBlock < this->m_yNumber; ++yBlock )
        {
            ns3::Ptr<ns3::Building> building = ns3::CreateObject<ns3::Building>();
            building->SetBoundaries( ns3::Box( this->m_blockX * xBlock + this->m_marginX,
                                               this->m_blockX * xBlock + this->m_marginX + this->m_buildingX,
                                               this->m_blockY * yBlock + this->m_marginY,
                                               this->m_blockY * yBlock + this->m_marginY + this->m_buildingY,
                                               0.0,
                                               this->m_buildingZ ) );
            
            building->SetBuildingType( ns3::Building::Residential );
            building->SetExtWallsType( ns3::Building::ConcreteWithWindows );
        }
    }
}

void
DowntownTopologyHelper::AllocatePositions( void )
{
    TCoordinate sinkX = ( this->m_xNumber * this->m_blockX ) / 2;
    TCoordinate sinkY = ( this->m_yNumber * this->m_blockY ) / 2;
    
    std::cout << "(" << sinkX << "," << sinkY << ")" << std::endl;
    
    ns3::MobilityHelper sinkMobilityHelper;
    ns3::Ptr<ns3::ListPositionAllocator> sinkPosition = ns3::CreateObject<ns3::ListPositionAllocator>();
    sinkPosition->Add( ns3::Vector( sinkX, sinkY, this->m_sinkHeight ) );
    sinkMobilityHelper.SetPositionAllocator( sinkPosition );
    sinkMobilityHelper.Install( this->m_sinkNode );
    
    ns3::Ptr<ns3::MobilityBuildingInfo> buildingInfoSink = ns3::CreateObject<ns3::MobilityBuildingInfo>();
    ns3::BuildingsHelper::Install( this->m_sinkNode );
    
    ns3::MobilityHelper sensorsMobilityHelper;
    
    ns3::Ptr<ns3::RandomBoxPositionAllocator> sensorsPosition = ns3::CreateObject<ns3::RandomBoxPositionAllocator>();
    ns3::Ptr<ns3::UniformRandomVariable> xAllocator = ns3::CreateObject<ns3::UniformRandomVariable>();
    xAllocator->SetAttribute( "Min", ns3::DoubleValue( 0 ) );
    xAllocator->SetAttribute( "Max", ns3::DoubleValue( this->m_xNumber * this->m_blockX ) );
    
    ns3::Ptr<ns3::UniformRandomVariable> yAllocator = ns3::CreateObject<ns3::UniformRandomVariable>();
    yAllocator->SetAttribute( "Min", ns3::DoubleValue( 0 ) );
    yAllocator->SetAttribute( "Max", ns3::DoubleValue( this->m_yNumber * this->m_blockY ) );
    
    ns3::Ptr<ns3::UniformRandomVariable> zAllocator = ns3::CreateObject<ns3::UniformRandomVariable>();
    zAllocator->SetAttribute( "Min", ns3::DoubleValue( this->m_sensorHeight ) );
    zAllocator->SetAttribute( "Max", ns3::DoubleValue( this->m_buildingZ - this->m_sensorHeight ) );

    sensorsPosition->SetX( xAllocator );
    sensorsPosition->SetY( yAllocator );
    sensorsPosition->SetZ( zAllocator );
    sensorsMobilityHelper.SetPositionAllocator( sensorsPosition );
    
    ns3::RectangleValue mobilityBox;
    mobilityBox.Set( ns3::Rectangle( 0, this->m_xNumber * this->m_blockX, 0, this->m_yNumber * this->m_blockY ) );
    sensorsMobilityHelper.SetMobilityModel( "ns3::RandomWalk2dMobilityModel",
                                            "Distance", ns3::DoubleValue( 300 ),
                                            "Bounds", mobilityBox );
    
    sensorsMobilityHelper.Install( this->m_sensorNodesContainer );
    
    ns3::Ptr<ns3::MobilityBuildingInfo> buildingInfoSensors = ns3::CreateObject<ns3::MobilityBuildingInfo>();
    ns3::BuildingsHelper::Install( this->m_sensorNodesContainer );
    ns3::BuildingsHelper::MakeMobilityModelConsistent();
}

void
DowntownTopologyHelper::Configure( const TNodePtr sinkNode, ns3::NodeContainer & sensorNodesContainer )
{
    this->m_sinkNode = sinkNode;
    this->m_sensorNodesContainer = sensorNodesContainer;
    
    this->ReadConfiguration();
    
    this->CreateBuildings();
    this->AllocatePositions();
}

void
DowntownTopologyHelper::ReadConfiguration( void )
{
    std::ifstream conf( "downtownConf.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    char comma;
    if ( !( conf >> this->m_buildingX >> comma ) )
    {
        class BuildingXFailed{};
        throw BuildingXFailed();
    }
    if ( !( conf >> this->m_buildingY >> comma ) )
    {
        class BuildingYFailed{};
        throw BuildingYFailed();
    }
    if ( !( conf >> this->m_buildingZ >> comma ) )
    {
        class BuildingZFailed{};
        throw BuildingZFailed();
    }
    if ( !( conf >> this->m_blockX >> comma ) )
    {
        class BlockXFailed{};
        throw BlockXFailed();
    }
    if ( !( conf >> this->m_blockY >> comma ) )
    {
        class BlockYFailed{};
        throw BlockYFailed();
    }
    
    this->m_marginX = ( TCoordinate )( ( this->m_blockX - this->m_buildingX ) / 2 );
    this->m_marginY = ( TCoordinate )( ( this->m_blockY - this->m_buildingY ) / 2 );
    
    if ( !( conf >> this->m_sinkHeight >> comma ) )
    {
        class SinkHeightFailed{};
        throw SinkHeightFailed();
    }
    
    if ( !( conf >> this->m_sensorHeight >> comma ) )
    {
        class SensorHeightFailed{};
        throw SensorHeightFailed();
    }
    
    if ( !( conf >> this->m_xNumber >> comma ) )
    {
        class XNumberFailed{};
        throw XNumberFailed();
    }
    
    if ( !( conf >> this->m_yNumber ) )
    {
        class YNumberFailed{};
        throw YNumberFailed();
    }
}
