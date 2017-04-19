//
//  main.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/8/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "Simulation.hpp"

/** \mainpage Optimal Aggregation ns3 Simulation Code
 This code defines multiple transmission manager implementations, including our
 optimal versions. The user doesn't have to change the code, unless a new
 implementation is required. Please use the configuration files to implement
 scenarios.
 
 \section Code Structure
 The code structure consists of TransmissionManager classes that control the
 aggregation times of each node. Each manager has multiple Application class
 instances defining data streams. Every Application has a DeadlineProcess for
 deadline assignments, a GenerationProcess for data generation and a
 GainFunction for optimization purposes. Also, each TransmissionManager has a
 Packet level GainFunction that is applied to all Application instances.
 The user can implement more GainFunction algorithms, DeadlineProcess and
 GenerationProcess codes. The GainConfigureHelper, GenerationConfigureHelper and
 DeadlineConfigureHelper must be updated accordingly.
 
 \section Contact
 For any bugs, suggestions or copy/modification/usage requests, email me at
 aakyurek@ucsd.edu. This code has been implemented by Alper Sinan Akyurek in
 part as an NSF project. Please provide proper citation if you will be using any
 part of the code.
**/

/**
 Creates a new Simulation instance and runs it.
 \param argc Number of arguments.
 \param argv All arguments.
**/
int
main( int argc, char * argv[] )
{
    srand( ( unsigned int )time( NULL ) );
    std::cout << "================////////////////=================" << std::endl;
    
    Simulation* mainSimulation = new Simulation();
    mainSimulation->Configure( argc, argv );
    mainSimulation->Run();
    delete mainSimulation;
    
    return ( 0 );
}
