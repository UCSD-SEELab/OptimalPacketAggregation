//
//  FiveGTransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef FiveGTransmissionManager_hpp
#define FiveGTransmissionManager_hpp

#include "TransmissionManager.hpp"
#include "BaseStation.hpp"

/**
 Implements the 5G optimal transmission manager algorithm that takes into
 account the congestion levels and related degradation as a gain function.
**/
class FiveGTransmissionManager : public TransmissionManager
{
    public:
        /** Gain value type. **/
        typedef GainFunction::TGain TGain;
    
    private:
        /** Gain maximization iteration count type **/
        typedef unsigned int TCount;

    private:
        /**
         The communication with the base station is not implemented and is
         currently bypassed using a pointer to the actual C value in the
         base station.
        **/
        TGain* m_cValue;
    
        /**
         Current C value used for aggregation time determination. This is used
         to check whether the cached C value is the same as in the base station.
         If they are different, an iteration is started with the new value.
        **/
        TGain m_usedCValue;
    
        /**
         Current optimal transmission time.
        **/
        GainFunction::TTransmissionTime m_currentOptimalTime;
    
        /** Number of Bisection method iterations **/
        TCount m_searchCount;
    
        /** Bisection method starting value **/
        ns3::Time m_searchStart;
    
        /** Bisection method stopping value **/
        ns3::Time m_searchStop;
    
        /** Update threshold for transmission time changes. **/
        GainFunction::TTransmissionTime m_updateThreshold;
    
        /** My responses to the C values of the base station. **/
        BaseStation::TResponseVector m_myResponses;
        
    private:
        /**
         Returns the total gain value of the applications.
         \param x Aggregation time to be used in the gain function.
         \return Total gain value of the applications.
        **/
        TGain
        GetTotalGain( const GainFunction::TTransmissionTime & x ) const;
    
        /**
         Returns the total gain derivative value of the applications.
         \param x Aggregation time to be used in the gain function.
         \return Total gain derivative value of the applications.
         **/
        TGain
        GetTotalGainDerivative( const GainFunction::TTransmissionTime & x ) const;
    
        /**
         Solves for a given C value using Bisection internally.
         \param cValue C Value to be used for iterations.
         \return Optimal aggregation time for the c value.
        **/
        GainFunction::TTransmissionTime
        SolveForCValue( const TGain cValue ) const;
    
        /**
         Solves the optimal aggregation time by negotiating with the base
         station for the common C value.
         \return Optimal aggregation time.
        **/
        GainFunction::TTransmissionTime
        GetOptimalTime( void );
    
        /**
         Reads the bisection searching parameters from "5GTM.txt"
        **/
        void
        ReadConfiguration( void );
    
        /**
         Calculates the total gain value for a given C value.
         \param cValue C Value to be solved for internally.
         \return Total gain value for the given C value.
        **/
        TGain
        ProcessCValue( const TGain cValue ) const;
    
        /**
         Connects to the base station and starts a negotiation.
        **/
        void
        ConnectToBaseStation( void );
    
    public:
        /**
         ns3 related Type ID function.
         \return ns3 related Type ID.
        **/
        static ns3::TypeId
        GetTypeId( void );
    
        /**
         Constructor to set the default value.
        **/
        FiveGTransmissionManager( void );
    
        /**
         Empty destructor.
        **/
        ~FiveGTransmissionManager( void ){};
    
        /**
         Starts the applications and computes the optimal aggergation time.
        **/
        void
        Start( void );
    
        /**
         Transmits all measurements in the aggregation queue.
        **/
        void
        TransmitAllMeasurements( void );
    
    
};

#endif /* FiveGTransmissionManager_hpp */
