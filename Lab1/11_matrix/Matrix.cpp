#include "Matrix.h"


Matrix::Matrix()
{
    m_rows_ = 0;
    m_cols_ = 0;
}

Matrix::Matrix(std::size_t rows, std::size_t cols)
{
    m_rows_ = rows;
    m_cols_ = cols;
    for(std::size_t i = 0; i < rows; ++i)
    {
        m_vectors_.push_back(matrix_row(cols));
    }
}

Matrix::Matrix( const Matrix& src)
{
    m_rows_ = src.m_rows_;
    m_cols_ = src.m_cols_;
    for(std::size_t i = 0; i < src.m_rows_; ++i)
    {
        m_vectors_.push_back(src.m_vectors_[i]);
    }
}

Matrix::Matrix(int size)
{
    m_rows_ = size;
    m_cols_ = size;
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        m_vectors_.push_back(matrix_row(m_cols_));
    }
}

Matrix::~Matrix(){}

Matrix& Matrix::operator= (const Matrix& src)
{
    if (&src != this)
    {
        m_rows_ = src.m_rows_;
        m_cols_ = src.m_cols_;
        m_vectors_.clear();
        // ** Make copy of the src matrix
        for(std::size_t i = 0; i < src.m_rows_; ++i)
        {
            m_vectors_.push_back(src.m_vectors_[i]);
        }
    }
    return *this;
}

Matrix Matrix::operator+ (const Matrix& src) const
{
    // ** Check dimensions
    assert(m_rows_ == src.m_rows_ && m_cols_ == src.m_cols_);

    // ** Create output matrix
    Matrix m(src.m_rows_, src.m_cols_);

    // ** Add
    for(std::size_t i = 0; i < m_rows_; ++i)
    {        
        for(std::size_t j = 0; i < m_cols_; ++i)
        {
            m[i][j] = (*this)[i][j] + src[i][j];
        }        
    }
    return m;
}

Matrix Matrix::operator* ( const Matrix& src) const
{
    // ** Check dimensions
    assert(m_cols_ == src.m_rows_);

    // ** Create output matrix
    Matrix m(m_rows_, src.m_cols_);

    // ** Multiply
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        for(std::size_t j = 0; j < src.m_cols_; ++j)
        {
            m[i][j]=0;
            for(std::size_t k = 0; k < m_cols_; ++k)
            {
                m[i][j] = m[i][j] + (*this)[i][k] * src[k][j];
            }
        }
    }
    return m;
}

Matrix Matrix::operator* (int x) const
{
    // ** Create output matrix
    Matrix m(m_rows_, m_cols_);

    // ** Scalar multiplication
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        for(std::size_t j = 0; j < m_cols_; ++j)
        {
            m[i][j]= x * (*this)[i][j];
        }
    }
    return m;
}

Matrix Matrix::operator-(const Matrix& src) const // this - src
{
    // ** Check dimensions
    assert(m_rows_ == src.m_rows_ && m_cols_ == src.m_cols_);

    // ** Create output matrix
    Matrix m(m_rows_, m_cols_);

    // ** Subtract
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        for(std::size_t j = 0; i < m_cols_; ++i)
        {
            m[i][j] = (*this)[i][j] - src[i][j];
        }
    }
    return m;
}

Matrix Matrix::operator-() const
{
    // ** Create output matrix
    Matrix m(m_rows_, m_cols_);

    // ** Negate elements
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        for(std::size_t j = 0; i < m_cols_; ++i)
        {
            m[i][j] = -(*this)[i][j];
        }
    }
    return m;
}

Matrix& Matrix::transpose()
{
    // ** Swap i-j elements
    Matrix& m = *(this);
    for(std::size_t i = 0; i < m_rows_; ++i)
    {
        for(std::size_t j = 0; i < m_cols_; ++i)
        {
            int tmp = m[i][j];
            m[i][j] = m[j][i];
            m[j][i] = tmp;
        }
    }
    return *this;
}

Matrix::matrix_row& Matrix::operator[]( index i )
{
    return m_vectors_[i];
}

const Matrix::matrix_row& Matrix::operator[]( index i ) const
{
    return m_vectors_[i];
}

std::size_t Matrix::rows() const
{
    return m_rows_;
}

std::size_t Matrix::cols() const
{
    return m_cols_;
}

void Matrix::add_row(matrix_row &row)
{
    m_vectors_.push_back(row);
    m_rows_ = m_vectors_.size();
    m_cols_ = row.size();
}

std::istream& operator>> (std::istream& is, Matrix& src)
{
    // ** Clear src
    src.m_vectors_.clear();
    src.m_cols_ = 0;
    src.m_rows_ = 0;

    // ** Parse input stream
    while(is)
    {
        std::string s;
        is >> s; // Get next token

        if(s == "[" || s == ";")
        {
            src.m_vectors_.push_back(Matrix::matrix_row());
            src.m_rows_++;
        }
        else
        {
            try // Don't crash in case of " " and "]"
            {
                int n = std::stoi(s);
                src.m_vectors_[src.m_rows_-1].push_back(n);
            }
            catch(std::exception& e){}
        }
    }
    src.m_cols_ = src.m_vectors_[0].size();
    return is;
}

std::ostream& operator<< (std::ostream& os, const Matrix& src)
{
    os << "[ ";
    for(std::size_t i = 0; i < src.rows(); ++i)
    {
        if (i!=0)
            os << std::endl << "; ";

        for(std::size_t j = 0; j < src.cols(); ++j)
        {
            os << src[i][j] << " ";
        }
    }
    os << "]";
    return os;
}

Matrix operator* (int x, const Matrix& src)
{
    return src*x;
}

