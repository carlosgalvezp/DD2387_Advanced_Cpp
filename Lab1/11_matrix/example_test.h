#ifndef MATRIX_TEST_H_INCLUDED
#define MATRIX_TEST_H_INCLUDED

#include "Matrix_original.h"
//#include "Matrix.h"
#include <cxxtest/TestSuite.h>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

class MatrixTestSuite : public CxxTest::TestSuite
{

    Matrix a_matrix_3by2() {    // [ 1 3 5 ]
        Matrix m;               // [ 0 2 0 ]
        std::stringstream s("  [ 1 3 5 ; 0 2 0 ]");
        s >> m;
        return m;
    }

    void init_matrix( Matrix& m, const char* file )
    {
        std::stringstream stream( file );   
        stream >> m;
    }

void assertEqualMatrices(const Matrix &m1, const Matrix &m2)
{
    TS_ASSERT(m1.cols() == m2.cols() && m1.rows() == m2.rows());
    for(std::size_t i = 0; i < m1.rows(); ++i)
    {
        for(std::size_t j = 0; j < m1.cols(); ++j)
        {
            TS_ASSERT(m1[i][j] == m2[i][j]);
        }
    }
}

void assertValue(const Matrix &m, int value)
{
    for(std::size_t i = 0; i < m.rows(); ++i)
    {
        for(std::size_t j = 0; j < m.cols(); ++j)
        {
            TS_ASSERT(m[i][j] == value);
        }
    }
}

void assertIdentity(const Matrix &m)
{
	TS_ASSERT(m.cols() == m.rows());
    for(std::size_t i = 0; i < m.rows(); ++i)
    {
	    TS_ASSERT(m[i][i] == 1);
    }
}

void assertMultiplication(const Matrix &m0, const Matrix &m1, int value)
{
	TS_ASSERT(m0.cols() == m1.cols() && m0.rows() == m1.rows());
    for(std::size_t i = 0; i < m0.rows(); ++i)
    {
        for(std::size_t j = 0; j < m0.cols(); ++j)
        {
            TS_ASSERT(m1[i][j] == value * m0[i][j]);
        }
    }
}

public:

void testConstructors()
{
    std::cout << "===== TEST CONSTRUCTORS ====="<<std::endl;
    // ** Default constructor
    Matrix m;
    TS_ASSERT(m.rows() == 0 && m.cols() == 0);
    // ** Row-col constructor
    Matrix m2(2,4);
	std::cout << "m2\n" << m2 <<std::endl;
    TS_ASSERT(m2.rows() == 2  && m2.cols() == 4);
	assertValue(m2,0);

    // ** Copy constructor
    Matrix m3(m2);
    assertEqualMatrices(m2,m3);
	m3[1][1] = 5;
	TS_ASSERT(m3[1][1] == 5 && m2[1][1] != 5);

    // ** Squared matrix
    Matrix m4(5);
    TS_ASSERT(m4.rows() == 5 && m4.cols() == 5);
	assertIdentity(m4);
	std::cout << "m4\n"<<m4 << std::endl;
	assertIdentity(m4);
}

void testAssignment()
{
    std::cout << "===== TEST ASSIGNMENT ====="<<std::endl;

    Matrix m(2);
    m[0][1] = 7;
    m[1][0] = 43;
    std::cout << "m\n"<<m<<std::endl;

    Matrix m2;
    m2 = m;
    assertEqualMatrices(m,m2);
    std::cout <<"m2 = m\n"<<m2<<std::endl;

	// Modify the copied matrix
	m2[1][0] = 67;
	TS_ASSERT(m2[1][0] == 67 && m[1][0] != 67);
}

void testArithmetics()
{
    std::cout << "===== TEST ARITHMETICS ====="<<std::endl;

    Matrix m1(2);
    m1[0][0] = 7;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 9;

    Matrix m2(2);
    m2[0][0] = 5;
    m2[0][1] = 1;
    m2[1][0] = -15;
    m2[1][1] = -5;

    std::cout <<"m1\n"<<m1 << "\n m2\n"<<m2<<std::endl;

    // ** Add
    Matrix m3 = m1+m2;
    std::cout << "Add: m3 = m1+m2\n" <<m3 << std::endl;
    TS_ASSERT(m3[0][0] == 12 && m3[0][1] == 3 && m3[1][0] == -12 && m3[1][1] == 4);

    // ** Subtract
    Matrix m4 = m1-m2;
    std::cout << "Subtract: m4 = m1-m2\n" <<m4 << std::endl;
    TS_ASSERT(m4[0][0] == 2 && m4[0][1] == 1 && m4[1][0] == 18 && m4[1][1] == 14);

    // ** Multiply scalar
    Matrix m5 = 3*m1;
    Matrix m6 = m1*6;
	assertMultiplication(m1,m5,3);
	assertMultiplication(m1,m6,6);
    std::cout << "m5 = 3*m1\n" << "m1\n"<<m1<<"\n m5\n"<<m5 <<std::endl;
    std::cout << "m6 = m1*6\n" << "m1\n"<<m1<<"\n m6\n"<<m6 <<std::endl;

    // ** Multiply matrix
    Matrix m7 = m1 * m2;
	Matrix m7_good(m7);
	m7_good[0][0] = 5;
	m7_good[0][1] = -3;
	m7_good[1][0] = -120;
	m7_good[1][1] =  -42;
    std::cout << "m7 = m1 * m2\n" << m7<<std::endl;
	assertEqualMatrices(m7, m7_good);

    // ** Negation
    Matrix m8 = m1;
 //   std::cout << "m8\n"<<m8<<std::endl;
    Matrix m9 = -m8;
 //   std::cout << "m9 = -m8\n"<<m9<<std::endl;
    for(std::size_t i = 0; i < m8.rows(); ++i)
        for(std::size_t j = 0; j < m9.rows(); ++j)
            TS_ASSERT(m8[i][j] == -m9[i][j]);

    // ** Chain
    Matrix m10 = (m1 + m2 + m3 + m4 + m5) * m1 * m2;
 //   std::cout << "m10 = (m1+m2+m3+m4+m5)*m1*m2 \n"<<m10<<std::endl;

}

void testTranspose()
{
    std::cout << "===== TEST TRANSPOSE ====="<<std::endl;

    Matrix m1(2);
    m1[0][0] = 1;
    m1[0][1] = 2;
    m1[1][0] = 3;
    m1[1][1] = 4;
    std::cout << "m1\n"<<m1<<std::endl;
    Matrix m2(m1);
    m1.transpose();
    std::cout << "m1 transpose\n"<<m1<<std::endl;
    for(std::size_t i = 0; i < m1.rows(); ++i)
        for(std::size_t j = 0; j < m1.cols(); ++j)
            TS_ASSERT(m1[i][j] == m2[j][i]);
}


void testDimensions()
{
    std::cout << "===== TEST DIMENSIONS ====="<<std::endl;
    // ** Arithmetics different dimensions
    Matrix m1(2);
    Matrix m2(2,3);
    Matrix m3(3,4);

	bool ok(false);
	try
 	{
 	   Matrix m4 = m1+m2; // Fail, different dimensions
	}catch(std::exception &e){ok = true;}

	TS_ASSERT(ok);
	ok = false;

	try{
	    Matrix m5 = m1-m2; // Fail, different dimensions
	}catch(std::exception &e){ok = true;}

	TS_ASSERT(ok);
	ok = false;

	try{
	    Matrix m7 = m3*m2; // Fail, incorrect dimensions
	}catch(std::exception &e){ok = true;}
	
	TS_ASSERT(ok);
}

