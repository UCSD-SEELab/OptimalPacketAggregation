//
//  MeasurementQueue.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef MeasurementQueue_hpp
#define MeasurementQueue_hpp

#include <list>
#include "Measurement.hpp"
#include <ns3/core-module.h>

/**
 A queue class containing measurements and provides simple modification methods.
**/
class MeasurementQueue : public ns3::SimpleRefCount< MeasurementQueue >
{
    private:
        /** Type of the underlying storage type **/
        typedef std::list<TMeasurementPtr> TMeasurementQueue;
    
    public:
        /** Type for the size of the queue **/
        typedef unsigned int TQueueSize;
    
        /** Iterator type for the queue **/
        typedef TMeasurementQueue::iterator TIterator;
    
        /** Constant iterator type for the queue **/
        typedef TMeasurementQueue::const_iterator TConstIterator;
    
    private:
        /** Underlying measurement storage element **/
        TMeasurementQueue m_queue;
    
    public:
        /**
         Adds a new measurement item
         \param item New measurement
        **/
        void
        Add( const TMeasurementPtr & item );
    
        /**
         Adds multiple measurement items at once
         \param items The queue to be merged
        **/
        void
        Add( MeasurementQueue & items );
    
        /**
         Empties the queue from all measurements.
        **/
        void
        Empty( void );
    
        /**
         Prints the contents for information
        **/
        void
        Print( void ) const;
    
        /**
         Returns the total size (bytes) of all measurements in the queue.
         \return Size (bytes) of all measurements in the queue.
        **/
        TQueueSize
        Size( void ) const
        {
            return ( ( TQueueSize )( this->m_queue.size() ) * Measurement::TotalSize );
        }
    
        /**
         Returns the number of measurement in the queue.
         \return Number of measurements in the queue.
        **/
        TQueueSize
        Count( void ) const
        {
            return ( ( TQueueSize )( this->m_queue.size() ) );
        }
    
        /**
         Reads from a buffer and creates measurements
         \param buffer Address of the buffer
         \param bufferSize Size of the buffer
         \return Address of the end of the buffer
        **/
        void*
        ReadFromBuffer( void* buffer, const unsigned int bufferSize );
    
        /**
         Writes to a buffer all measurements in the queue.
         \param buffer Buffer to be written to.
         \return Address of the end of the buffer.
        **/
        void*
        WriteToBuffer( void* buffer );
    
        /**
         Beginning of the queue iterator.
         \return Beginning iterator.
        **/
        TIterator
        Begin( void )
        {
            return ( this->m_queue.begin() );
        }
    
        /**
         Beginning of the queue iterator (constant).
         \return Constant beginning iterator.
        **/
        TConstIterator
        Begin( void ) const
        {
            return ( this->m_queue.begin() );
        }
    
        /** 
         End of the queue iterator
         \return Ending iterator
        **/
        TIterator
        End( void )
        {
            return ( this->m_queue.end() );
        }
    
        /**
         End of the queue iterator (constant).
         \return Ending iterator (constant).
        **/
        TConstIterator
        End( void ) const
        {
            return ( this->m_queue.end() );
        }
};

/** Type of a smart pointer to the measurement queue class **/
typedef ns3::Ptr<MeasurementQueue> TMeasurementQueuePtr;

#endif /* MeasurementQueue_hpp */
