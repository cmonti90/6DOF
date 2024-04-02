#ifndef TABLE_H
#define TABLE_H


/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table
{
  public:

    Table();
    virtual ~Table();

    void Reset();
    void TableIndexAndScale( T fValue, const T* fpInput, const int iLength, const bool extrapolate, int& iIndex, T faScale[] );

  protected:

    bool resetSearch_;

}; // class Table


///////////////////////////////
//////    DEFINITIONS    //////
///////////////////////////////

template< typename T >
Table< T >::Table()
    : resetSearch_( true )
{
}


template< typename T >
Table< T >::~Table()
{
}


template< typename T >
void Table< T >::Reset()
{
    resetSearch_ = true;
}


template< typename T >
void Table< T >::TableIndexAndScale( T fValue, const T* fpInput, const int iLength, const bool extrapolate, int& iIndex, T faScale[] )
{
    if ( !extrapolate )
    {
        if ( fValue < fpInput[0] )
        {
            fValue = fpInput[0];
        }

        if ( fValue > fpInput[iLength - 1] )
        {
            fValue = fpInput[iLength - 1];
        }
    }

    if ( resetSearch_ )
    {
        resetSearch_ = false;

        // Binary search
        int upperIdx = iLength - 1;
        int lowerIdx = 0;

        while ( upperIdx - lowerIdx > 1 )
        {
            int midIdx = static_cast< int >( ( upperIdx + lowerIdx ) / 2 );

            if ( fValue < fpInput[midIdx] )
            {
                upperIdx = midIdx;
            }
            else
            {
                lowerIdx = midIdx;
            }
        }
        
        iIndex = lowerIdx;
    }
    else
    {
        if ( fValue < fpInput[iIndex] )
        {
            while ( fValue < fpInput[iIndex] && iIndex > 0)
            {
                iIndex--;
            }
        }
        else
        {
            while ( fValue > fpInput[iIndex + 1] && iIndex < iLength - 2)
            {
                iIndex++;
            }
        }
    }

    faScale[1] = ( fValue - fpInput[iIndex] ) / ( fpInput[iIndex + 1] - fpInput[iIndex] );
    faScale[0] = static_cast< T >( 1 ) - faScale[1];
}

#endif // TABLE_H