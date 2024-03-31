
#include "ProcModule.h"

#include "RtcClock.h"

#include "NavigationComponent.h"
#include "GuidanceComponent.h"
#include "AutopilotComponent.h"

#include <iostream>

ProcModule::ProcModule( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
    : Module( queueMngr )
    , pRtcClock           ( new TimePt::RtcClock    ( m_time ) )
    , navThread           ( "NavigationThread" )
    , guidanceThread      ( "GuidanceThread" )
    , autopilotThread     ( "AutopilotThread" )
    , pNavigationComponent( new NavigationComponent ( queueMngr, pRtcClock ) )
    , pGuidanceComponent  ( new GuidanceComponent   ( queueMngr, pRtcClock ) )
    , pAutopilotComponent ( new AutopilotComponent  ( queueMngr, pRtcClock ) )
{
}

ProcModule::~ProcModule()
{
}

void ProcModule::launch()
{
    RegisterThread( navThread );
    AddCompToThread( navThread, pNavigationComponent.get() );

    RegisterThread( guidanceThread );
    AddCompToThread( guidanceThread, pGuidanceComponent.get() );

    RegisterThread( autopilotThread );
    AddCompToThread( autopilotThread, pAutopilotComponent.get() );
}