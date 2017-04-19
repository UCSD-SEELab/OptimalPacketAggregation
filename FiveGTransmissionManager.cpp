//
//  FiveGTransmissionManager.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "FiveGTransmissionManager.hpp"

#include "ApplicationConfigureHelper.hpp"

NS_LOG_COMPONENT_DEFINE("FiveGTransmissionManager");

NS_OBJECT_ENSURE_REGISTERED(FiveGTransmissionManager);

ns3::TypeId
FiveGTransmissionManager::GetTypeId( void )
{
    static ns3::TypeId tid = ns3::TypeId( "FiveGTransmissionManager" )
    .SetParent<ns3::Object> ()
    .AddConstructor<FiveGTransmissionManager> ()
    ;
    
    return ( tid );
}

FiveGTransmissionManager::FiveGTransmissionManager( void ) : m_searchCount( 20 ),
                                                             m_searchStart( ns3::Seconds( 0.1 ) ),
                                                             m_searchStop( ns3::Seconds( 20 ) ),
                                                             m_usedCValue( -1.0 )
{
}

FiveGTransmissionManager::TGain
FiveGTransmissionManager::GetTotalGain( const GainFunction::TTransmissionTime & x ) const
{
    TGain totalGain = 0;
    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        totalGain += ( *i )->GetMeasurementGain( x );
    }
    
    return ( totalGain );
}

FiveGTransmissionManager::TGain
FiveGTransmissionManager::GetTotalGainDerivative( const GainFunction::TTransmissionTime & x ) const
{
    TGain totalGainDerivative = 0;
    for ( auto i = this->m_applications.begin(); i != this->m_applications.end(); ++i )
    {
        totalGainDerivative += ( *i )->GetMeasurementGainDerivative( x );
    }
    
    return ( totalGainDerivative * this->m_messageGainFunction->GetGain( x ) / this->m_messageGainFunction->GetGainDerivative( x )  );
}

GainFunction::TTransmissionTime
FiveGTransmissionManager::GetOptimalTime( void )
{
    if ( this->m_usedCValue != *( this->m_cValue ) )
    {
        this->m_usedCValue = *( this->m_cValue );
        this->m_currentOptimalTime = this->SolveForCValue( *this->m_cValue );
    }
    else
    {
        GainFunction::TTransmissionTime updatedTime = this->SolveForCValue( *this->m_cValue );
        
        if ( std::abs( updatedTime.GetSeconds() - this->m_currentOptimalTime.GetSeconds() ) > this->m_updateThreshold.GetSeconds() )
        {
            BaseStation::TResponseVector myResponses, deltaResponses;
            auto numberOfCValues = BaseStation::GetBaseStation().cVector.size();
            for ( auto cIndex = 0; cIndex < numberOfCValues; ++cIndex )
            {
                myResponses.push_back( this->ProcessCValue( BaseStation::GetBaseStation().cVector[cIndex] ) );
                deltaResponses.push_back( myResponses[cIndex] - this->m_myResponses[cIndex] );
            }
            
            BaseStation::GetBaseStation().UpdateResponses( deltaResponses );
            this->m_myResponses = myResponses;
        }
    }
    return ( this->m_currentOptimalTime );
}

void
FiveGTransmissionManager::Start( void )
{
    this->ConnectToBaseStation();
    GainFunction::TTransmissionTime x = this->GetOptimalTime() + ns3::Seconds( 0.1 * ((double)rand() / (double)RAND_MAX ) );
    ns3::Simulator::Schedule( x, &FiveGTransmissionManager::TransmitAllMeasurements, this );
}

void
FiveGTransmissionManager::TransmitAllMeasurements( void )
{
    this->SendAllMeasurements();
    GainFunction::TTransmissionTime x = this->GetOptimalTime();
    if ( x == 0 )
    {
        class ZeroTransmissionTime{};
        throw ZeroTransmissionTime();
    }
    ns3::Simulator::Schedule( x, &FiveGTransmissionManager::TransmitAllMeasurements, this );
}

void
FiveGTransmissionManager::ReadConfiguration( void )
{
    std::ifstream conf( "5GTM.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    char comma;
    if ( !( conf >> this->m_searchCount >> comma >> this->m_searchStart >> comma >> this->m_searchStop >> comma >> this->m_updateThreshold >> comma ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    
    this->m_messageGainFunction =  GainConfigureHelper::Configure( conf );
    ApplicationConfigureHelper::Configure( this );
}

FiveGTransmissionManager::TGain
FiveGTransmissionManager::ProcessCValue( const TGain cValue ) const
{
    return ( this->GetTotalGain( this->SolveForCValue( cValue ) ) );
}

GainFunction::TTransmissionTime
FiveGTransmissionManager::SolveForCValue( const TGain cValue ) const
{
    GainFunction::TTransmissionTime xMin = this->m_searchStart;
    GainFunction::TTransmissionTime xMax = this->m_searchStop;
    GainFunction::TTransmissionTime xTrial = ( xMin + xMax ) / 2;
    
    double yMin = this->GetTotalGainDerivative( xMin ) + cValue;
    double yMax = this->GetTotalGainDerivative( xMax ) + cValue;
    double yTrial = this->GetTotalGainDerivative( xTrial ) + cValue;
    
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
            yMin = this->GetTotalGainDerivative( xMin ) + cValue;
        }
        
        xTrial = ( xMin + xMax ) / 2;
        yTrial = this->GetTotalGainDerivative( xTrial ) + cValue;
    }
    return ( xTrial );
}

void
FiveGTransmissionManager::ConnectToBaseStation( void )
{
    BaseStation::TResponseVector myResponses;
    auto numberOfCValues = BaseStation::GetBaseStation().cVector.size();
    for ( auto cIndex = 0; cIndex < numberOfCValues; ++cIndex )
    {
        myResponses.push_back( this->ProcessCValue( BaseStation::GetBaseStation().cVector[cIndex] ) );
    }
    
    this->m_myResponses = myResponses;
    this->m_cValue = &( BaseStation::GetBaseStation().RegisterMe( myResponses ) );
    //std::cout << "Optimal C Value: " << *this->m_cValue << std::endl;
}
