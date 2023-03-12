#include "Navigation.h"

#include <cmath>

void Nav::getNavReferences(TimeMngr *ref)
{
    pTimeMngr_ = ref;
}

void Nav::initialize(void)
{
    counter = 0;
}

void Nav::exec(void)
{
    myMath::Matrix3d test{0.0};
    myMath::Matrix3d LUtest{0.0};
    myMath::Matrix3d Ltest{0.0};
    myMath::Matrix3d Utest{0.0};

    test[0][0] = 1;
    test[0][1] = 2;
    test[0][2] = 3;

    test[1][0] = 4;
    test[1][1] = 5;
    test[1][2] = 6;

    test[2][0] = 7;
    test[2][1] = 8;
    test[2][2] = 9;

    test.LU_Decomposition(Ltest, Utest);

    printf("\nL+U+I = \n");

    for (unsigned int i{0u}; i < 3u; i++)
    {
        for (unsigned int j{0u}; j < 3u; j++)
        {
            printf("%f, ", LUtest[i][j]);
        }

        printf("\n");
    }

    printf("\nL = \n");

    // printf("%f, ", Ltest[0][1]);
    // printf("%f, ", Ltest[0][1]);
    // printf("%f, ", Ltest[0][2]);
    // printf("%f, ", Ltest[1][0]);
    // printf("%f, ", Ltest[1][1]);
    // printf("%f, ", Ltest[1][2]);
    // printf("%f, ", Ltest[2][0]);
    // printf("%f, ", Ltest[2][1]);
    // printf("%f, ", Ltest[2][2]);

    for (unsigned int i{0u}; i < 3u; i++)
    {
        for (unsigned int j{0u}; j < 3u; j++)
        {
            printf("%f, ", Ltest[i][j]);
        }

        printf("\n");
    }

    printf("\nU = \n");

    for (unsigned int i{0u}; i < 3u; i++)
    {
        for (unsigned int j{0u}; j < 3u; j++)
        {
            printf(" %f", Utest[i][j]);
        }

        printf("\n");
    }
}

void Nav::setEncoderOutput(const double encThetadot)
{
}

/*
void Nav::setImuOutput(double& imuXdotdot, double& imuYdotdot, double& imuZdotdot)
{

}*/

void Nav::Filter()
{
    extendedKalFilt();
}

void Nav::kalFilt()
{
    // prediction
    stateVec_k_k1 = kfF * stateVec_k1_k1 + kfB * u;
    kfPk_k1 = kfF * kfPk1_k1 * myMath::Transpose(kfF) + kfQ;

    // error
    yTilda = z - kfH * stateVec_k_k1;

    kfS = kfH * kfPk_k1 * myMath::Transpose(kfH) + kfR;

    // update Kalman gain
    // kfK = kfPk_k1 * kfH.Transpose() * kfS.Inverse();

    // update estimates
    stateVec_k1_k1 = stateVec_k_k1 + kfK * yTilda;
    kfPk1_k1 = (kfPk1_k1.Identity() - kfK * kfH) * kfPk_k1;
}

void Nav::extendedKalFilt()
{
    ekfPtk_k = Phi(time, tk_1) * ekfPtk_k * Phi(time, tk_1).Transpose() + integralTermEKF(tk_1, time);

    myMath::Matrix2d ekfK_invTerm = ekfH * ekfPtk_k1 * ekfH.Transpose() + ekfR;
    // ekfK = ekfPtk_k1 * ekfH.Transpose() * ekfK_invTerm.Inverse();

    ekfStateVec_tk_k = ekfStateVec_tk_k1 + ekfK * (ekfZ - hVecEKF(ekfStateVec_tk_k1));
    ekfPtk_k = (ekfPtk_k.Identity() - ekfK * ekfH) * ekfPtk_k1;

    ekfPtk1_k1 = ekfPtk_k;
}

myMath::Vector<double, 4> Nav::fVecEKF(myMath::Vector<double, 4> &stateVec)
{
    myMath::Vector<double, 4> f_vec;

    f_vec[0] = 0.0;
    f_vec[1] = 0.0;
    f_vec[2] = 0.0;
    f_vec[3] = 0.0;

    return f_vec;
}

myMath::Vector<double, 2> Nav::hVecEKF(myMath::Vector<double, 4> &stateVec)
{
    myMath::Vector<double, 2> h_vec;

    h_vec[0] = 0.0;
    h_vec[1] = 0.0;

    return h_vec;
}

