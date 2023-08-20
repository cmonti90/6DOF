
#include "EomComponent.h"
#include "EomTypes.h"

#include "eom.h"

EomComponent::EomComponent( std::shared_ptr<PubSub::QueueMngr> queueMngr, const PubSub::COMPONENT_LABEL name )
    : PubSub::SimComponent( queueMngr, 1000, name ), pAlg( new eom() ), inData_(new EomTypes::InData()), outData_(new EomTypes::OutData()), counter_( 0u )
{
}

EomComponent::~EomComponent()
{
}

void EomComponent::initialize( void )
{

    subscribe<AeroMsg>( *inData_, PubSub::Message_Type::ACTIVE );

    // pAlg->initialize();
    counter_ = 0u;
}

void EomComponent::update( void )
{

    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while (status == PubSub::MessageStatus::MESSAGE_AVAILABLE)
    {
        switch (label)
        {
        case AeroMsg::MESSAGE_LABEL:
            receive<AeroMsg>( *inData_ );
            pAlg->addForces( myMath::Vector3d( inData_->AeroData::force ) );
            pAlg->addMoments( myMath::Vector3d( inData_->AeroData::moment ) );

            break;

        default:
            removeTopMessage();
            break;
        }

        status = peek( label );
    }

    // pAlg->exec();

    counter_++;
}

void EomComponent::finalize( void )
{
    pAlg->finalize();
}