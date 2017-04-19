//
//  GenerationConfigureHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "GenerationConfigureHelper.hpp"

Application::TGenerationPtr
GenerationConfigureHelper::Configure( std::ifstream & conf )
{
    char comma;
    TGenerationId generationId;
    if ( !( conf >> generationId >> comma ) )
    {
        class GenerationIdFailed{};
        throw GenerationIdFailed();
    }
    
    Application::TGenerationPtr generationProcess;
    if ( generationId == ConstantGenerationId )
    {
        ConstantGenerationProcess::TSamplingInterval samplingInterval;
        if ( !( conf >> samplingInterval >> comma ) )
        {
            class ConstantGenerationSamplingFailed{};
            throw ConstantGenerationSamplingFailed();
        }
        
        generationProcess = ns3::Create<ConstantGenerationProcess>( samplingInterval );
    }
    else if ( generationId == PoissonGenerationId )
    {
        PoissonGenerationProcess::TMeanRate meanRate;
        if ( !( conf >> meanRate >> comma ) )
        {
            class PoissonGenerationMeanRateFailed{};
            throw PoissonGenerationMeanRateFailed();
        }
        
        generationProcess = ns3::Create<PoissonGenerationProcess>( meanRate );
    }
    else if ( generationId == IntermittentGenerationId )
    {
        IntermittentGenerationProcess::TMeanRate slowRate, fastRate;
        IntermittentGenerationProcess::TArrivalTime minSlowTime, maxSlowTime, minFastTime, maxFastTime;
        if ( !( conf >> slowRate >> comma >> fastRate >> comma ) )
        {
            class IntermittentGenerationRateFailed{};
            throw IntermittentGenerationRateFailed();
        }
        if ( !( conf >> minSlowTime >> comma >> maxSlowTime >> comma >> minFastTime >> comma >> maxFastTime >> comma ) )
        {
            class IntermittentGenerationTimeFailed{};
            throw IntermittentGenerationTimeFailed();
        }
        
        generationProcess = ns3::Create<IntermittentGenerationProcess>( slowRate,
                                                                        fastRate,
                                                                        minSlowTime,
                                                                        maxSlowTime,
                                                                        minFastTime,
                                                                        maxFastTime );
    }
    
    return ( generationProcess );
}
