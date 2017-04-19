//
//  UniformDeadlineProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef UniformDeadlineProcess_hpp
#define UniformDeadlineProcess_hpp

#include <ns3/core-module.h>
#include "DeadlineProcess.hpp"

/**
 This class implements a Uniform random value deadline process.
**/
class UniformDeadlineProcess : public DeadlineProcess
{
    public:
        /** Type for the uniform boundaries **/
        typedef double TBoundSeconds;
    
    private:
        /** Type for the uniform number generator **/
        typedef ns3::Ptr<ns3::UniformRandomVariable> TUniformGenerator;
    
    private:
        /**
         Uniform distributed number generator
        **/
        TUniformGenerator m_uniformGenerator;
    
        /**
         Lower bound of the uniform random number
        **/
        TBoundSeconds m_lowerBound;
    
        /**
         Upper bound of the uniform random number
        **/
        TBoundSeconds m_upperBound;
    
    public:
        /**
         Constructor takes in the bounds and initiates the base class with their
         average.
         \param lowerBound Lower bound of the random number.
         \param upperBound Upper bound of the random number.
        **/
        UniformDeadlineProcess( const TDeadline lowerBound,
                                const TDeadline upperBound );
    
        /**
         Generates a uniform distributed deadline value.
         \return Next deadline value on a uniform distribution.
        **/
        TDeadline
        GetNextDeadline( void ) const;
    
        /**
         Returns the lower bound.
         \return Lower bound.
        **/
        TBoundSeconds
        GetLowerBound( void ) const
        {
            return ( this->m_lowerBound );
        }
    
        /**
         Returns the upper bound.
         \return Upper bound.
        **/
        TBoundSeconds
        GetUpperBound( void ) const
        {
            return ( this->m_upperBound );
        }
};

#endif /* UniformDeadlineProcess_hpp */
