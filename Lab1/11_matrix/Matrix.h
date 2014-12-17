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

    class matrix_row : private Vector< int > // Private inheritance to use only some functions from vector
    {
    public:
        explicit matrix_row( std::size_t s = 0) : Vector< int >( s ) {}
        using Vector<int>::operator[];
        using Vector<int>::size;
    private:
        friend std::istream& operator>>( std::istream&, Matrix& );
    };
    
    Matrix();
    explicit Matrix(std::size_t rows, std::size_t cols);
    Matrix(const Matrix& src);      // Copy constructor
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
    
    friend std::istream& operator>> ( std::istream&, Matrix& );
    // Need friend in >> since I need to setup all the internal variables.
    // Don't need friend in << since I just read and the operator[] is public
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, const Matrix& );
Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H
