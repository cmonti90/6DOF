#ifndef D870534D_1B82_4645_B89B_01FBA4A92BFB
#define D870534D_1B82_4645_B89B_01FBA4A92BFB

#include "Table1D.h"

namespace AeroTables
{

    constexpr double alt[] =
        {/*m*/
         -1000,
         0.0,
         1000.0,
         2000.0,
         3000.0,
         4000.0,
         5000.0,
         6000.0,
         7000.0,
         8000.0,
         9000.0,
         10000.0,
         15000.0,
         20000.0,
         25000.0,
         30000.0,
         40000.0,
         50000.0,
         60000.0,
         70000.0,
         80000.0};

    constexpr double temperature[] =
        {
            /*deg C*/
            21.50,
            15.00,
            8.50,
            2.00,
            -4.49,
            -10.98,
            -17.47,
            -23.96,
            -30.45,
            -36.94,
            -43.42,
            -49.90,
            -56.50,
            -56.50,
            -51.60,
            -46.64,
            -22.80,
            -2.5,
            -26.13,
            -53.57,
            -74.51,
    };

    static const Table1D<double> temperatureTable(alt, temperature);

    constexpr double density[] =
        {
            /*kg/m3*/
            1.347,
            1.225,
            1.112,
            1.007,
            0.9093,
            0.8194,
            0.7364,
            0.6601,
            0.5900,
            0.5258,
            0.4671,
            0.4135,
            0.1948,
            0.08891,
            0.04008,
            0.01841,
            0.003996,
            0.001027,
            0.0003097,
            0.00008283,
            0.00001846};

    static const Table1D<double> densityTable(alt, density);

    constexpr double pressure[] =
        {
            /*kPa*/
            113.9,
            101.3,
            89.88,
            79.50,
            70.12,
            61.66,
            54.05,
            47.22,
            41.11,
            35.65,
            30.80,
            26.50,
            12.11,
            0.05529,
            0.02549,
            0.01197,
            0.00287,
            0.0007978,
            0.0002196,
            0.000052,
            0.000011};

    static const Table1D<double> pressureTable(alt, pressure);

    double viscosity[] =
        {
            /*N*sec/m2*/
            1.821e-5,
            1.789e-5,
            1.758e-5,
            1.726e-5,
            1.694e-5,
            1.661e-5,
            1.628e-5,
            1.595e-5,
            1.561e-5,
            1.527e-5,
            1.493e-5,
            1.458e-5,
            1.422e-5,
            1.422e-5,
            1.448e-5,
            1.475e-5,
            1.601e-5,
            1.704e-5,
            1.584e-5,
            1.438e-5,
            1.321e-5};

    static const Table1D<double> viscosityTable(alt, viscosity);

} // namespace AeroTables

#endif /* D870534D_1B82_4645_B89B_01FBA4A92BFB */
