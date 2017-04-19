//
//  DeadlineProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef DeadlineProcess_hpp
#define DeadlineProcess_hpp

#include <ns3/core-module.h>

/**
 Base class for a deadline process. Any inheriting class must implement
 a deadline generating function and a destructor if necessary
**/
class DeadlineProcess : public ns3::SimpleRefCount< DeadlineProcess >
{
    public:
        /** Deadline type **/
        typedef ns3::Time TDeadline;
    
    protected:
        /** Expected deadline of the process **/
        TDeadline m_expectedDeadline;
    
    public:
        /** 
         Constructor to set the expected deadline value
         \param expectedDeadline Expected Deadline value.
        **/
        DeadlineProcess( const TDeadline expectedDeadline );
    
        /**
         Virtual function that returns the actual deadline value by the
         inheriting class.
         \return The next deadline value.
        **/
        virtual TDeadline
        GetNextDeadline( void ) const = 0;
    
        /**
         Returns the expected deadline value.
         \return Expected deadline independent from the distribution.
        **/
        TDeadline
        GetExpectedDeadline( void ) const
        {
            return ( this->m_expectedDeadline );
        }
    
        /**
         Empty virtual destructor.
        **/
        virtual ~DeadlineProcess( void ){}
};

#endif /* DeadlineProcess_hpp */
