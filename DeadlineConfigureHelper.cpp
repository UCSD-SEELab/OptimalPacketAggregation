//
//  DeadlineConfigureHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "DeadlineConfigureHelper.hpp"

Application::TDeadlinePtr
DeadlineConfigureHelper::Configure( std::ifstream & conf )
{
    char comma;
    TDeadlineId deadlineId;
    if ( !( conf >> deadlineId >> comma ) )
    {
        class DeadlineIdFailed{};
        throw DeadlineIdFailed();
    }
    
    Application::TDeadlinePtr deadlineProcess;
    if ( deadlineId == ConstantDeadlineId )
    {
        ConstantDeadlineProcess::TDeadline deadlineValue;
        if ( !( conf >> deadlineValue >> comma ) )
        {
            class ConstantDeadlineValueFailed{};
            throw ConstantDeadlineValueFailed();
        }
        
        deadlineProcess = ns3::Create<ConstantDeadlineProcess>( deadlineValue );
    }
    else if ( deadlineId == UniformDeadlineId )
    {
        UniformDeadlineProcess::TDeadline lowerLimit, upperLimit;
        if ( !( conf >> lowerLimit >> comma ) )
        {
            class UniformLowerFailed{};
            throw UniformLowerFailed();
        }
        if ( !( conf >> upperLimit >> comma ) )
        {
            class UniformUpperFailed{};
            throw UniformUpperFailed();
        }
        
        deadlineProcess = ns3::Create<UniformDeadlineProcess>( lowerLimit, upperLimit );
    }
    
    return ( deadlineProcess );
}