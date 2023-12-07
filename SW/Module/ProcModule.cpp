
#include "ProcModule.h"

#include "RtcClock.h"

#include "NavigationComponent.h"
#include "GuidanceComponent.h"
#include "AutopilotComponent.h"

#include <iostream>

ProcModule::ProcModule( std::shared_ptr< PubSub::QueueMngr >& queueMngr )
    : Module( queueMngr )
    , pRtcClock           ( new TimePt::RtcClock( m_time ) )
    , navThread           ()
    , guidanceThread      ()
    , autopilotThread     ()
    , pNavigationComponent( new NavigationComponent     ( queueMngr, pRtcClock ) )
    , pGuidanceComponent  ( new GuidanceComponent       ( queueMngr, pRtcClock ) )
    , pAutopilotComponent ( new AutopilotComponent      ( queueMngr, pRtcClock ) )
{
}

ProcModule::~ProcModule()
{
}

void ProcModule::launch()
{
    addThread( navThread );
    addCompToThread( pNavigationComponent.get() );

    addThread( guidanceThread );
    addCompToThread( pGuidanceComponent.get() );

    addThread( autopilotThread );
    addCompToThread( pAutopilotComponent.get() );
}