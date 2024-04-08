#ifndef TABLE5D_H
#define TABLE5D_H

#include "Table.h"

/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table5D : public Table< T >
{
  public:

    Table5D( const T* fpInput1, const int input1Length,
             const T* fpInput2, const int input2Length,
             const T* fpInput3, const int input3Length,
             const T* fpInput4, const int input4Length,
             const T* fpInput5, const int input5Length,
             const T* fpOutput, const int outputLength );

    virtual ~Table5D();

    T LookUp( const T fValue1, const T fValue2, const T fValue3, const T fValue4, const T fValue5, bool extrapolate = false );
    void GetIndex( int& index1, T faScale1[], int& index2, T faScale2[], int& index3, T faScale3[], int& index4, T faScale4[], int& index5, T faScale5[] );

  private:

    T ComputeValue();

    T scale1_[2];
    T scale2_[2];
    T scale3_[2];
    T scale4_[2];
    T scale5_[2];
    int index1_;
    int index2_;
    int index3_;
    int index4_;
    int index5_;

    const int input1Length_;
    const T*  fpInput1_;

    const int input2Length_;
    const T*  fpInput2_;

    const int input3Length_;
    const T*  fpInput3_;

    const int input4Length_;
    const T*  fpInput4_;

    const int input5Length_;
    const T*  fpInput5_;

    const int outputLength_;
    const T*****  fpOutput_;

}; // class Table5D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template< typename T >
Table5D< T >::Table5D( const T* fpInput1, const int input1Length,
                       const T* fpInput2, const int input2Length,
                       const T* fpInput3, const int input3Length,
                       const T* fpInput4, const int input4Length,
                       const T* fpInput5, const int input5Length,
                       const T* fpOutput, const int outputLength )
    : Table< T >()
    , scale1_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale2_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale3_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale4_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , scale5_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , index1_       ( 0 )
    , index2_       ( 0 )
    , index3_       ( 0 )
    , index4_       ( 0 )
    , index5_       ( 0 )
    , input1Length_ ( input1Length )
    , fpInput1_     ( fpInput1 )
    , input2Length_ ( input2Length )
    , fpInput2_     ( fpInput2 )
    , input3Length_ ( input3Length )
    , fpInput3_     ( fpInput3 )
    , input4Length_ ( input4Length )
    , fpInput4_     ( fpInput4 )
    , input5Length_ ( input5Length )
    , fpInput5_     ( fpInput5 )
    , outputLength_ ( outputLength )
    , fpOutput_     ( nullptr )
{
    fpOutput_ = new const T**** [ input5Length_ ];

    for ( int i5 = 0; i5 < input5Length_; ++i5 )
    {
        fpOutput_[ i5 ] = new T*** [ input4Length_ ];

        for ( int i4 = 0; i4 < input4Length_; ++i4 )
        {
            fpOutput_[ i5 ][ i4 ] = new T** [ input3Length_ ];

            for ( int i3 = 0; i3 < input3Length_; ++i3 )
            {
                fpOutput_[ i5 ][ i4 ][ i3 ] = new T* [ input2Length_ ];

                for ( int i2 = 0; i2 < input2Length_; ++i2 )
                {
                    fpOutput_[ i5 ][ i4 ][ i3 ][ i2 ] = &fpOutput[ ( ( ( i5 * input4Length_ + i4 ) * input3Length_ + i3 ) * input2Length_ + i2 ) * input1Length_ ];
                }
            }
        }
    }
}


template< typename T >
Table5D< T >::~Table5D()
{
    for ( int i5 = 0; i5 < input5Length_; ++i5 )
    {
        for ( int i4 = 0; i4 < input4Length_; ++i4 )
        {
            for ( int i3 = 0; i3 < input3Length_; ++i3 )
            {
                delete[] fpOutput_[ i5 ][ i4 ][ i3 ];
            }

            delete[] fpOutput_[ i5 ][ i4 ];
        }

        delete[] fpOutput_[ i5 ];
    }

    delete[] fpOutput_;
}


template< typename T >
T Table5D< T >::LookUp( const T fValue1, const T fValue2, const T fValue3, const T fValue4, const T fValue5, bool extrapolate )
{
    TableIndexAndScale( fValue1, fpInput1_, input1Length_, extrapolate, index1_, scale1_ );
    TableIndexAndScale( fValue2, fpInput2_, input2Length_, extrapolate, index2_, scale2_ );
    TableIndexAndScale( fValue3, fpInput3_, input3Length_, extrapolate, index3_, scale3_ );
    TableIndexAndScale( fValue4, fpInput4_, input4Length_, extrapolate, index4_, scale4_ );
    TableIndexAndScale( fValue5, fpInput5_, input5Length_, extrapolate, index5_, scale5_ );

    return ComputeValue();
}


template< typename T >
void Table5D< T >::GetIndex( int& index1, T faScale1[], int& index2, T faScale2[], int& index3, T faScale3[], int& index4, T faScale4[], int& index5, T faScale5[] )
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

    index4 = index4_;
    faScale4[0] = scale4_[0];
    faScale4[1] = scale4_[1];

    index5 = index5_;
    faScale5[0] = scale5_[0];
    faScale5[1] = scale5_[1];
}


