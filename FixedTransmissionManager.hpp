//
//  FixedTransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/13/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef FixedTransmissionManager_hpp
#define FixedTransmissionManager_hpp

#include "TransmissionManager.hpp"

/**
 Implements the Fixed period transmission manager.
**/
class FixedTransmissionManager : public TransmissionManager
{
    private:
        /** Fixed period of transmission **/
        GainFunction::TTransmissionTime m_fixedTime;
        
    public:
        /**
         Returns the ns3 related Type ID.
         \return ns3 Type ID
        **/
        static ns3::TypeId
        GetTypeId( void );
    
        /**
         Starts all applications and aggregation.
        **/
        void
        Start( void );
    
        /**
         Transmits all measurements aggregated.
        **/
        void
        TransmitAllMeasurements( void );
    
        /**
         Sets the fixed aggregation period.
         \param fixedTime Fixed period.
        **/
        void
        SetInterval( const GainFunction::TTransmissionTime & fixedTime )
        {
            this->m_fixedTime = fixedTime;
        }
    
        /**
         Reads the configuration from "fixedTM.txt"
        **/
        void
        ReadConfiguration( void );
};


#endif /* FixedTransmissionManager_hpp */
