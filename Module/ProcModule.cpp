
#include "ProcModule.h"

#include "EomComponent.h"
#include "NavigationComponent.h"
#include "GuidanceComponent.h"
#include "AutopilotComponent.h"

#include <iostream>

ProcModule::ProcModule() : Module(),
                           navThread(),
                           pEomComponent(new EomComponent(m_queueMngr)),
                           pNavigationComponent(new NavigationComponent(m_queueMngr)),
                           pGuidanceComponent(new GuidanceComponent(m_queueMngr)),
                           pAutopilotComponent(new AutopilotComponent(m_queueMngr))
{
}

ProcModule::~ProcModule()
{
}

void ProcModule::launch()
{
    addThread(navThread);

    addCompToThread(pNavigationComponent.get());

    addThread(guidanceThread);

    addCompToThread(pGuidanceComponent.get());

    addThread(autopilotThread);

    addCompToThread(pAutopilotComponent.get());

    addSimComp(pEomComponent.get());

    std::cout << "Initializing" << std::endl;
    initialize();

    int i = 0;

    for (i = 0; i < 10; i++)
    {
        start();
    }

    stop();
}