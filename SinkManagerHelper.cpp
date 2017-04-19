//
//  SinkManagerHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/12/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "SinkManagerHelper.hpp"

void
SinkManagerHelper::Install( TNodePtr node ) const
{
    ns3::ObjectFactory sinkManagerFactory;
    ns3::TypeId sinkManagerTypeId = ns3::TypeId::LookupByName( "SinkManager" );
    sinkManagerFactory.SetTypeId( sinkManagerTypeId );
    ns3::Ptr< ns3::Object > sinkManager = sinkManagerFactory.Create< ns3::Object > ();
    node->AggregateObject( sinkManager );
    ns3::DynamicCast< SinkManager >( sinkManager )->InstallOnNode( node );
}

void
SinkManagerHelper::Install( ns3::NodeContainer c ) const
{
    for ( ns3::NodeContainer::Iterator i = c.Begin (); i != c.End (); ++i )
    {
        this->Install( *i );
    }
}
