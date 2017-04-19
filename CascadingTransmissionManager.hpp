//
//  CascadingTransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/27/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef CascadingTransmissionManager_hpp
#define CascadingTransmissionManager_hpp

#include "TransmissionManager.hpp"

/**
 Implements the cascading transmission manager implementation that takes into
 account the hop distances to the sink node by a discount factor.
**/
class CascadingTransmissionManager : public TransmissionManager
{
    private:
        /** Transmission period **/
        GainFunction::TTransmissionTime m_fixedTime;
    
        /** Hop distance to the sink node **/
        unsigned int m_hopNumber;
        
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


#endif /* CascadingTransmissionManager_hpp */
