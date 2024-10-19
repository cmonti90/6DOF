#ifndef TABLE1D_H
#define TABLE1D_H

#include "Table.h"


/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template < typename T >
class Table1D : public Table< T >
{
  public:

    Table1D( const T* fpInput1, const int input1Length,
             const T* fpOutput, const int outputLength );

    virtual ~Table1D();

    T LookUp( const T fValue1, bool extrapolate = false );
    T LookUp( const int index1, const T faScale[] );
    void GetIndex( int& index1, T faScale[] );

  private:

    T ComputeValue();

    T scale1_[2];
    int index1_;

    const int input1Length_;
    const T*  fpInput1_;

    const int outputLength_;
    const T*  fpOutput_;


}; // class Table1D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template < typename T >
Table1D< T >::Table1D( const T* fpInput1, const int input1Length,
                       const T* fpOutput, const int outputLength )
    : Table< T >()
    , scale1_       { static_cast< T >( 0 ), static_cast< T >( 0 ) }
    , index1_       ( 0 )
    , input1Length_ ( input1Length )
    , fpInput1_     ( fpInput1 )
    , outputLength_ ( outputLength )
    , fpOutput_     ( fpOutput )
{
}


template < typename T >
Table1D< T >::~Table1D()
{
}


template < typename T >
T Table1D< T >::LookUp( const T fValue1, bool extrapolate )
{
    this->TableIndexAndScale( fValue1, fpInput1_, input1Length_, extrapolate, index1_, scale1_ );

    return ComputeValue();
}


template < typename T >
T Table1D< T >::LookUp( const int index1, const T faScale[] )
{
    index1_    = index1;
    scale1_[0] = faScale[0];
    scale1_[1] = faScale[1];

    return ComputeValue();
}


template < typename T >
void Table1D< T >::GetIndex( int& index1, T faScale[] )
{
    index1 = index1_;
    faScale[0] = scale1_[0];
    faScale[1] = scale1_[1];
}


template < typename T >
T Table1D< T >::ComputeValue()
{
    return ( scale1_[0] * fpOutput_[index1_] +
             scale1_[1] * fpOutput_[index1_ + 1] );
}


#endif // TABLE1D_H
