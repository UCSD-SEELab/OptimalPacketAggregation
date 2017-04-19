//
//  ConstantDeadlineProcess.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "ConstantDeadlineProcess.hpp"

ConstantDeadlineProcess::ConstantDeadlineProcess( const TDeadline value ) : DeadlineProcess( value )
{
}

ConstantDeadlineProcess::TDeadline
ConstantDeadlineProcess::GetNextDeadline( void ) const
{
    return ( this->m_expectedDeadline );
}