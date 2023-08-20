
#include "ProcModule.h"

#include "RtcClock.h"

#include "MassPropertiesComponent.h"
#include "EngineComponent.h"
#include "AeroComponent.h"
#include "EomComponent.h"

#include "NavigationComponent.h"
#include "GuidanceComponent.h"
#include "AutopilotComponent.h"

#include <iostream>

ProcModule::ProcModule() : Module(),
pRtcClock( new TimePt::RtcClock( m_time ) ),
navThread(),
guidanceThread(),
autopilotThread(),
pMassPropComponent( new MassPropertiesComponent( m_queueMngr ) ),
pEngineComponent( new EngineComponent( m_queueMngr ) ),
pEomComponent( new EomComponent( m_queueMngr ) ),
pAeroComponent( new AeroComponent( m_queueMngr ) ),
pNavigationComponent( new NavigationComponent( m_queueMngr ) ),
pGuidanceComponent( new GuidanceComponent( m_queueMngr ) ),
pAutopilotComponent( new AutopilotComponent( m_queueMngr ) )
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

    addSimComp( pMassPropComponent.get() );
    addSimComp( pEngineComponent.get() );
    addSimComp( pEomComponent.get() );
    addSimComp( pAeroComponent.get() );

    std::cout << "Initializing" << std::endl;
    initialize();

    int i = 0;

    for (i = 0; i < 10; i++)
    {
        start();
    }

    stop();
}