//
//  GenerationConfigureHelper.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef GenerationConfigureHelper_hpp
#define GenerationConfigureHelper_hpp

#include "TransmissionManager.hpp"

#include "ConstantGenerationProcess.hpp"
#include "PoissonGenerationProcess.hpp"
#include "IntermittenGenerationProcess.hpp"

#include <fstream>

/**
 This class configures a Generation process from an input file stream.
**/
class GenerationConfigureHelper
{
    public:
        /** Generation process ID type **/
        typedef unsigned int TGenerationId;
    
        /** Implemented generation process IDs **/
        enum GenerationIdValues : TGenerationId
        {
            /** Constant rate generation process **/
            ConstantGenerationId = 0,
            
            /** Poisson distribution random generation process **/
            PoissonGenerationId = 1,
            
            /** Intermittent generation process with two rates **/
            IntermittentGenerationId = 2
        };
        
    public:
        /**
         This function configures a new generation process from a file stream.
         \param input Input file stream.
         \return A new generation process is created, configured and returned.
        **/
        static Application::TGenerationPtr
        Configure( std::ifstream & input );
        
};

#endif /* GenerationConfigureHelper_hpp */
