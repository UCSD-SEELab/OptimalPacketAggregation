//
//  ADATransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 10/6/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef ADATransmissionManager_hpp
#define ADATransmissionManager_hpp

#include "TransmissionManager.hpp"

/**
 Implements the ADA transmission manager implementation.
 **/
class ADATransmissionManager : public TransmissionManager
{
    private:
        /** Tf time constant **/
        GainFunction::TTransmissionTime m_timeConstant;
    
        /** Time to check for the transmission timer **/
        GainFunction::TTransmissionTime m_checkTimer;
        
        /** phi Factor **/
        double m_phi = 0.9;
        
        /** S Queue Size **/
        double m_S = 32;
    
    private:
        /** Checks whether the waiting timer is to be fired **/
        void
        CheckWaitingTimer( void );
    
    public:
        /**
         ns3 related Type ID function.
         \return ns3 related Type ID.
         **/
        static ns3::TypeId
        GetTypeId( void );
        
        /**
         Starts the applications.
         **/
        void
        Start( void );
        
        /**
         Transmits all measurements in the aggregation queue.
         **/
        void
        TransmitAllMeasurements( void );
        
        /**
         Reads the configuration from "cascTM.txt" file.
         **/
        void
        ReadConfiguration( void );
};

#endif /* ADATransmissionManager_hpp */
