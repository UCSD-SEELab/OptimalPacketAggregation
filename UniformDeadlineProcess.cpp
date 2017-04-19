//
//  UniformDeadlineProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "UniformDeadlineProcess.hpp"

UniformDeadlineProcess::UniformDeadlineProcess( const TDeadline lowerBound,
                                                const TDeadline upperBound ) : DeadlineProcess( ( upperBound + lowerBound ) / 2 )
{
    this->m_lowerBound = lowerBound.GetSeconds();
    this->m_upperBound = upperBound.GetSeconds();
    this->m_uniformGenerator = ns3::CreateObject<ns3::UniformRandomVariable> ();
    this->m_uniformGenerator->SetAttribute ("Min", ns3::DoubleValue ( this->m_lowerBound ) );
    this->m_uniformGenerator->SetAttribute ("Max", ns3::DoubleValue ( this->m_upperBound ) );

}

UniformDeadlineProcess::TDeadline
UniformDeadlineProcess::GetNextDeadline( void ) const
{
    return ( ns3::Seconds( this->m_uniformGenerator->GetValue() ) );
}