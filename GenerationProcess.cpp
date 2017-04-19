//
//  GenerationProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "GenerationProcess.hpp"
#include "StatisticsManager.hpp"

GenerationProcess::GenerationProcess( const TMeanRate meanRate, const TMeasurementQueuePtr list ) : m_meanRate( meanRate ),
                                                                                                    m_measurementList( list ),
                                                                                                    m_id( Measurement::InvalidId )
{
}

GenerationProcess::GenerationProcess( const TMeanRate meanRate ) : m_meanRate( meanRate ),
                                                                   m_id( Measurement::InvalidId )
{
}

void
GenerationProcess::AddMeasurement( const TMeasurementPtr & measurement )
{
    this->m_measurementList->Add( measurement );
    
    StatisticsManager::GetStatisticsManager().MeasurementGenerated( measurement );
}