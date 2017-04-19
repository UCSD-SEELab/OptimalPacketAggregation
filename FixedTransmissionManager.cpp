//
//  FixedTransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/13/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "FixedTransmissionManager.hpp"

#include "ApplicationConfigureHelper.hpp"

NS_LOG_COMPONENT_DEFINE("FixedTransmissionManager");

NS_OBJECT_ENSURE_REGISTERED(FixedTransmissionManager);

ns3::TypeId
FixedTransmissionManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "FixedTransmissionManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<FixedTransmissionManager> ()
    ;
    
    return ( tid );
}

void
FixedTransmissionManager::Start( void )
{
    GainFunction::TTransmissionTime x = ns3::Seconds( 0.1 * ((double)rand() / (double)RAND_MAX ) );
    ns3::Simulator::Schedule( this->m_fixedTime + x, &FixedTransmissionManager::TransmitAllMeasurements, this );
}

void
FixedTransmissionManager::TransmitAllMeasurements( void )
{
    this->SendAllMeasurements();
    ns3::Simulator::Schedule( this->m_fixedTime, &FixedTransmissionManager::TransmitAllMeasurements, this );
}

void
FixedTransmissionManager::ReadConfiguration( void )
{
    std::ifstream conf( "fixedTM.txt" );
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