template< typename T >
T Table5D< T >::ComputeValue()
{
    const int index1p1 = index1_ + 1;
    const int index2p1 = index2_ + 1;
    const int index3p1 = index3_ + 1;
    const int index4p1 = index4_ + 1;
    const int index5p1 = index5_ + 1;

    return ( scale5_[0] * scale4_[0] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index5_  ][ index4_  ][ index3_  ][ index2_  ][ index1_  ] +
             scale5_[0] * scale4_[0] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index5_  ][ index4_  ][ index3_  ][ index2_  ][ index1p1 ] +
             scale5_[0] * scale4_[0] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index5_  ][ index4_  ][ index3_  ][ index2p1 ][ index1_  ] +
             scale5_[0] * scale4_[0] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index5_  ][ index4_  ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale5_[0] * scale4_[0] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index5_  ][ index4_  ][ index3p1 ][ index2_  ][ index1_  ] +
             scale5_[0] * scale4_[0] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index5_  ][ index4_  ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale5_[0] * scale4_[0] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index5_  ][ index4_  ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale5_[0] * scale4_[0] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index5_  ][ index4_  ][ index3p1 ][ index2p1 ][ index1p1 ] +
             scale5_[0] * scale4_[1] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index5_  ][ index4p1 ][ index3_  ][ index2_  ][ index1_  ] +
             scale5_[0] * scale4_[1] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index5_  ][ index4p1 ][ index3_  ][ index2_  ][ index1p1 ] +
             scale5_[0] * scale4_[1] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index5_  ][ index4p1 ][ index3_  ][ index2p1 ][ index1_  ] +
             scale5_[0] * scale4_[1] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index5_  ][ index4p1 ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale5_[0] * scale4_[1] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index5_  ][ index4p1 ][ index3p1 ][ index2_  ][ index1_  ] +
             scale5_[0] * scale4_[1] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index5_  ][ index4p1 ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale5_[0] * scale4_[1] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index5_  ][ index4p1 ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale5_[0] * scale4_[1] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index5_  ][ index4p1 ][ index3p1 ][ index2p1 ][ index1p1 ] +
             scale5_[1] * scale4_[0] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index5p1 ][ index4_  ][ index3_  ][ index2_  ][ index1_  ] +
             scale5_[1] * scale4_[0] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index5p1 ][ index4_  ][ index3_  ][ index2_  ][ index1p1 ] +
             scale5_[1] * scale4_[0] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index5p1 ][ index4_  ][ index3_  ][ index2p1 ][ index1_  ] +
             scale5_[1] * scale4_[0] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index5p1 ][ index4_  ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale5_[1] * scale4_[0] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index5p1 ][ index4_  ][ index3p1 ][ index2_  ][ index1_  ] +
             scale5_[1] * scale4_[0] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index5p1 ][ index4_  ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale5_[1] * scale4_[0] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index5p1 ][ index4_  ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale5_[1] * scale4_[0] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index5p1 ][ index4_  ][ index3p1 ][ index2p1 ][ index1p1 ] +
             scale5_[1] * scale4_[1] * scale3_[0] * scale2_[0] * scale1_[0] * fpOutput_[ index5p1 ][ index4p1 ][ index3_  ][ index2_  ][ index1_  ] +
             scale5_[1] * scale4_[1] * scale3_[0] * scale2_[0] * scale1_[1] * fpOutput_[ index5p1 ][ index4p1 ][ index3_  ][ index2_  ][ index1p1 ] +
             scale5_[1] * scale4_[1] * scale3_[0] * scale2_[1] * scale1_[0] * fpOutput_[ index5p1 ][ index4p1 ][ index3_  ][ index2p1 ][ index1_  ] +
             scale5_[1] * scale4_[1] * scale3_[0] * scale2_[1] * scale1_[1] * fpOutput_[ index5p1 ][ index4p1 ][ index3_  ][ index2p1 ][ index1p1 ] +
             scale5_[1] * scale4_[1] * scale3_[1] * scale2_[0] * scale1_[0] * fpOutput_[ index5p1 ][ index4p1 ][ index3p1 ][ index2_  ][ index1_  ] +
             scale5_[1] * scale4_[1] * scale3_[1] * scale2_[0] * scale1_[1] * fpOutput_[ index5p1 ][ index4p1 ][ index3p1 ][ index2_  ][ index1p1 ] +
             scale5_[1] * scale4_[1] * scale3_[1] * scale2_[1] * scale1_[0] * fpOutput_[ index5p1 ][ index4p1 ][ index3p1 ][ index2p1 ][ index1_  ] +
             scale5_[1] * scale4_[1] * scale3_[1] * scale2_[1] * scale1_[1] * fpOutput_[ index5p1 ][ index4p1 ][ index3p1 ][ index2p1 ][ index1p1 ] );
}

#endif // TABLE5D_H