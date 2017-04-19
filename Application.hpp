//
//  Application.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef Application_hpp
#define Application_hpp

#include <map>

#include "MeasurementQueue.hpp"
#include "GainFunction.hpp"

/**
 \brief Describes an application that generates data with associated deadlines.
 Each application is also assigned a gain function for optimization.
 */
class Application : public ns3::SimpleRefCount< Application >
{
    public:
        /** Generation process pointer **/
        typedef GainFunction::TGenerationPtr TGenerationPtr;
    
        /** Deadline process pointer **/
        typedef GainFunction::TDeadlinePtr TDeadlinePtr;
    
        /** Pointer to the gain function **/
        typedef ns3::Ptr< GainFunction > TGainFunctionPtr;
    
    private:
        /** Each application is assigned an ID for identification **/
        typedef Measurement::TId TApplicationId;
    
        /** A key-value store to map IDs to Application pointers **/
        typedef std::map< TApplicationId, Application* > TApplicationMap;
    
    private:
        /** Global Application ID counter for unique assignment **/
        static TApplicationId globalIdCounter;
    
        /** Global Application mapping from ID to Application pointers **/
        static TApplicationMap globalApplicationMap;
    
    private:
        /** Unique ID of this Application **/
        TApplicationId m_id;
    
        /** The generation process for data generation **/
        TGenerationPtr m_generationProcess;
    
        /** The deadline process for deadline assignment **/
        TDeadlinePtr m_deadlineProcess;
    
        /** The queue holding the measurements to be sent **/
        TMeasurementQueuePtr m_measurementQueue;
    
        /** Pointer to the data stream gain function **/
        TGainFunctionPtr m_gainFunction;
    
    public:
        /**
         Constructor without a gain function definition.
         \param generation The generation process.
         \param deadline The deadline process.
        **/
        Application( TGenerationPtr generation, TDeadlinePtr deadline );
    
        /** 
         Constructor with all the necessary elements.
         \param generation The generation process.
         \param deadline The deadline process.
         \param gainFunction The Gain Function of the Application.
        **/
        Application( TGenerationPtr generation, TDeadlinePtr deadline, const TGainFunctionPtr & gainFunction );
    
        /**
         Template constructor for the cases of Gain function type mismatch.
         \param generation The generation process.
         \param deadline The deadline process.
         \param gainFunction Gain function of the application.
         \tparam GainFunctionType The template type of the gain function.
        **/
        template <typename GainFunctionType>
        Application( TGenerationPtr generation,
                     TDeadlinePtr deadline,
                     const ns3::Ptr<GainFunctionType> & gainFunction ) : Application( generation,
                                                                                      deadline,
                                                                                      ns3::DynamicCast< GainFunction >( gainFunction ) )
        {
        }
    
        /** Prints Application and its queue for information **/
        void
        Print( void ) const;
    
        /** 
         Sets the Application's gain function .
         \param gainFunction New Gain Function of the application.
        **/
        void
        SetMeasurementGainFunction( const TGainFunctionPtr & gainFunction );
    
        /**
         Returns the value of the Gain function for a given transmission time.
         \param x The queried transmission time.
         \return Returns the Gain value of the Application.
        **/
        GainFunction::TGain
        GetMeasurementGain( const GainFunction::TTransmissionTime & x ) const;
    
        /**
         Return the derivative value of the Gain function for a given 
         transmission time.
         \param x The queried transmission time.
         \return Returns the Derivative of the Gain function of the Application.
        **/
        GainFunction::TGain
        GetMeasurementGainDerivative( const GainFunction::TTransmissionTime & x ) const;
    
        /**
         Moves all measurements into the given queue.
         \param measurementQueue The queue to be moved into.
        **/
        void
        GetAllMeasurements( TMeasurementQueuePtr & measurementQueue );
    
        /**
         Static function that returns the generation prcess of an Application.
         \param id ID to be queried.
         \return Returns the generation process of the application.
        **/
        static TGenerationPtr
        GetGenerationProcess( const TApplicationId id );
    
        /**
         Static function that returns the deadline process of an Application.
         \param id ID to be queried.
         \return Returns the deadline process of the application.
        **/
        static TGenerationPtr
        GetDeadlineProcess( const TApplicationId id );
    
        /**
         Returns the number of measurements queued.
         \return Number of measurements in the queue.
        **/
        MeasurementQueue::TQueueSize
        GetNumberOfQueuedMeasurements( void ) const;
};

/** Smart Pointer to an Application **/
typedef ns3::Ptr<Application> TApplicationPtr;

#endif /* Application_hpp */
