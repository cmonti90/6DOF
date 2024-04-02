#ifndef TABLE2D_H
#define TABLE2D_H

#include "Table.h"

/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table2D : public Table< T >
{
  public:

    Table2D( const T* fpInput1, const int input1Length,
             const T* fpInput2, const int input2Length,
             const T* fpOutput, const int outputLength );

    virtual ~Table2D();

    T LookUp( const T fValue1, const T fValue2, bool extrapolate = false );
    void GetIndex( int& index1, T faScale1[], int& index2, T faScale2[] );

  private:

    T ComputeValue();

    T scale1_[2];
    T scale2_[2];
    int index1_;
    int index2_;

    const int input1Length_;
    const T*  fpInput1_;

    const int input2Length_;
    const T*  fpInput2_;

    const int outputLength_;
    const T**  fpOutput_;

}; // class Table2D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template< typename T >
Table2D< T >::Table2D( const T* fpInput1, const int input1Length,
                       const T* fpInput2, const int input2Length,
                       const T* fpOutput, const int outputLength )
    : Table< T >()
    , scale1_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale2_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , index1_       ( 0 )
    , index2_       ( 0 )
    , input1Length_ ( input1Length )
    , fpInput1_     ( fpInput1 )
    , input2Length_ ( input2Length )
    , fpInput2_     ( fpInput2 )
    , outputLength_ ( outputLength )
    , fpOutput_     ( nullptr )
{
    fpOutput_ = new T*[ input2Length_ ];

    for ( int i2 = 0; i2 < input2Length_; ++i2 )
    {
        fpOutput_[ i2 ] = &fpOutput[ i2 * input1Length_ ];

    }
}


template< typename T >
Table2D< T >::~Table2D()
{
    delete[] fpOutput_;
}


template< typename T >
T Table2D< T >::LookUp( const T fValue1, const T fValue2, bool extrapolate )
{
    TableIndexAndScale( fValue1, fpInput1_, input1Length_, extrapolate, index1_, scale1_ );
    TableIndexAndScale( fValue2, fpInput2_, input2Length_, extrapolate, index2_, scale2_ );

    return ComputeValue();
}


template< typename T >
void Table2D< T >::GetIndex( int& index1, T faScale1[], int& index2, T faScale2[] )
{
    index1 = index1_;
    index2 = index2_;

    faScale1[0] = scale1_[0];
    faScale1[1] = scale1_[1];

    faScale2[0] = scale2_[0];
    faScale2[1] = scale2_[1];
}


template< typename T >
T Table2D< T >::ComputeValue()
{
    const int indexp1 = index1_ + 1;
    const int indexp2 = index2_ + 1;
    
    return ( scale2_[0] * scale1_[0] * fpOutput_[ index2_ ][ index1_ ] +
             scale2_[0] * scale1_[1] * fpOutput_[ index2_ ][ indexp1 ] +
             scale2_[1] * scale1_[0] * fpOutput_[ indexp2 ][ index1_ ] +
             scale2_[1] * scale1_[1] * fpOutput_[ indexp2 ][ indexp1 ] );
}

#endif // TABLE2D_H