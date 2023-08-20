#ifndef D870534D_1B82_4645_B89B_01FBA4A92BFB
#define D870534D_1B82_4645_B89B_01FBA4A92BFB

#include "Table1D.h"

namespace AeroTables
{

    class AltitudeTable : public Table1D<double>
    {
    public:
        AltitudeTable(const double *data) : Table1D<double>(data) {}
        virtual ~AltitudeTable() {}

        const double startPoint = -2000.0;
        const double stepSize = 500.0;

        double lookUp(const double x) const override
        {
            double value{0.0};
            double idx = (x - startPoint) / stepSize;

            if (idx < 0.0)
            {
                value = extrapolate(x, startPoint, m_data[0], (m_data[1] - m_data[0]) / stepSize);
            }
            else if (idx >= static_cast<double>(m_size - 1u))
            {
                value = extrapolate(x, startPoint + static_cast<double>(m_size - 1) * stepSize, m_data[m_size - 1], (m_data[m_size - 1] - m_data[m_size - 2]) / stepSize);
            }
            else if ((static_cast<double>(static_cast<int>(idx)) - idx) == 0.0)
            {
                value = m_data[static_cast<int>(idx)];
            }
            else
            {
                interpolate(idx, static_cast<double>(static_cast<int>(idx)), x, stepSize);
            }

            return value;
        }
    };

    constexpr double density[] =
        {
            /*ft        kg/cm3*/
            /*-2000*/ 1.11,
            /*-1500*/ 1.09,
            /*-1000*/ 1.07,
            /*-500 */ 1.05,
            /*0    */ 1.03,
            /*500  */ 1.01,
            /*1000 */ 0.997,
            /*1500 */ 0.979,
            /*2000 */ 0.961,
            /*2500 */ 0.943,
            /*3000 */ 0.926,
            /*3500 */ 0.909,
            /*4000 */ 0.893,
            /*4500 */ 0.876,
            /*5000 */ 0.860,
            /*6000 */ 0.828,
            /*7000 */ 0.797,
            /*8000 */ 0.768,
            /*9000 */ 0.739,
            /*10000*/ 0.711,
            /*15000*/ 0.583,
            /*20000*/ 0.475,
            /*25000*/ 0.384,
            /*30000*/ 0.307,
            /*35000*/ 0.243,
            /*40000*/ 0.191,
            /*45000*/ 0.148,
            /*50000*/ 0.113};

    static const AltitudeTable densityTable(density);

    constexpr double pressure[] =
        {
            /*ft        kPa*/
            /*-2000*/ 109.0,
            /*-1500*/ 107.0,
            /*-1000*/ 105.0,
            /*-500 */ 103.0,
            /*0    */ 101.0,
            /*500  */ 99.5,
            /*1000 */ 97.7,
            /*1500 */ 96.0,
            /*2000 */ 94.2,
            /*2500 */ 92.5,
            /*3000 */ 90.8,
            /*3500 */ 89.1,
            /*4000 */ 87.5,
            /*4500 */ 85.9,
            /*5000 */ 84.3,
            /*6000 */ 81.2,
            /*7000 */ 78.2,
            /*8000 */ 75.3,
            /*9000 */ 72.4,
            /*10000*/ 69.7,
            /*15000*/ 57.2,
            /*20000*/ 46.6,
            /*25000*/ 37.6,
            /*30000*/ 30.1,
            /*35000*/ 23.8,
            /*40000*/ 18.7,
            /*45000*/ 14.5,
            /*50000*/ 11.1};

    static const AltitudeTable pressureTable(pressure);

} // namespace AeroTables

#endif /* D870534D_1B82_4645_B89B_01FBA4A92BFB */