    void testIndexOperator ( )
    {
        Matrix m( 2, 2 );
        TS_ASSERT( m[ 0 ][ 1 ] == 0 );

        m = a_matrix_3by2();
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        init_matrix(m, "  [ 1 3 5 ; 0 2 1 ]");
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );

        std::stringstream ss;
        ss << m;
        ss >> m;
        TS_ASSERT( m[ 0 ][ 0 ] == 1 );
    }

void testIndex()
{
    std::cout << "===== TEST INDEX OPERATOR ====="<<std::endl;

	Matrix m(2);
	m[0][0] = 124;
	m[0][1] = 12;
	m[1][0] = 213;
	m[1][1] = 1245;
	std::cout << "m\n"<<m<<std::endl;
	TS_ASSERT(m[0][0] == 124 && m[0][1] == 12 && m[1][0] == 213 && m[1][1] == 1245);
}

void testInput()
{
	Matrix m(2,3);
	init_matrix(m, "  [ 67 54 12 ; 234 68 9654 ]");
    TS_ASSERT( m[0][0] == 67 && m[0][1] == 54 && m[0][2] == 12 &&
			   m[1][0] == 234 && m[1][1] == 68 && m[1][2] == 9654);

}

void test59()
{
    std::cout << "===== TEST 5 and 9 ====="<<std::endl;

	// ** Value after assignment
	Matrix m(3);
	assertIdentity(m);
	std::cout <<"m\n"<<m << std::endl;
	assertIdentity(m);
	std::cout << "m (after cout)\n" <<m<< std::endl;

	// ** Value after printing
	Matrix m2(4);
	std::cout << "m2\n" <<m2<< std::endl;
	Matrix m3 = m2;
	assertEqualMatrices(m3,m2);
	assertEqualMatrices(m2,m2);
	std::cout << "m2 (after assignment)\n"<<m2 <<std::endl;
	std::cout << "m3 (after assignment)\n"<<m3 <<std::endl;
	
}

