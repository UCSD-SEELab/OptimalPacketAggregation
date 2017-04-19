//
//  GainConfigureHelper.cpp
//  AggregationNS3
//
//  Created by Alper Sinan Akyurek on 8/21/16.
//  Copyright © 2016 Alper Sinan Akyurek. All rights reserved.
//

#include "GainConfigureHelper.hpp"

Application::TGainFunctionPtr
GainConfigureHelper::Configure( std::ifstream & conf )
{
    TGainFunctionId gainId;
    if ( !( conf >> gainId ) )
    {
        class GainIdFailed{};
        throw GainIdFailed();
    }
    
    Application::TGainFunctionPtr gainFunction;
    
    if ( gainId == EnergyId )
    {
        gainFunction = ns3::Create<EnergyGainFunction>();
    }
    else if ( gainId == InformationFreshnessId )
    {
        gainFunction = ns3::Create<InformationFreshnessGainFunction>();
    }
    else if ( gainId == SuccessId )
    {
        gainFunction = ns3::Create<SuccessGainFunction>();
    }
    else if ( gainId == CongestionId )
    {
        gainFunction = ns3::Create<CongestionGainFunction>();
    }
    else if ( gainId == SuccessUniformId )
    {
        gainFunction = ns3::Create<SuccessUniformGainFunction>();
    }
    else
    {
        gainFunction = ns3::Create<NoGainFunction>();
    }
    
    return ( gainFunction );
}