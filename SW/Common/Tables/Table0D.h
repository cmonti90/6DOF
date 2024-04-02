#ifndef TABLE0D_H
#define TABLE0D_H

#include "Table.h"

/////////////////////////////
/////    DECLARATION    /////
/////////////////////////////

template< typename T >
class Table0D : public Table< T >
{
  public:

    Table0D( const T* input1, const int input1Length );
    virtual ~Table0D();

    void LookUp( T fValue1, int& iIndex1, T faScale1[], bool extrapolate = false );

  private:

    const int input1Length_;
    const T* input1_;

}; // class Table0D


/////////////////////////////
/////    DEFINITIONS    /////
/////////////////////////////

template< typename T >
Table0D< T >::Table0D( const T* input1, const int input1Length )
    : Table<T>()
    , input1_( input1 )
    , input1Length_( input1Length )
{
}


template< typename T >
Table0D< T >::~Table0D()
{
}

template< typename T >
void Table0D< T >::LookUp( T fValue1, int& iIndex1, T faScale1[], bool extrapolate )
{
    TableIndexAndScale( fValue1, input1_, input1Length_, extrapolate, iIndex1, faScale1 );
}

#endif // TABLE0D_H