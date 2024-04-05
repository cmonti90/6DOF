
#include "HighRateDigitalFilter2.h"

HighRateDigitalFilter2::HighRateDigitalFilter2()
    : input_ ( 0.0f )
    , output_( 0.0f )
    , num_   ()
    , den_   ()
    , state_ ()
{
    SetDefaults();
}

HighRateDigitalFilter2::~HighRateDigitalFilter2()
{
}

const float* HighRateDigitalFilter2::GetNum() const
{
    return num_;
}

const float* HighRateDigitalFilter2::GetDen() const
{
    return den_;
}

void HighRateDigitalFilter2::SetState( const float inState0,
                                       const float inState1,
                                       const float inState2,
                                       const float inState3,
                                       const float inState4 )
{
    state_[0] = inState0;
    state_[1] = inState1;
    state_[2] = inState2;
    state_[3] = inState3;
    state_[4] = inState4;
}

void HighRateDigitalFilter2::SetDefaults()
{
    num_[0] = 0.0f;
    num_[1] = 0.0f;
    num_[2] = 0.0f;

    den_[0] = 0.0f;
    den_[1] = 0.0f;

    state_[0] = 0.0f;
    state_[1] = 0.0f;
    state_[2] = 0.0f;
    state_[3] = 0.0f;
    state_[4] = 0.0f;

    input_  = 0.0f;
    output_ = 0.0f;
}

void HighRateDigitalFilter2::SetCoefficients( const float* inNum, const float* inDen )
{
    num_[0] = inNum[0];
    num_[1] = inNum[1];
    num_[2] = inNum[2];

    den_[0] = inDen[0];
    den_[1] = inDen[1];
}


//-----------------------------------------------------------------------
// Function:    Update
// Description: Update the filter with a new input value using the transfer
//              function:
//
//                      Y(z)     n0 - n1*z^-1 - n2*z^-2
//              G(z) = ------ = ------------------------
//                      U(z)     1  + d0*z^-1 + d1*z^-2
//
//              State Equation:
//              x(k) = u(k) + d0*x(k-1) + d1*u(k-2)
//
//              Output Equation:
//              y(k) = n0*x(k) + n1*x(k-1) + n2*x(k-2)
//
//-----------------------------------------------------------------------
float HighRateDigitalFilter2::Update( const float inU )
{
    input_ = inU;

    state_[0] = input_ - den_[0] * state_[1] - den_[1] * state_[2];

    output_ = num_[0] * state_[0]
              + num_[1] * state_[1]
              + num_[2] * state_[2];

    state_[2] = state_[1];
    state_[1] = state_[0];

    return output_;
}