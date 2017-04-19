//
//  BaseStation.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "BaseStation.hpp"
#include "FiveGTransmissionManager.hpp"

BaseStation::BaseStation( void ) : m_CValueMinimum( 0 ),
                                   m_CValueMaximum( 100 ),
                                   m_CValueResolution( 0.1 ),
                                   m_numberOfNodes( 0 ),
                                   m_alpha( 0 ),
                                   m_useDynamicAlpha( true )
{
    this->ReadConfiguration();
    for ( TCValue cValue = this->m_CValueMinimum; cValue <= this->m_CValueMaximum; cValue += this->m_CValueResolution )
    {
        this->cVector.push_back( cValue );
        this->m_responseVector.push_back( 0 );
    }
}

void
BaseStation::ReadConfiguration( void )
{
    std::ifstream conf( "baseStation.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    char comma;
    if ( !( conf >> this->m_CValueResolution >> comma >> this->m_CValueMinimum >> comma >> this->m_CValueMaximum >> comma >> this->m_alpha >> comma >> this->m_updateEnabled ) )
    {
        class ConfigurationFailed{};
        throw ConfigurationFailed();
    }
    if ( this->m_alpha == 0 )
    {
        this->m_useDynamicAlpha = true;
    }
    else
    {
        this->m_useDynamicAlpha = false;
    }
}

BaseStation &
BaseStation::GetBaseStation( void )
{
    static BaseStation baseStation;
    return ( baseStation );
}

BaseStation::TResponse
BaseStation::GetError( const TResponseVector::size_type index ) const
{
    return ( std::abs( ( this->m_alpha * this->m_responseVector[index] / ( TCValue )this->m_numberOfNodes ) - this->cVector[index] ) );
}

BaseStation::TCValue &
BaseStation::RegisterMe( const TResponseVector & responses )
{
    ++this->m_numberOfNodes;
    
    if ( this->m_useDynamicAlpha )
    {
        this->m_alpha = ( ( TResponse )this->m_numberOfNodes )/ 100.0;
    }

    TResponseVector::size_type minimumIndex = 0;
    this->m_responseVector[0] += responses[0];
    TResponse minimumError = this->GetError( 0 );
    
    TResponseVector::size_type numberOfResponses = responses.size();
    for ( auto index = 1; index < numberOfResponses; ++index )
    {
        this->m_responseVector[index] += responses[index];
        TResponse currentError = this->GetError( index );
        if ( minimumError > currentError )
        {
            minimumError = currentError;
            minimumIndex = index;
        }
        
    }
    
    this->m_optimalCValue = this->cVector[minimumIndex];
    
    return ( this->m_optimalCValue );
}

void
BaseStation::UpdateResponses( const TResponseVector & deltaResponses )
{
    ++this->m_numberOfUpdates;
    if ( !this->m_updateEnabled )
    {
        return;
    }
    if ( this->m_useDynamicAlpha )
    {
        this->m_alpha = ( ( TResponse )this->m_numberOfNodes )/ 100.0;
    }
    
    TResponseVector::size_type minimumIndex = 0;
    this->m_responseVector[0] += deltaResponses[0];
    TResponse minimumError = this->GetError( 0 );
    
    TResponseVector::size_type numberOfResponses = deltaResponses.size();
    for ( auto index = 1; index < numberOfResponses; ++index )
    {
        this->m_responseVector[index] += deltaResponses[index];
        TResponse currentError = this->GetError( index );
        if ( minimumError > currentError )
        {
            minimumError = currentError;
            minimumIndex = index;
        }
        
    }
    
    if ( this->m_optimalCValue != this->cVector[minimumIndex] )
    {
        ++this->m_numberOfBroadcasts;
        this->m_optimalCValue = this->cVector[minimumIndex];
    }
    
}
