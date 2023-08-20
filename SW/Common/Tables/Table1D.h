#ifndef AFAE9597_1EDD_409F_B906_60DFE541C1A1
#define AFAE9597_1EDD_409F_B906_60DFE541C1A1

template <typename T>
class Table1D
{
public:
    Table1D(const T *data) : m_data(data),
                             m_size(sizeof(data) / sizeof(T))
    {
    }

    virtual ~Table1D() {}

    T operator[](const unsigned int index) const
    {
        return m_data[index];
    }

    virtual T lookUp(const T x) const = 0;

    T interpolate(const double idx, const T baseX, const T interpX, const T step) const
    {
        T slope = (m_data[static_cast<unsigned int>(idx) + 1u] - m_data[static_cast<unsigned int>(idx)]) / step;
        return m_data[static_cast<unsigned int>(idx)] + slope * (interpX - baseX);
    }

    T extrapolate(const T extrapX, const T baseX, const T baseY, const T slope) const
    {
        return baseY + slope * (extrapX - baseX);
    }

protected:
    const T *m_data;
    const unsigned int m_size;
};

#endif /* AFAE9597_1EDD_409F_B906_60DFE541C1A1 */