void testNegativeDimensions()
{
    std::cout << "===== TEST NEGATIVE DIMENSIONS ====="<<std::endl;
	bool ok(false);

	try
	{
		Matrix m(-2);
	}catch(std::exception &e) {ok = true;}

	TS_ASSERT(ok);
	ok = false;

	try
	{
		Matrix m(-9,-7);
	}catch (std::exception &e) {ok  = true;}
	
	TS_ASSERT(ok);
}

void testOutput()
{
    std::cout << "===== TEST OUTPUT ====="<<std::endl;

	Matrix m(2);
	m[0][0] = 123;
	m[0][1] = -129;
	m[1][0] = 98;
	m[1][1] = 54;

	std::stringstream ss;
	std::string ss_str;
	ss << m;
	ss_str = ss.str();
	std::replace(ss_str.begin(), ss_str.end(), ' ', '_');
	std::cout << ss_str << std::endl;
	TS_ASSERT(ss.str() == "[ 123 -129 \n; 98 54 ]");
	TS_ASSERT(ss_str == "[_123_-129_\n;_98_54_]");
}

void testChain()
{
    std::cout << "===== TEST CHAIN OPERATIONS ====="<<std::endl;

	Matrix m1(2);
	m1[0][0] = 34;
	m1[0][1] = 123;
	m1[1][0] = -25;
	m1[1][1] = 67;

	Matrix m2 = m1+m1+3*m1;
	Matrix m3(2);
	m3[0][0] = 5*34;
	m3[0][1] = 5*123;
	m3[1][0] = 5*(-25);
	m3[1][1] = 5*67;

	assertEqualMatrices(m2,m3);
	Matrix m4(2);	
	m4 = m4*5;
	Matrix m5 = m4 * m4 * m4;
	Matrix m6(2);
	m6 = m6*125;
	
	assertEqualMatrices(m5,m6);
}

void test1Dimension()
{
    std::cout << "===== TEST ONE DIMENSION ====="<<std::endl;
	Matrix m1(3);
	Matrix m2(1);

	std::cout << "Multiplication" << std::endl;
	Matrix m7 = m2 * m1;
	Matrix m8 = m1 * m2;
}


};

#endif

