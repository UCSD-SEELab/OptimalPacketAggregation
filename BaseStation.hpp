//
//  BaseStation.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef BaseStation_hpp
#define BaseStation_hpp

#include "GainFunction.hpp"
#include <vector>

/**
 Implements the smart Base Station for the 5G case with the capability of
 negotiating the C values.
**/
class BaseStation
{
    public:
        /** C Value type **/
        typedef GainFunction::TGain TCValue;
    
        /** Gain value type **/
        typedef GainFunction::TGain TResponse;
    
        /** Number of nodes in the network **/
        typedef unsigned int TNumberOfNodes;
    
        /** The C Values used during negotiations in a vector **/
        typedef std::vector<TCValue> TCValueVector;
    
        /** The response vector for each C Values **/
        typedef std::vector<TResponse> TResponseVector;
    
        /** Number type for iteration statistics. **/
        typedef unsigned int TIterationNumber;
    
    private:
        /** Minimum C Value for the iterations. **/
        TCValue m_CValueMinimum;
    
        /** Maximum C Values for the iterations. **/
        TCValue m_CValueMaximum = 100;
    
        /** Resolution for the iterations. **/
        TCValue m_CValueResolution = 0.1;

        /** The response vector from all nodes to the C values **/
        TResponseVector m_responseVector;
    
        /** Current Optimal C Value as a result of negotiations. **/
        TCValue m_optimalCValue;
    
        /** Number of Nodes in the Network **/
        TNumberOfNodes m_numberOfNodes;
    
        /** Alpha parameter in the algorithm **/
        TResponse m_alpha;
    
        /** Determines whether a static or dynamic Alpha value is used. **/
        bool m_useDynamicAlpha;
    
        /** Number of update broadcasts. **/
        TIterationNumber m_numberOfBroadcasts = 0;
    
        /** Number of updated responses. **/
        TIterationNumber m_numberOfUpdates = 0;
    
        /** Indicates whether updates from nodes have an effect. **/
        bool m_updateEnabled = true;
    
    public:
        /**
         C Value vector used for negotiations. This would normally be sent OTA
         to the negotiating nodes. Used a public variable for simple
         implementation.
        **/
        TCValueVector cVector;
    
    private:
        /**
         Creates the initial C Value vector
        **/
        BaseStation( void );
    
        /**
         Reads the configuration of C values from "baseStation.txt" file.
        **/
        void
        ReadConfiguration ( void );
    
        /**
         For a C Value vector index, get the gain value response from the
         negotiating node.
         \param index C Value vector index to be used for Gain value calculation
         by the node.
         \return The gain value response of the node.
        **/
        TResponse
        GetError( const TResponseVector::size_type index ) const;
    
    public:
        /**
         Returns the single instance of the BaseStation class.
         \return Single instance of BaseStation.
        **/
        static
        BaseStation &
        GetBaseStation( void );
    
        /**
         Used to register a new incoming node. The node published its gain value
         responses and optains the result of the negotiation C Value.
         \param responses Gain value vector response to the C Values.
         \return Optimal C Value of the negotiation.
        **/
        TCValue &
        RegisterMe( const TResponseVector & responses );
    
        /**
         Returns the Optimal C Value.
         \return Optimal C Value.
        **/
        TCValue &
        GetOptimalCValue( void )
        {
            return ( this->m_optimalCValue );
        }
    
        /**
         Updates responses so the the base station can calculate optimal
         solution.
         \param deltaResponses New Responses - OldResponses
        **/
        void
        UpdateResponses( const TResponseVector & deltaResponses );
    
        /**
         Returns the number of update broadcasts.
         \return Number of broadcasts of C values.
        **/
        TIterationNumber
        GetNumberOfBroadcasts( void ) const
        {
            return ( this->m_numberOfBroadcasts );
        }
    
        /**
         Returns the number of update requests for C values.
         \return Number of C value update requests.
        **/
        TIterationNumber
        GetNumberOfUpdateRequests( void ) const
        {
            return ( this->m_numberOfUpdates );
        }
};

#endif /* BaseStation_hpp */
