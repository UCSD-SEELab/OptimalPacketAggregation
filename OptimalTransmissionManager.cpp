//
//  OptimalTransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/10/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "OptimalTransmissionManager.hpp"
#include "ApplicationConfigureHelper.hpp"

NS_LOG_COMPONENT_DEFINE("OptimalTransmissionManager");

NS_OBJECT_ENSURE_REGISTERED(OptimalTransmissionManager);

ns3::TypeId
OptimalTransmissionManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "OptimalTransmissionManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<OptimalTransmissionManager> ()
    ;
    
    return ( tid );
}

OptimalTransmissionManager::OptimalTransmissionManager( void ) : m_searchCount( 20 ),
                                                                 m_searchStart( ns3::Seconds( 0.1 ) ),
                                                                 m_searchStop( ns3::Seconds( 20 ) )
{
}


OptimalTransmissionManager::TGain
OptimalTransmissionManager::GetTotalGain( const GainFunction::TTransmissionTime & x ) const
{
    TGain totalGain = 0;
    TGain totalGainDerivative = 0;

    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        totalGain += ( *i )->GetMeasurementGain( x );
        totalGainDerivative += ( *i )->GetMeasurementGainDerivative( x );
        
        //std::cout << "Gains: " << ( *i )->GetMeasurementGain( x ) << ", " << ( *i )->GetMeasurementGainDerivative( x ) << std::endl;
    }
    
    // std::cout << "Total Gains: " << totalGain << ", " << totalGainDerivative << std::endl;
    
    TGain totalDerivative = totalGain * this->m_messageGainFunction->GetGainDerivative( x ) +
                            totalGainDerivative * this->m_messageGainFunction->GetGain( x );
    
    // std::cout << "Resulting expression: " << totalDerivative << std::endl;

    
    return ( totalDerivative );
}

GainFunction::TTransmissionTime
OptimalTransmissionManager::GetOptimalTime( void ) const
{
    GainFunction::TTransmissionTime xMin = this->m_searchStart;
    GainFunction::TTransmissionTime xMax = this->m_searchStop;
    GainFunction::TTransmissionTime xTrial = ( xMin + xMax ) / 2;
    
    double yMin = this->GetTotalGain( xMin );
    double yMax = this->GetTotalGain( xMax );
    double yTrial = this->GetTotalGain( xTrial );
    
    if ( yMin == 0 )
    {
        return ( xMin );
    }
    else if ( yMax == 0 )
    {
        return ( xMax );
    }
    else if ( yMin * yMax > 0 )
    {
        if ( yMin <= yMax )
        {
            return ( xMin );
        }
        else
        {
            return ( xMax );
        }
    }
    
    for ( TCount count = 0; count < this->m_searchCount; ++count )
    {
        if ( yTrial == 0 )
        {
            break;
        }
        if ( yTrial * yMin < 0 )
        {
            xMax = xTrial;
        }
        else
        {
            xMin = xTrial;
            yMin = this->GetTotalGain( xMin );
        }
        
        xTrial = ( xMin + xMax ) / 2;
        yTrial = this->GetTotalGain( xTrial );
    }
    // std::cout << xTrial << std::endl;
    return ( xTrial );
}

void
OptimalTransmissionManager::Start( void )
{
    GainFunction::TTransmissionTime x = this->GetOptimalTime() + ns3::Seconds( 0.1 * ((double)rand() / (double)RAND_MAX ) );
    //GainFunction::TTransmissionTime x = this->GetOptimalTime();
    ns3::Simulator::Schedule( x, &OptimalTransmissionManager::TransmitAllMeasurements, this );
}

void
OptimalTransmissionManager::TransmitAllMeasurements( void )
{
    this->SendAllMeasurements();
    GainFunction::TTransmissionTime x = this->GetOptimalTime();
    if ( x== 0 )
    {
        throw "No gain function";
    }
    ns3::Simulator::Schedule( x, &OptimalTransmissionManager::TransmitAllMeasurements, this );
}

void
OptimalTransmissionManager::ReadConfiguration( void )
{
    std::ifstream conf( "optimalTM.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
   
    char comma;
    if ( !( conf >> this->m_searchCount >> comma >> this->m_searchStart >> comma >> this->m_searchStop ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    ApplicationConfigureHelper::Configure( this );
}