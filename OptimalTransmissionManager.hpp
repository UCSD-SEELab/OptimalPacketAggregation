//
//  OptimalTransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/10/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef OptimalTransmissionManager_hpp
#define OptimalTransmissionManager_hpp

#include "TransmissionManager.hpp"

/**
 Implements the Optimal single hop Transmission Manager algorithm.
**/
class OptimalTransmissionManager : public TransmissionManager
{
    public:
        /** Gain value type. **/
        typedef GainFunction::TGain TGain;
    
    private:
        /** Gain maximization iteration count type **/
        typedef unsigned int TCount;
    
    private:
        /** Number of bisection iterations **/
        TCount m_searchCount;
    
        /** Bisection search start value **/
        ns3::Time m_searchStart;
    
        /** Bisection search stop value **/
        ns3::Time m_searchStop;
    
    private:
        /**
         Obtains the total gain value for a given aggregation time
         \param x Tried aggregation time value.
         \return Total gain value.
        **/
        TGain
        GetTotalGain( const GainFunction::TTransmissionTime & x ) const;
    
        /**
         Searches for the optimal time that maximizes the gain value.
         \return Optimal aggregation time.
        **/
        GainFunction::TTransmissionTime
        GetOptimalTime( void ) const;
    
        /**
         Reads "optimalTM.txt" for configuration of search parameters.
        **/
        virtual void
        ReadConfiguration( void );
    
    public:
        /**
         ns3 related Type ID function.
         \return ns3 Type ID value.
        **/
        static ns3::TypeId
        GetTypeId( void );
    
        /**
         Constructor to set default search values.
        **/
        OptimalTransmissionManager( void );
    
        /**
         Starts all applications and calculates the optimal transmission time.
        **/
        void
        Start( void );
    
        /**
         Transmits all measurements in the aggregation queue.
        **/
        void
        TransmitAllMeasurements( void );
};

#endif /* OptimalTransmissionManager_hpp */
