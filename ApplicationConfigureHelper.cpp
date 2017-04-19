//
//  ApplicationConfigureHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/16/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "ApplicationConfigureHelper.hpp"


void
ApplicationConfigureHelper::Configure( TransmissionManager* tm )
{
    std::ifstream conf( "applicationConf.txt" );
    if ( !conf )
    {
        class FileOpenFailed{};
        throw FileOpenFailed();
    }
    
    while ( !conf.eof() )
    {
        Application::TDeadlinePtr deadlineProcess = DeadlineConfigureHelper::Configure( conf );
        Application::TGenerationPtr generationProcess = GenerationConfigureHelper::Configure( conf );
        Application::TGainFunctionPtr gainFunction = GainConfigureHelper::Configure( conf );
        
        tm->InstallApplication( ns3::Create<Application>( generationProcess, deadlineProcess, gainFunction ) );
    }
}
