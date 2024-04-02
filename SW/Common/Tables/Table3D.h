#ifndef TABLE3D_H
#define TABLE3D_H

#include "Table.h"


/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table3D : public Table< T >
{
  public:

    Table3D( const T* fpInput1, const int input1Length,
             const T* fpInput2, const int input2Length,
             const T* fpInput3, const int input3Length,
             const T* fpOutput, const int outputLength );

    virtual ~Table3D();

    T LookUp( const T fValue1, const T fValue2, const T fValue3, bool extrapolate = false );
    void GetIndex( int& index1, T faScale1[], int& index2, T faScale2[], int& index3, T faScale3[] );

  private:

    T ComputeValue();

    T scale1_[2];
    T scale2_[2];
    T scale3_[2];
    int index1_;
    int index2_;
    int index3_;

    const int input1Length_;
    const T*  fpInput1_;

    const int input2Length_;
    const T*  fpInput2_;

    const int input3Length_;
    const T*  fpInput3_;

    const int outputLength_;
    const T***  fpOutput_;

}; // class Table3D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template< typename T >
Table3D< T >::Table3D( const T* fpInput1, const int input1Length,
                       const T* fpInput2, const int input2Length,
                       const T* fpInput3, const int input3Length,
                       const T* fpOutput, const int outputLength )
    : Table< T >()
    , scale1_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale2_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale3_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , index1_       ( 0 )
    , index2_       ( 0 )
    , index3_       ( 0 )
    , input1Length_ ( input1Length )
    , fpInput1_     ( fpInput1 )
    , input2Length_ ( input2Length )
    , fpInput2_     ( fpInput2 )
    , input3Length_ ( input3Length )
    , fpInput3_     ( fpInput3 )
    , outputLength_ ( outputLength )
    , fpOutput_     ( nullptr )
{
    fpOutput_ = new T**[ input3Length_ ];

    for ( int i3 = 0; i3 < input3Length_; ++i3 )
    {
        fpOutput_[ i3 ] = new T*[ input2Length_ ];

        for ( int i2 = 0; i2 < input2Length_; ++i2 )
        {
            fpOutput_[ i3 ][ i2 ] = &fpOutput[ ( i3 * input2Length_ + i2 ) * input1Length_ ];
        }
    }
}


template< typename T >
Table3D< T >::~Table3D()
{
    for ( int i3 = 0; i3 < input3Length_; ++i3 )
    {
        delete[] fpOutput_[ i3 ];
    }

    delete[] fpOutput_;
}


template< typename T >
T Table3D< T >::LookUp( const T fValue1, const T fValue2, const T fValue3, bool extrapolate )
{
    TableIndexAndScale( fValue1, fpInput1_, input1Length_, extrapolate, index1_, scale1_ );
    TableIndexAndScale( fValue2, fpInput2_, input2Length_, extrapolate, index2_, scale2_ );
    TableIndexAndScale( fValue3, fpInput3_, input3Length_, extrapolate, index3_, scale3_ );

    return ComputeValue();
}


template< typename T >
void Table3D< T >::GetIndex( int& index1, T faScale1[], int& index2, T faScale2[], int& index3, T faScale3[] )
{
    index1 = index1_;
    faScale1[0] = scale1_[0];
    faScale1[1] = scale1_[1];

    index2 = index2_;
    faScale2[0] = scale2_[0];
    faScale2[1] = scale2_[1];

    index3 = index3_;
    faScale3[0] = scale3_[0];
    faScale3[1] = scale3_[1];
}


template< typename T >
T Table3D< T >::ComputeValue()
{
    const int index1p1 = index1_ + 1;
    const int index2p1 = index2_ + 1;
    const int index3p1 = index3_ + 1;
    
    return ( scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index3_  ][ index2_  ][ index1_  ] +
             scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index3_  ][ index2_  ][ index1p1 ] +
             scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index3_  ][ index2p1 ][ index1_  ] +
             scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index3_  ][ index2p1 ][ index1p1 ] +
             scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index3p1 ][ index2_  ][ index1_  ] +
             scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index3p1 ][ index2_  ][ index1p1 ] +
             scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index3p1 ][ index2p1 ][ index1_  ] +
             scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index3p1 ][ index2p1 ][ index1p1 ] );
}

#endif // TABLE3D_H