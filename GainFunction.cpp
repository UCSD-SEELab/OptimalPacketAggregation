//
//  GainFunction.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/9/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "GainFunction.hpp"

void
GainFunction::SetProcesses( const TGenerationPtr & gen,
                            const TDeadlinePtr & deadline )
{
    this->m_generationProcess = gen;
    this->m_deadlineProcess = deadline;
}