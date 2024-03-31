#ifndef AFAE9597_1EDD_409F_B906_60DFE541C1A1
#define AFAE9597_1EDD_409F_B906_60DFE541C1A1

template <typename T>
class Table1D
{
  public:
    Table1D( const T* independentVar, const T* data )
        : m_data( data ),
          m_independentVar( independentVar ),
          m_size( sizeof( data ) / sizeof( T ) )
    {
    }

    virtual ~Table1D() {}

    T operator[]( const unsigned int index ) const
    {
        return m_data[index];
    }

    virtual T lookUp( const T x ) const
    {
        if ( x < m_independentVar[0] )
        {
            return extrapolate( x, m_independentVar[0], m_data[0], ( m_data[1] - m_data[0] ) / ( m_independentVar[1] - m_independentVar[0] ) );
        }
        else if ( x > m_independentVar[m_size - 1u] )
        {
            return extrapolate( x, m_independentVar[m_size - 1u], m_data[m_size - 1u], ( m_data[m_size - 1u] - m_data[m_size - 2u] ) / ( m_independentVar[m_size - 1u] - m_independentVar[m_size - 2u] ) );
        }
        else
        {
            unsigned int idx = 0u;
            while ( x > m_independentVar[idx + 1u] )
            {
                idx++;
            }
            return interpolate( idx, m_independentVar[idx], x, m_independentVar[idx + 1u] - m_independentVar[idx] );
        }
    }

  protected:
    T interpolate( const double idx, const T baseX, const T interpX, const T step ) const
    {
        T slope = ( m_data[static_cast<unsigned int>( idx ) + 1u] - m_data[static_cast<unsigned int>( idx )] ) / step;
        return m_data[static_cast<unsigned int>( idx )] + slope * ( interpX - baseX );
    }

    T extrapolate( const T extrapX, const T baseX, const T baseY, const T slope ) const
    {
        return baseY + slope * ( extrapX - baseX );
    }

    const T* m_data;
    const T* m_independentVar;
    const unsigned int m_size;
};

#endif /* AFAE9597_1EDD_409F_B906_60DFE541C1A1 */
