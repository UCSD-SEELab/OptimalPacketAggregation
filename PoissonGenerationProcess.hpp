//
//  PoissonGenerationProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef PoissonGenerationProcess_hpp
#define PoissonGenerationProcess_hpp

#include "GenerationProcess.hpp"

/**
 Implements a Poisson distributed generation process.
**/
class PoissonGenerationProcess : public GenerationProcess
{
    private:
        /** Uniform distributed random number generator **/
        typedef ns3::Ptr<ns3::UniformRandomVariable> TUniformGenerator;
    
    private:
        /** Uniform random number generator **/
        TUniformGenerator m_uniformGenerator;
    
    public:
        /**
         Constructor to set the mean generation rate.
         \param lambda Mean generation rate.
        **/
        PoissonGenerationProcess( const TMeanRate lambda );
        
    private:
        /**
         Schedules a generation according to the Poisson distribution.
        **/
        void
        ScheduleGeneration( void );
    
        /**
         Creates a measurement and adds to the queue.
        **/
        void
        CreateMeasurement( void );

        /**
         Returns the next arrival time according ot the exponential distribution
         \return Next measurement arrival time.
        **/
        TArrivalTime
        GetNextTime( void ) const;
};

#endif /* PoissonGenerationProcess_hpp */
