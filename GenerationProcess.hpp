//
//  GenerationProcess.h
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef GenerationProcess_h
#define GenerationProcess_h

#include <list>
#include "MeasurementQueue.hpp"
#include <ns3/core-module.h>

/**
 Base class for all generation process implementations. Any inheriting class
 must implement a method to schedule measurements
**/
class GenerationProcess : public ns3::SimpleRefCount< GenerationProcess >
{
    public:
        /** Mean generation rate type **/
        typedef double TMeanRate;
    
        /** Is deterministic boolean type **/
        typedef bool TIsDeterministic;
    
        /** Is deterministic values **/
        enum IsDeterministicValues : TIsDeterministic
        {
            /** Generation is deterministic **/
            IsDeterministic = true,
            
            /** Generation is random **/
            IsRandom = false
        };
    
        /** Arrival time type **/
        typedef ns3::Time TArrivalTime;
    
        /** Application ID type **/
        typedef Measurement::TId TId;
    
    protected:
        /** Mean rate of generation **/
        TMeanRate m_meanRate;
    
        /** Measurement queue of all the generated measurements **/
        TMeasurementQueuePtr m_measurementList;
    
        /** ID of the application **/
        TId m_id;
    
    protected:
        /**
         Constructor to set the mean rate.
         \param meanRate Mean generation rate.
        **/
        GenerationProcess( const TMeanRate meanRate );
    
        /**
         Constructor to set the mean rate and the measurement queue.
         \param meanRate Average generation rate.
         \param list Measurement queue.
        **/
        GenerationProcess( const TMeanRate meanRate, const TMeasurementQueuePtr list );
    
        /**
         Virtual class that schedules the next generation of measurement(s).
        **/
        virtual void ScheduleGeneration( void ) = 0;
    
        /**
         Adds a measurement to the measurement queue
         \param measurement New measurement to be added.
        **/
        void
        AddMeasurement( const TMeasurementPtr & measurement );
    
        /**
         Sets the mean generation rate.
         \return Mean generation rate.
         **/
        void
        SetMeanGenerationRate( const TMeanRate meanRate )
        {
            this->m_meanRate = meanRate;
        }
    
    public:
        /**
         Returns the mean generation rate.
         \return Mean generation rate.
        **/
        TMeanRate
        GetMeanGenerationRate( void ) const
        {
            return ( this->m_meanRate );
        }
    
        /**
         Sets the application ID.
         \param id Application ID.
        **/
        void
        SetId( const TId id )
        {
            this->m_id = id;
        }
    
        /**
         Returns the application ID.
         \return Application ID.
        **/
        TId
        GetId( void ) const
        {
            return ( this->m_id );
        }
    
        /**
         Sets the measurement queue.
         \param list Measurement queue.
        **/
        void
        SetMeasurementQueue( const TMeasurementQueuePtr list )
        {
            this->m_measurementList = list;
        }
    
        /**
         Virtual empty destructor.
        **/
        virtual ~GenerationProcess( void ){}
};

#endif /* GenerationProcess_h */
