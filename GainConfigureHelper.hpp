//
//  GainConfigureHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef GainConfigureHelper_hpp
#define GainConfigureHelper_hpp

#include "TransmissionManager.hpp"

#include "NoGainFunction.hpp"
#include "EnergyGainFunction.hpp"
#include "InformationFreshnessGainFunction.hpp"
#include "SuccessGainFunction.hpp"
#include "CongestionGainFunction.hpp"
#include "SuccessUniformGainFunction.hpp"

#include <fstream>

/**
 This class is used to configure the gain function for an application
**/
class GainConfigureHelper
{
    public:
        /** Gain function ID type **/
        typedef unsigned int TGainFunctionId;
    
        /** IDs for the implemented Gain functions **/
        enum GainFunctionIdValues : TGainFunctionId
        {
            /** Initial value for no gain function **/
            NoId = 0,
            
            /** Energy minimization gain function **/
            EnergyId = 1,
            
            /** Information Freshness maximization gain function **/
            InformationFreshnessId = 2,
            
            /** Expiration minimization gain function **/
            SuccessId = 3,
            
            /** Congestion minimization gain function **/
            CongestionId = 4,
            
            /** Uniform deadline expiration maximization gain function **/
            SuccessUniformId = 5,
        };
        
    public:
        /**
         This function configures a new gain function from a file stream.
         \param input Input file stream.
         \return A new gain function is created and configured and returned.
        **/
        static Application::TGainFunctionPtr
        Configure( std::ifstream & input );
    
};

#endif /* GainConfigureHelper_hpp */
