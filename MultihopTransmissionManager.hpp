//
//  MultihopTransmissionManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/27/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef MultihopTransmissionManager_hpp
#define MultihopTransmissionManager_hpp

#include "TransmissionManager.hpp"

/**
 Implements the Multi Hop Optimal transmission manager algorithm by using the
 relaying delay based gain function.
**/
class MultihopTransmissionManager : public TransmissionManager
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
    
        /** Hop distance type **/
        typedef unsigned int THopDistance;
        
    private:
        /** Gain maximization iteration count type **/
        typedef unsigned int TCount;
        
    private:
        /** Number of Bisection method iterations **/
        TCount m_searchCount;
    
        /** Bisection method starting value **/
        ns3::Time m_searchStart;
    
        /** Bisection method stopping value **/
        ns3::Time m_searchStop;
    
        /** Hop distance to the Sink Node **/
        THopDistance m_hopDistance;
    
        /** Added delay due to the distance to the Sink Node **/
        ns3::Time m_hopFactor;
        
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
        GainFunction::TTransmissionTime
        GetOptimalTime( void ) const;
    
        /**
         Reads the bisection searching parameters from "multihopTM.txt"
        **/
        virtual void
        ReadConfiguration( void );
        
    public:
        /**
         ns3 related Type ID function.
         \return ns3 related Type ID.
         **/
        static ns3::TypeId
        GetTypeId( void );
    
        /**
         Constructor sets the default values.
        **/
        MultihopTransmissionManager( void );
    
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
    
        /**
         Sets the hop distance to the Sink Node.
         \param hop Distance to the Sink Node.
        **/
        void
        SetHopDistance( const THopDistance hop )
        {
            this->m_hopDistance = hop;
        }
};

#endif /* MultihopTransmissionManager_hpp */
