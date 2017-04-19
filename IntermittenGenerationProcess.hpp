//
//  IntermittenGenerationProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 12/6/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef IntermittenGenerationProcess_hpp
#define IntermittenGenerationProcess_hpp

#include "GenerationProcess.hpp"

/**
 Implements an Intermittent generation process.
 **/
class IntermittentGenerationProcess : public GenerationProcess
{
    private:
        /** Uniform distributed random number generator **/
        typedef ns3::Ptr<ns3::UniformRandomVariable> TUniformGenerator;
        
    private:
        /** Uniform random number generator **/
        TUniformGenerator m_uniformGenerator;
    
        /** First of the two rates **/
        TMeanRate m_slowRate;
    
        /** Second of the two rates **/
        TMeanRate m_fastRate;
    
        /** Minimum time for slow rate interval **/
        TArrivalTime m_minimumSlowTime;
    
        /** Maximum time for slow rate interval **/
        TArrivalTime m_maximumSlowTime;
    
        /** Minimum time for fast rate interval **/
        TArrivalTime m_minimumFastTime;
    
        /** Maximum time for fast rate interval **/
        TArrivalTime m_maximumFastTime;
    
        /** Indicates whether the current state is slow or fast **/
        bool m_slowStateCurrently;
        
    public:
        /**
         Constructor to set the generation rates and switching.
         \param slowRate Slow Mean generation rate.
         \param fastRate Fast Mean generation rate.
         \param minSlowTime Minimum time for Slow rate.
         \param maxSlowTime Maximum time for Slow rate.
         \param minFastTime Minimum time for Fast rate.
         \param maxFastTime Maximum time for Fast rate.
         **/
        IntermittentGenerationProcess( const TMeanRate slowRate,
                                       const TMeanRate fastRate,
                                       const TArrivalTime minSlowTime,
                                       const TArrivalTime maxSlowTime,
                                       const TArrivalTime minFastTime,
                                       const TArrivalTime maxFastTime  );
    
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
    
        /**
         Schedules an intermittent switch from slow to fast.
         **/
        void
        ScheduleSwitch( void );
};

#endif /* IntermittenGenerationProcess_hpp */
