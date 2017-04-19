//
//  CascadingTransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/27/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "CascadingTransmissionManager.hpp"

#include "ApplicationConfigureHelper.hpp"

NS_LOG_COMPONENT_DEFINE("CascadingTransmissionManager");

NS_OBJECT_ENSURE_REGISTERED(CascadingTransmissionManager);

ns3::TypeId
CascadingTransmissionManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "CascadingTransmissionManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<CascadingTransmissionManager> ()
    ;
    
    return ( tid );
}

unsigned int hopNumber = 1;

void
CascadingTransmissionManager::Start( void )
{
    this->m_hopNumber = hopNumber;
    ++hopNumber;
    this->m_fixedTime = 2 * ( this->m_fixedTime - this->m_hopNumber * ns3::Seconds( 0.03 ) );
    GainFunction::TTransmissionTime x = ns3::Seconds( 0.1 * ((double)rand() / (double)RAND_MAX ) );
    ns3::Simulator::Schedule( this->m_fixedTime + x, &CascadingTransmissionManager::TransmitAllMeasurements, this );
}

void
CascadingTransmissionManager::TransmitAllMeasurements( void )
{
    this->SendAllMeasurements();
    ns3::Simulator::Schedule( this->m_fixedTime, &CascadingTransmissionManager::TransmitAllMeasurements, this );
}

void
CascadingTransmissionManager::ReadConfiguration( void )
{
    std::ifstream conf( "cascTM.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    if ( !( conf >> this->m_fixedTime ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    ApplicationConfigureHelper::Configure( this );
}