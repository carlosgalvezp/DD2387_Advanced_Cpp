#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <assert.h>

#include "kth_cprog_template_container.hpp"

class Matrix
{
 public:
    typedef unsigned int index; //not so good, can create confusion with variable name
    
    class matrix_row : private Vector< int >
    {
    public:
        matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator[];
        using Vector<int>::size;
    private:
        friend std::istream& operator>>( std::istream&, Matrix& ); // Why is this here??
    };
    
    Matrix();
    explicit Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix& src);
    explicit Matrix(int size);
    ~Matrix( );
    
    Matrix& operator= ( const Matrix& ); //Copy assigment operator
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    std::size_t rows() const;
    std::size_t cols() const;
    
    void add_row(matrix_row& row);            // Non mandatory help function

 protected:
 private:
    Vector< matrix_row >        m_vectors_;
    std::size_t                 m_rows_;
    std::size_t                 m_cols_;
    
    friend std::istream& operator>> ( std::istream&, Matrix& ); // need also operator<<!
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, const Matrix& );
Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H
