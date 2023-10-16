
#include "ProcModule.h"

#include "RtcClock.h"

#include "GravityComponent.h"
#include "MassPropertiesComponent.h"
#include "EngineComponent.h"
#include "ControlSurfacesComponent.h"
#include "GRAMComponent.h"
#include "AeroComponent.h"
#include "EomComponent.h"
#include "ImuComponent.h"

#include "NavigationComponent.h"
#include "GuidanceComponent.h"
#include "AutopilotComponent.h"

#include <iostream>

ProcModule::ProcModule()
    : Module()
    , pRtcClock           ( new TimePt::RtcClock( m_time ) )
    , navThread           ()
    , guidanceThread      ()
    , autopilotThread     ()
    , pGravityComponent   ( new GravityComponent        ( m_queueMngr ) )
    , pMassPropComponent  ( new MassPropertiesComponent ( m_queueMngr ) )
    , pEngineComponent    ( new EngineComponent         ( m_queueMngr ) )
    , pCtrlSurfComponent  ( new ControlSurfacesComponent( m_queueMngr, pRtcClock ) )
    , pGRAMComponent      ( new GRAMComponent           ( m_queueMngr, pRtcClock ) )
    , pEomComponent       ( new EomComponent            ( m_queueMngr, pRtcClock ) )
    , pImuComponent       ( new ImuComponent            ( m_queueMngr, pRtcClock ) )
    , pAeroComponent      ( new AeroComponent           ( m_queueMngr, pRtcClock ) )
    , pNavigationComponent( new NavigationComponent     ( m_queueMngr, pRtcClock ) )
    , pGuidanceComponent  ( new GuidanceComponent       ( m_queueMngr, pRtcClock ) )
    , pAutopilotComponent ( new AutopilotComponent      ( m_queueMngr, pRtcClock ) )
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

    addSimComp( pEngineComponent.get() );
    addSimComp( pCtrlSurfComponent.get() );
    addSimComp( pGRAMComponent.get() );
    addSimComp( pAeroComponent.get() );
    addSimComp( pMassPropComponent.get() );
    addSimComp( pGravityComponent.get() );
    addSimComp( pEomComponent.get() );
    addSimComp( pImuComponent.get() );

    std::cout << "Initializing" << std::endl;
    initialize();

    int i = 0;

    for ( i = 0; i < 5000; i++ )
    {
        start();
    }

    stop();
}