//
//  TransmissionManagerHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "TransmissionManagerHelper.hpp"

void
TransmissionManagerHelper::Install( const TAddress & sinkNode, TNodePtr node, const TTransmissionManagerName & name ) const
{
    ns3::ObjectFactory transmissionManagerFactory;
    ns3::TypeId transmissionManagerTypeId = ns3::TypeId::LookupByName( name );
    transmissionManagerFactory.SetTypeId( transmissionManagerTypeId );
    ns3::Ptr< ns3::Object > transmissionManager = transmissionManagerFactory.Create< ns3::Object > ();
    node->AggregateObject( transmissionManager );
    ns3::DynamicCast< TransmissionManager >( transmissionManager )->InstallOnNode( node );
    ns3::DynamicCast< TransmissionManager >( transmissionManager )->SetSinkAddress( sinkNode );
    ns3::DynamicCast< TransmissionManager >( transmissionManager )->ReadConfiguration();
    ns3::DynamicCast< TransmissionManager >( transmissionManager )->Start();
}

void
TransmissionManagerHelper::Install( const TAddress & sinkNode, ns3::NodeContainer c, const TTransmissionManagerName & name ) const
{
    for ( ns3::NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i )
    {
        this->Install( sinkNode, *i, name );
    }
}