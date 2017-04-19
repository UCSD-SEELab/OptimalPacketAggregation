//
//  DeadlineConfigureHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef DeadlineConfigureHelper_hpp
#define DeadlineConfigureHelper_hpp

#include "TransmissionManager.hpp"

#include "ConstantDeadlineProcess.hpp"
#include "UniformDeadlineProcess.hpp"

#include <fstream>

/**
 This class configures the deadline process for an application.
**/
class DeadlineConfigureHelper
{
    public:
        /** Deadline ID type **/
        typedef unsigned int TDeadlineId;
    
        /** Current deadline implementations **/
        enum DeadlineIdValues : TDeadlineId
        {
            /** Constant deadline process **/
            ConstantDeadlineId = 0,
            
            /** Uniform random deadline process **/
            UniformDeadlineId = 1
        };
        
    public:
        /**
         Function to configure the deadline process from a file stream.
         \param input File stream to read configuration values.
         \return Creates a deadline process and returns the pointer.
        **/
        static Application::TDeadlinePtr
        Configure( std::ifstream & input );
    
};

#endif /* DeadlineConfigureHelper_hpp */
