//
//  ConstantDeadlineProcess.hpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#ifndef ConstantDeadlineProcess_hpp
#define ConstantDeadlineProcess_hpp

#include "DeadlineProcess.hpp"

/**
 Constant deadline implementation. It uses a constant value for all packets.
**/
class ConstantDeadlineProcess : public DeadlineProcess
{
    public:
        /**
         Constructor to pass the expected deadline to the base class.
         \param value Expected deadline value.
        **/
        ConstantDeadlineProcess( const TDeadline value );
    
        /**
         Returns the same deadline constantly.
         \return Constant deadline value.
        **/
        TDeadline
        GetNextDeadline( void ) const;
};

#endif /* ConstantDeadlineProcess_hpp */
