//
//  Measurement.h
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef Measurement_hpp
#define Measurement_hpp

#include <string.h>
#include <iostream>
#include <ns3/core-module.h>

/**
 A simple measurement class.
 The data includes an ID and the value of the measurement, which simulate the
 actual OTA data content. The class also includes statistics related values,
 normally not expected to be sent.
**/
class Measurement : public ns3::SimpleRefCount< Measurement >
{
    public:
        /** Type of a measurement ID **/
        typedef unsigned short TId;
    
        /** Type of the measurement value **/
        typedef unsigned short TMeasurement;
    
        /** Type for generation time **/
        typedef double TGenerationTime;
    
        /** Type for reception time **/
        typedef double TReceptionTime;
    
        /** Type for the deadline **/
        typedef double TDeadline;

        /** Special values for ID type **/
        enum IdValues : TId
        {
            /** If the ID is not set, invalid is used instead **/
            InvalidId = ( TId )-1
        };
    
        /** Size of the data content fields. **/
        enum SizeInformation : unsigned int
        {
            /** Size of the ID field **/
            IdSize = sizeof( TId ),
            
            /** Size of the measurement value field **/
            MeasurementSize = sizeof( TMeasurement ),
            
            /** Size of the generation time field **/
            GenerationTimeSize = sizeof( TGenerationTime ),
            
            /** Size of the reception time field **/
            ReceptionTimeSize = sizeof( TReceptionTime ),
            
            /** Size of the deadline field **/
            DeadlineSize = sizeof( TDeadline ),
            
            /** Total size of the measurement **/
            TotalSize = IdSize + MeasurementSize + GenerationTimeSize + ReceptionTimeSize + DeadlineSize
        };
    
    private:
        /** Measurement identifier **/
        TId m_id;
    
        /** Value of the sensor measurement **/
        TMeasurement m_value;
    
        /** Time of generation **/
        TGenerationTime m_generationTime;
    
        /** Time of reception **/
        TReceptionTime m_receptionTime;
    
        /** Deadline starting from generation **/
        TDeadline m_deadline;
    
        /** Measurement counter for statistics **/
        static TMeasurement measurementCounter;
    
    public:
        /** Default constructor, does nothing **/
        Measurement( void );
    
        /** Creates a measurement with an ID and a value **/
        Measurement( const TId id, const TMeasurement value = measurementCounter );
    
        /** Copy constructor **/
        Measurement( const Measurement & copy );
    
        /** Reads from a buffer and increments it by the total size.
         \param buffer Buffer to be read from.
         \return Returns the address of the next measurement
        **/
        void*
        ReadFromBuffer( void* buffer );
    
        /** Writes to a buffer the contents of the measurement 
         \param buffer Buffer to be written to.
         \return Returns the address for the next measurement
        **/
        void*
        WriteToBuffer( void* buffer );
    
        /**
         Prints the contents of the measurement for debugging
        **/
        void
        Print( void );
    
        /**
         Sets the deadline of the measurement
         \param deadline New deadline of the measurement
        **/
        void
        SetDeadline( const TDeadline deadline )
        {
            this->m_deadline = deadline;
        }
    
        /**
         Returns the value of the measurement
         \return Value of the measurement
        **/
        TMeasurement
        GetValue( void ) const
        {
            return ( this->m_value );
        }
    
        /**
         Returns the ID of the measurement.
         \return ID of the measurement.
        **/
        TId
        GetId( void ) const
        {
            return ( this->m_id );
        }
    
        /**
         Returns the generation time of the measurement.
         \return Generation time of the measurement.
        **/
        TGenerationTime
        GetGenerationTime( void ) const
        {
            return ( this->m_generationTime );
        }
    
        /**
         Returns the reception time of the measurement.
         \return Reception time of the measurement.
        **/
        TReceptionTime
        GetReceptionTime( void ) const
        {
            return ( this->m_receptionTime );
        }
    
        /**
         Returns the deadline of the measurement.
         \return Deadline of the measurement.
        **/
        TDeadline
        GetDeadline( void ) const
        {
            return ( this->m_deadline );
        }
    
        /**
         Calculates the delay of the measurement for statistics.
         \return Delay of the measurement.
        **/
        TDeadline
        GetDelay( void ) const
        {
            return ( this->m_receptionTime - this->m_generationTime );
        }
    
        /**
         Checks whether the measurement is expired or not.
         \return Is the measurement expired.
        **/
        bool
        IsExpired( void ) const
        {
            return ( this->GetDelay() > this->m_deadline );
        }
    
        /**
         Returns the freshness of the measurement.
         \return Information freshness of the measurement.
        **/
        TDeadline
        GetFreshness( void ) const
        {
            return ( this->m_deadline - this->GetDelay() );
        }
    
        /**
         Marks the measurement as received and sets the reception time.
        **/
        void
        MarkReceived( void );
};

/** Type for smart pointer to a measurement **/ 
typedef ns3::Ptr< Measurement > TMeasurementPtr;

#endif /* Measurement_h */