myMath::Matrix4d Nav::AmatrixEKF(myMath::Vector<double, 4> &stateVec)
{
    myMath::Matrix4d A_mat;

    // differentiate with respect to:
    // [][0] = theta
    // [][1] = thetadot
    // [][2] = xb
    // [][3] = xbdot

    // deriv of thetadot state eqn
    A_mat[0][0] = 0.0;
    A_mat[0][1] = 1.0;
    A_mat[0][2] = 0.0;
    A_mat[0][3] = 0.0;

    // deriv of thetadotdot state eqn
    A_mat[1][0] = ((((mb + mr) * mr * g * Len - std::pow(mr * Len * stateVec[1], 2)) * std::sin(stateVec[0])) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)))) + (((std::pow(mr * Len * stateVec[1], 2) * std::cos(stateVec[0]) + mr * Len * Ff + (mb + mr) * Mf + (mb + mr) * mr * Len * g * std::cos(stateVec[0]) + mr * Len * u[0]) * std::pow(mr * Len, 2) * std::cos(stateVec[0])) / std::pow((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0])), 2));

    A_mat[1][1] = (2.0 * std::pow(mr * Len, 2) * stateVec[1] * std::cos(stateVec[0])) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)));
    A_mat[1][2] = 0.0;
    A_mat[1][3] = 0.0;

    // deriv of xbdot state eqn
    A_mat[2][0] = 0.0;
    A_mat[2][1] = 0.0;
    A_mat[2][2] = 0.0;
    A_mat[2][3] = 1.0;

    // deriv of xbdotdot state eqn
    A_mat[3][0] = (-mr * Len * std::pow(mr * Len * stateVec[1] * std::cos(stateVec[0]), 2) / (std::pow(mb + mr, 2) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)))) - ((mr * Len * std::pow(stateVec[1], 2) * std::sin(stateVec[0]) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)) - std::pow(mr * Len, 3) / (mb + mr)) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)))) - (((std::pow(mr * Len * stateVec[1] * std::cos(stateVec[0]), 2) / (mb + mr)) * (mr * Len * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)) - std::pow(mr * Len, 3) / (mb + mr))) / ((mb + mr) * std::pow(I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr), 2))) - ((std::pow(mr * Len, 2) * g * std::sin(stateVec[0]) + Ff * std::pow(mr * Len, 2) / (mb + mr)) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)))) + (((std::pow(mr * Len, 2) * std::cos(stateVec[0]) / (mb + mr)) * std::pow(mr * Len, 2) * g * std::cos(stateVec[0]) + mr * Len * Mf + Ff * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr))) / (std::pow((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)), 2)));

    A_mat[3][1] = (2.0 * mr * Len * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)) - 2.0 * std::pow(mr * Len, 3) / (mb + mr)) * stateVec[1] * std::cos(stateVec[0]) / ((mb + mr) * (I + mr * std::pow(Len, 2) - std::pow(mr * Len, 2) * std::sin(stateVec[0]) / (mb + mr)));
    A_mat[3][2] = 0.0;
    A_mat[3][3] = 0.0;

    return A_mat;
}

myMath::Matrix<double, 2, 4> Nav::HmatrixEKF(myMath::Vector<double, 4> &stateVec)
{
    myMath::Matrix<double, 2, 4> H_mat;
    myMath::Matrix4d A_mat = AmatrixEKF(stateVec);

    H_mat[0][0] = 1.0;
    H_mat[0][1] = 0.0;
    H_mat[0][2] = 0.0;
    H_mat[0][3] = 0.0;

    H_mat[1] = A_mat[3];

    return H_mat;
}

myMath::Matrix4d Nav::Phi(double t, double tau)
{
    myMath::Matrix4d phi{0.0};

    return phi;
}

myMath::Matrix4d Nav::integralTermEKF(double t0, double tf)
{
    double stepSize = 1e-6;

    myMath::Matrix4d result{0.0};

    for (double t{t0 + stepSize}; t < tf; t += stepSize)
    {
        result += 0.5 * stepSize * (Phi(time, t) * ekfG * ekfQ * ekfG.Transpose() * Phi(time, t).Transpose() - Phi(time, t - stepSize) * ekfG * ekfQ * ekfG.Transpose() * Phi(time, t - stepSize).Transpose());
    }

    return result;
}

void Nav::unscentedKalFilt()
{
}
