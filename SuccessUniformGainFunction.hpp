//
//  SuccessUniformGainFunction.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/22/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef SuccessUniformGainFunction_hpp
#define SuccessUniformGainFunction_hpp

#include "GainFunction.hpp"
#include "UniformDeadlineProcess.hpp"

/**
 Implements the expiration minimization gain function for a uniform generation.
 **/
class SuccessUniformGainFunction : public GainFunction
{
    public:
        /** Gain value type **/
        typedef GainFunction::TGain TGain;
    
        /** Transmission time type **/
        typedef GainFunction::TTransmissionTime TTransmissionTime;
    
    private:
        /** Lower bound for the uniform random number. **/
        UniformDeadlineProcess::TBoundSeconds m_lower;
    
        /** Upper bound for the uniform random number. **/
        UniformDeadlineProcess::TBoundSeconds m_upper;
        
    public:
        /**
         Returns the expiration gain value.
         \param x Aggreagation time to be calculated for.
         \return Gain value.
         **/
        TGain
        GetGain( const TTransmissionTime & x ) const;
    
        /**
         Returns the expiration gain derivative value.
         \param x Aggreagation time to be calculated for.
         \return Gain derivative value.
        **/
        TGain
        GetGainDerivative( const TTransmissionTime & x ) const;
    
        /**
         Sets the generation and deadline processes.
         \param gen Generation process.
         \param deadline Deadline process.
        **/
        void
        SetProcesses( const TGenerationPtr & gen,
                      const TDeadlinePtr & deadline );
        
};

#endif /* SuccessUniformGainFunction_hpp */
