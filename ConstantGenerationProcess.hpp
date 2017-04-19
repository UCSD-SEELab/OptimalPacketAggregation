//
//  ConstantGenerationProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef ConstantGenerationProcess_hpp
#define ConstantGenerationProcess_hpp

#include "GenerationProcess.hpp"

/**
 Implements a constant rate generation process.
**/
class ConstantGenerationProcess : public GenerationProcess
{
    public:
        /** Constant Sampling Interval Type **/
        typedef ns3::Time TSamplingInterval;
    
    private:
        /** Constant generation interval **/
        TSamplingInterval m_samplingInterval;
    
    public:
        /**
         Constructor to set the constant generation rate
         \param samplingInterval Constant Sampling interval
        **/
        ConstantGenerationProcess( const TSamplingInterval samplingInterval );
    
    private:
        /**
         Schedule the generation of the next measurement(s)
        **/
        void
        ScheduleGeneration( void );
    
        /**
         Creates an actual measurement
        **/
        void
        CreateMeasurement( void );
};

#endif /* ConstantGenerationProcess_hpp */
