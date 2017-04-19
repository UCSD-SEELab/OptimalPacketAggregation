//
//  ADATransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 10/6/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "ADATransmissionManager.hpp"

#include "ApplicationConfigureHelper.hpp"

NS_LOG_COMPONENT_DEFINE("ADATransmissionManager");

NS_OBJECT_ENSURE_REGISTERED(ADATransmissionManager);

ns3::TypeId
ADATransmissionManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "ADATransmissionManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<ADATransmissionManager> ()
    ;
    
    return ( tid );
}

void
ADATransmissionManager::Start( void )
{
    GainFunction::TTransmissionTime x = ns3::Seconds( 0.1 * ((double)rand() / (double)RAND_MAX ) );
    ns3::Simulator::Schedule( this->m_checkTimer + x, &ADATransmissionManager::CheckWaitingTimer, this );
}

void
ADATransmissionManager::TransmitAllMeasurements( void )
{
    this->SendAllMeasurements();
    ns3::Simulator::Schedule( this->m_checkTimer, &ADATransmissionManager::CheckWaitingTimer, this );
}

void
ADATransmissionManager::ReadConfiguration( void )
{
    std::ifstream conf( "adaTM.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    char comma;
    if ( !( conf >> this->m_timeConstant >> comma ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    if ( !( conf >> this->m_checkTimer >> comma ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    if ( !( conf >> this->m_phi >> comma ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    if ( !( conf >> this->m_S ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    ApplicationConfigureHelper::Configure( this );
}

void
ADATransmissionManager::CheckWaitingTimer( void )
{
    auto totalNumber = this->GetTotalNumberOfMeasurements();
    GainFunction::TTransmissionTime fireTimer = this->m_timeConstant * ( 1 - totalNumber / ( this->m_S * this->m_phi ) );
    if ( this->m_checkTimer > fireTimer )
    {
        if ( totalNumber > 0 )
        {
            this->TransmitAllMeasurements();
        }
        else
        {
            ns3::Simulator::Schedule( this->m_checkTimer, &ADATransmissionManager::CheckWaitingTimer, this );
        }
    }
    else
    {
        ns3::Simulator::Schedule( this->m_checkTimer, &ADATransmissionManager::CheckWaitingTimer, this );
    }
}
