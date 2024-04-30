#ifndef TABLE4D_H
#define TABLE4D_H

#include "Table.h"

/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table4D : public Table< T >
{
  public:

    Table4D( const T* fpInput1, const int input1Length,
             const T* fpInput2, const int input2Length,
             const T* fpInput3, const int input3Length,
             const T* fpInput4, const int input4Length,
             const T* fpOutput, const int outputLength );

    virtual ~Table4D();

    T LookUp( const T fValue1, const T fValue2,
              const T fValue3, const T fValue4,
              bool extrapolate = false );

    T LookUp( const int index1, const T faScale1[],
              const int index2, const T faScale2[],
              const int index3, const T faScale3[],
              const int index4, const T faScale4[] );

    void GetIndex( int& index1, T faScale1[],
                   int& index2, T faScale2[],
                   int& index3, T faScale3[],
                   int& index4, T faScale4[] );

  private:

    T ComputeValue();

    T scale1_[2];
    T scale2_[2];
    T scale3_[2];
    T scale4_[2];

    int index1_;
    int index2_;
    int index3_;
    int index4_;

    const int input1Length_;
    const T*  fpInput1_;

    const int input2Length_;
    const T*  fpInput2_;

    const int input3Length_;
    const T*  fpInput3_;

    const int input4Length_;
    const T*  fpInput4_;

    const int outputLength_;
    const T****  fpOutput_;

}; // class Table4D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template< typename T >
Table4D< T >::Table4D( const T* fpInput1, const int input1Length,
                       const T* fpInput2, const int input2Length,
                       const T* fpInput3, const int input3Length,
                       const T* fpInput4, const int input4Length,
                       const T* fpOutput, const int outputLength )
    : Table< T >()
    , scale1_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale2_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale3_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale4_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , index1_       ( 0 )
    , index2_       ( 0 )
    , index3_       ( 0 )
    , index4_       ( 0 )
    , input1Length_ ( input1Length )
    , fpInput1_     ( fpInput1 )
    , input2Length_ ( input2Length )
    , fpInput2_     ( fpInput2 )
    , input3Length_ ( input3Length )
    , fpInput3_     ( fpInput3 )
    , input4Length_ ( input4Length )
    , fpInput4_     ( fpInput4 )
    , outputLength_ ( outputLength )
    , fpOutput_     ( nullptr )
{
    fpOutput_ = new const T*** [ input4Length_ ];

    for ( int i4 = 0; i4 < input4Length_; ++i4 )
    {
        fpOutput_[ i4 ] = new T** [ input3Length_ ];

        for ( int i3 = 0; i3 < input3Length_; ++i3 )
        {
            fpOutput_[ i4 ][ i3 ] = new T*[ input2Length_ ];

            for ( int i2 = 0; i2 < input2Length_; ++i2 )
            {
                fpOutput_[ i4 ][ i3 ][ i2 ] = &fpOutput[ ( ( i4 * input3Length_ + i3 ) * input2Length_ + i2 ) * input1Length_ ];
            }
        }
    }
}


template< typename T >
Table4D< T >::~Table4D()
{
    for ( int i4 = 0; i4 < input4Length_; ++i4 )
    {
        for ( int i3 = 0; i3 < input3Length_; ++i3 )
        {
            delete[] fpOutput_[ i4 ][ i3 ];
        }

        delete[] fpOutput_[ i4 ];
    }

    delete[] fpOutput_;
}


template< typename T >
T Table4D< T >::LookUp( const T fValue1, const T fValue2, const T fValue3, const T fValue4, bool extrapolate )
{
    this->TableIndexAndScale( fValue1, fpInput1_, input1Length_, extrapolate, index1_, scale1_ );
    this->TableIndexAndScale( fValue2, fpInput2_, input2Length_, extrapolate, index2_, scale2_ );
    this->TableIndexAndScale( fValue3, fpInput3_, input3Length_, extrapolate, index3_, scale3_ );
    this->TableIndexAndScale( fValue4, fpInput4_, input4Length_, extrapolate, index4_, scale4_ );

    return ComputeValue();
}


template< typename T >
T Table4D< T >::LookUp( const int index1, const T faScale1[],
                        const int index2, const T faScale2[],
                        const int index3, const T faScale3[],
                        const int index4, const T faScale4[] )
{
    index1_    = index1;
    scale1_[0] = faScale1[0];
    scale1_[1] = faScale1[1];

    index2_    = index2;
    scale2_[0] = faScale2[0];
    scale2_[1] = faScale2[1];

    index3_    = index3;
    scale3_[0] = faScale3[0];
    scale3_[1] = faScale3[1];

    index4_    = index4;
    scale4_[0] = faScale4[0];
    scale4_[1] = faScale4[1];

    return ComputeValue();
}

template< typename T >
void Table4D< T >::GetIndex( int& index1, T faScale1[],
                             int& index2, T faScale2[],
                             int& index3, T faScale3[],
                             int& index4, T faScale4[] )
{
    index1      = index1_;
    faScale1[0] = scale1_[0];
    faScale1[1] = scale1_[1];

    index2      = index2_;
    faScale2[0] = scale2_[0];
    faScale2[1] = scale2_[1];

    index3      = index3_;
    faScale3[0] = scale3_[0];
    faScale3[1] = scale3_[1];

    index4      = index4_;
    faScale4[0] = scale4_[0];
    faScale4[1] = scale4_[1];
}


template< typename T >
T Table4D< T >::ComputeValue()
{
    int index1p1 = index1_ + 1;
    int index2p1 = index2_ + 1;
    int index3p1 = index3_ + 1;
    int index4p1 = index4_ + 1;

    return ( scale4_[0] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index4_  ][ index3_  ][ index2_  ][ index1_  ] +
             scale4_[0] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index4_  ][ index3_  ][ index2_  ][ index1p1 ] +
             scale4_[0] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index4_  ][ index3_  ][ index2p1 ][ index1_  ] +
             scale4_[0] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index4_  ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale4_[0] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index4_  ][ index3p1 ][ index2_  ][ index1_  ] +
             scale4_[0] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index4_  ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale4_[0] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index4_  ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale4_[0] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index4_  ][ index3p1 ][ index2p1 ][ index1p1 ] +
             scale4_[1] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index4p1 ][ index3_  ][ index2_  ][ index1_  ] +
             scale4_[1] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index4p1 ][ index3_  ][ index2_  ][ index1p1 ] +
             scale4_[1] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index4p1 ][ index3_  ][ index2p1 ][ index1_  ] +
             scale4_[1] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index4p1 ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale4_[1] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index4p1 ][ index3p1 ][ index2_  ][ index1_  ] +
             scale4_[1] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index4p1 ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale4_[1] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index4p1 ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale4_[1] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index4p1 ][ index3p1 ][ index2p1 ][ index1p1 ] );

}

#endif // TABLE4D_H