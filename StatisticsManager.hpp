//
//  StatisticsManager.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef StatisticsManager_hpp
#define StatisticsManager_hpp

#include <map>

#include "Measurement.hpp"
#include "MeasurementQueue.hpp"
#include "TransmissionManager.hpp"

/**
 This class defines the main statistical manager regarding the whole simulation.
*/
class StatisticsManager
{
    private:
        /** A map type from measurement IDs to related queues **/
        typedef std::map< Measurement::TId, MeasurementQueue > TMeasurementMap;
    
        /** A packet counter type **/
        typedef unsigned int TPacketCount;
    
        /** Smart pointer to a node **/
        typedef TransmissionManager::TNodePtr TNodePtr;
    
        /** A map from nodes to the number of packets **/
        typedef std::map< TransmissionManager::TNodePtr, TPacketCount > TPacketCountMap;
    
    public:
        /** Defines a Delay type **/
        typedef ns3::Time TDelay;
    
        /** Expiration Rate type **/
        typedef double TExpirationRate;
    
        /** Information Freshness type **/
        typedef ns3::Time TInformationFreshness;
    
    private:
        /** Collects the generated measurements by each application ID **/
        TMeasurementMap m_generatedMeasurements;
    
        /** Collects the received measurements by each application ID **/
        TMeasurementMap m_receivedMeasurements;
    
        /** Counts the number of transmitted packets **/
        TPacketCountMap m_txPacketCounts;
    
        /** Counts the number of received packets **/
        TPacketCount m_rxPacketCount;
    
        /** Name of the Log File **/
        std::string m_logFileName = "results.txt";
    
        /** Indicates whether to write the timeseries file. **/
        bool m_writeTimeseries = false;
    
    private:
        /** Private constructor for Singleton construction **/
        StatisticsManager( void ){}
    
        /**
         Calculates the average delay of a queue.
         \param queue The queue to be processed.
         \return Average delay of the queue.
        **/
        TDelay
        GetAverageDelay( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the maximum delay of a queue.
         \param queue The queue to be processed.
         \return Maximum delay of the queue.
         **/
        TDelay
        GetMaximumDelay( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the total delay of a queue.
         \param queue The queue to be processed.
         \return Total delay of the queue.
        **/
        TDelay
        GetTotalDelay( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the expiration rate of a measurement queue.
         \param queue The queue to be processed.
         \return Expiration rate.
        **/
        TExpirationRate
        GetExpirationRate( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the number of expired measurements.
         \param queue The queue to be processed.
         \return Number of expired measurements.
        **/
        MeasurementQueue::TQueueSize
        GetNumberOfExpired( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the total Information Freshness.
         \param queue The queue to be processed.
         \return Total Information Freshness.
        **/
        TInformationFreshness
        GetTotalInformationFreshness( const MeasurementQueue & queue ) const;

        /**
         Calculates the average Information Freshness.
         \param queue The queue to be processed.
         \return Average Information Freshness.
        **/
        TInformationFreshness
        GetAverageInformationFreshness( const MeasurementQueue & queue ) const;
    
        /**
         Calculates the total number of lost measurements.
         \return Total number of lost measurements.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfLost( void ) const;

        /**
         Calculates the total number of expired measurements.
         \return Total number of expired measurements.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfExpired( void ) const;
    
        /**
         Calculates the total number of sent measurements.
         \return Total number of sent measurements.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfSent( void ) const;
    
        /**
         Calculates the total number of transmitted packets.
         \return Total number of transmitted packets.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfTransmitted( void ) const;
    
        /**
         Calculates the total number of received packets.
         \return Total number of received packets.
        **/
        MeasurementQueue::TQueueSize
        GetTotalNumberOfReceived( void ) const;
    
        /**
         Calculates the average delay.
         \return Average delay.
        **/
        TDelay
        GetAverageDelay( void ) const;
    
        /**
         Calculates the maximum delay.
         \return Maximum delay.
        **/
        TDelay
        GetMaximumDelay( void ) const;
    
        /**
         Calculates the Total Information Freshness over all packets.
         \return Total Information Freshness.
        **/
        TInformationFreshness
        GetTotalInformationFreshness( void ) const;
    
        /**
         Calculates the Average Information Freshness over all packets.
         \return Average Information Freshness.
        **/
        TInformationFreshness
        GetAverageInformationFreshness( void ) const;
    
        /**
         Calculates the total Information Freshness per Packet.
         \return Information Freshness per packet.
        **/
        TInformationFreshness
        GetInformationFreshnessPerPacket( void ) const;
    
        /**
         Calculates the Expiration Rate of all packets.
         \return Expiration Rate
        **/
        TExpirationRate
        GetExpirationRate( void ) const;
    
    public:
        /**
         Static method to obtain the singleton.
         \return Single instance of the StatisticsManager class.
        **/
        static StatisticsManager &
        GetStatisticsManager( void );
    
        /**
         This function is called to notify a measurement is generated. The
         measurement is stored for statistical purposes in ID based maps.
         \param measurement Generated measurement.
        **/
        void
        MeasurementGenerated( const TMeasurementPtr & measurement );
    
        /**
         This function is called to notify a measurement is received. The
         measurement is stored for statistical purposes in ID based maps.
         \param measurement Received measurement.
         **/
        void
        MeasurementReceived( const TMeasurementPtr & measurement );
    
        /**
         This function is called when a packet is transmitted. The internal
         counters are increased for statistical purposes.
         \param transmittingNode Pointer to the transmitting node.
        **/
        void
        PacketTransmitted( TNodePtr & transmittingNode );
    
        /**
         This function is called when a packet is received. Since the receiver
         can only be sink, no input is required.
        **/
        void
        PacketReceived( void );
    
        /**
         Prints statistics to the console and to a file.
        **/
        void
        PrintStatistics( void );
    
        /**
         Sets the name of the log file.
         \param logFileName Name of the log file.
        **/
        void
        SetLogFileName( const std::string & logFileName )
        {
            this->m_logFileName = logFileName;
        }
    
        /**
         Configures the timeseries writing preference.
         \param timeSeries Whether to write to the timeseries file.
        **/
        void
        SetTimeseriesPreference( const bool timeSeries )
        {
            this->m_writeTimeseries = timeSeries;
        }
};

#endif /* StatisticsManager_hpp */
