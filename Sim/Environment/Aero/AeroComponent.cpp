
#include "AeroComponent.h"
#include "AeroTypes.h"

#include "Aero.h"
#include "RtcClock.h"

AeroComponent::AeroComponent( std::shared_ptr<PubSub::QueueMngr>& queueMngr,
                              const std::shared_ptr<TimePt::RtcClock>& sysClock,
                              const PubSub::Component_Label name )
    : PubSub::SimComponent( queueMngr, 1000, name )
    , pAlg      ( new Aero() )
    , inData_   ( new AeroTypes::InData() )
    , outData_  ( new AeroTypes::OutData() )
    , sysClock_ ( sysClock )
    , counter_  ( 0u )
{
}

AeroComponent::~AeroComponent()
{
}

void AeroComponent::initialize( void )
{
    inData_ ->initialize();
    outData_->initialize();

    subscribe< CtrlSurfMsg >( *inData_ );
    subscribe< EomMsg      >( *inData_ );
    subscribe< GRAMMsg     >( *inData_ );

    pAlg->initialize();
    counter_ = 0u;
}

void AeroComponent::update()
{
    PubSub::Message_Label label;
    PubSub::MessageStatus status = peek( label );

    while ( status == PubSub::MessageStatus::MESSAGE_AVAILABLE )
    {
        switch ( label )
        {
            case EomMsg::MESSAGE_LABEL:
                
                receive< EomMsg >( *inData_ );

                break;

            case CtrlSurfMsg::MESSAGE_LABEL:
                
                receive< CtrlSurfMsg >( *inData_ );
                
                break;

            default:
                
                removeTopMessage();
                
                break;
        }

        status = peek( label );
    }

    // pAlg->exec(*inData_, *outData_);

    send<AeroMsg>( *outData_ );

    counter_++;
}

void AeroComponent::finalize( void )
{
    pAlg->finalize();
}