//
//  GainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef GainFunction_hpp
#define GainFunction_hpp

#include "Measurement.hpp"
#include "GenerationProcess.hpp"
#include "DeadlineProcess.hpp"

#include <ns3/core-module.h>

/**
 Base gain function class. Any inheriting class must implement the gain value
 and gain derivative value functions for optimization.
**/
class GainFunction : public ns3::SimpleRefCount< GainFunction >
{
    public:
        /** Generation Process Smart Pointer type **/
        typedef ns3::Ptr< GenerationProcess > TGenerationPtr;
    
        /** Deadline process Smart Pointer type **/
        typedef ns3::Ptr< DeadlineProcess > TDeadlinePtr;
    
        /** Gain value type **/
        typedef double TGain;
    
        /** Transmission Tyime type **/
        typedef ns3::Time TTransmissionTime;
    
    protected:
        /** Generation Process pointer, initially null **/
        TGenerationPtr m_generationProcess = nullptr;
    
        /** Deadline Process pointer, initially null **/
        TDeadlinePtr m_deadlineProcess = nullptr;
    
    public:
        /**
         Virtual function to set the generation and deadline processes.
         \param gen Generation process pointer.
         \param deadline Deadline process pointer.
        **/
        virtual void
        SetProcesses( const TGenerationPtr & gen,
                      const TDeadlinePtr & deadline );
    
        /**
         Virtual empty destructor.
        **/
        virtual ~GainFunction( void ){}
    
        /**
         Virtual function to obtain the gain derivative value.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
        **/
        virtual TGain
        GetGainDerivative( const TTransmissionTime & x ) const = 0;
    
        /**
         Virtual function to obtain the gain value.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
        **/
        virtual TGain
        GetGain( const TTransmissionTime & x ) const = 0;
};

#endif /* MeasurementGainFunction_hpp */
