//
//  ApplicationConfigureHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/16/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef ApplicationConfigureHelper_hpp
#define ApplicationConfigureHelper_hpp

#include "TransmissionManager.hpp"

#include "DeadlineConfigureHelper.hpp"
#include "GenerationConfigureHelper.hpp"
#include "GainConfigureHelper.hpp"

/**
 This class helps the configuration of Applications to be used with a transmission
 manager. It reads the configuration file applicationConf.txt.
**/
class ApplicationConfigureHelper
{
    public:
        /**
         Configures the given transmission manager using the configuration file.
         \param tm Tranmission manager to be configured.
        **/
        static void
        Configure( TransmissionManager* tm );
    
};

#endif /* ApplicationConfigureHelper_hpp */
