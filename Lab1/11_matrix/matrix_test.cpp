#include "Matrix.h"

void assertEqualMatrices(const Matrix &m1, const Matrix &m2);

void testConstructors();
void testAssigment();
void testArithmetics();
void testTranspose();
//void testIdentity();
void testInput();
void testMultiplicationScalar();
void testForbiddenOperations();

int main()
{
    testConstructors();
    testAssigment();
    testArithmetics();
    testTranspose();
//    testIdentity();
    testInput();
    testForbiddenOperations();

    return 0;
}

void testConstructors()
{
    std::cout << "===== TEST CONSTRUCTORS ====="<<std::endl;
    // ** Default constructor
    Matrix m;
    assert(m.rows() == 0 && m.cols() == 0);
    std::cout << "Default constructor: "<<m.rows()<<"x"<<m.cols()<<std::endl;
    std::cout << "m1\n" << m <<std::endl;

    // ** Row-col constructor
    Matrix m2(2,4);
    assert(m2.rows() == 2  && m2.cols() == 4);
    std::cout << "Row-col constructor: "<<m2.rows()<<"x"<<m2.cols()<<std::endl;
    std::cout << "m2\n"<<m2 << std::endl;

    // ** Copy constructor
    Matrix m3(m2);
    std::cout << "Copy constructor: "<<m3.rows()<<"x"<<m3.cols()<<std::endl;
    assertEqualMatrices(m2,m3);
    std::cout << "m3\n"<<m3<<std::endl;

    // ** Squared matrix
    Matrix m4(5);
    std::cout << "Square matrix constructor: "<<m4.rows()<<"x"<<m4.cols()<<std::endl;
    assert(m4.rows() == 5 && m4.cols() == 5);
    std::cout << "m4\n"<<m4<<std::endl;
}

void testAssigment()
{
    std::cout << "===== TEST ASSIGNMENT ====="<<std::endl;

    Matrix m(2);
    m[0][1] = 7;
    m[1][0] = 43;
    std::cout << "m\n"<<m<<std::endl;

    std::cout << "Assignment"<<std::endl;
    Matrix m2;
    m2 = m;
    assertEqualMatrices(m,m2);
    std::cout <<"m2\n"<<m2<<std::endl;
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
    assert(m3[0][0] == 12 && m3[0][1] == 3 && m3[1][0] == -12 && m3[1][1] == 4);

    // ** Subtract
    Matrix m4 = m1-m2;
    std::cout << "Add: m4 = m1-m2\n" <<m4 << std::endl;
    assert(m4[0][0] == 2 && m4[0][1] == 1 && m4[1][0] == 18 && m4[1][1] == 14);

    // ** Multiply scalar
    Matrix m5 = 3*m1;
    Matrix m6 = m1*6;
    std::cout << "m5 = 3*m1\n" << "m1\n"<<m1<<"\n m5\n"<<m5 <<std::endl;
    std::cout << "m6 = m1*6\n" << "m1\n"<<m1<<"\n m6\n"<<m6 <<std::endl;

    // ** Multiply matrix
    Matrix m7 = m1 * m2;
    std::cout << "m7 = m1 * m2\n" << m7<<std::endl;

    // ** Negation
    Matrix m8 = m1;
    std::cout << "m8\n"<<m8<<std::endl;
    Matrix m9 = -m8;
    std::cout << "m9 = -m8\n"<<m9<<std::endl;
    for(std::size_t i = 0; i < m8.rows(); ++i)
        for(std::size_t j = 0; j < m9.rows(); ++j)
            assert(m8[i][j] == -m9[i][j]);

    // ** Chain
    Matrix m10 = (m1 + m2 + m3 + m4 + m5) * m1 * m2;
    std::cout << "m10 = (m1+m2+m3+m4+m5)*m1*m2 \n"<<m10<<std::endl;

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
            assert(m1[i][j] == m2[j][i]);
}

//void testIdentity()
//{
//    std::cout << "===== TEST IDENTITY====="<<std::endl;

//    Matrix m1(5);
//    std::cout << "m1\n"<<m1<<std::endl;
//    m1.identity();
//    std::cout << "m1 identity\n"<<m1<<std::endl;

//    for(std::size_t i = 0; i < m1.rows(); ++i)
//    {
//        for(std::size_t j = 0; j < m1.cols(); ++j)
//        {
//            if(i == j)
//                assert(m1[i][j] == 1);
//            else
//                assert(m1[i][j] == 0);
//        }
//    }

//}

void testInput()
{
    std::cout << "===== TEST INPUT ===== "<<std::endl;
    std::stringstream stream("  [ 1 -7123 ; 0 2 ; 9 7 ]");
    Matrix m;
    stream >> m;
    std::cout << m;
}

void testForbiddenOperations()
{
    std::cout << "===== TEST FORBIDDEN OPERATIONS ====="<<std::endl;
    // ** Arithmetics different dimensions
    Matrix m1(2);
    Matrix m2(2,3);
    Matrix m3(3,4);

//    Matrix m4 = m1+m2; // Fail, different dimensions
//    Matrix m5 = m1-m2; // Fail, different dimensions
    Matrix m6 = m2*m3; // OK, correct dimensions
//    Matrix m7 = m3*m2; // Fail, incorrect dimensions

    // ** Set identity on rectangular matrix
//    m2.identity();
}

void assertEqualMatrices(const Matrix &m1, const Matrix &m2)
{
    assert(m1.cols() == m2.cols() && m1.rows() == m2.rows());
    for(std::size_t i = 0; i < m1.rows(); ++i)
    {
        for(std::size_t j = 0; j < m1.cols(); ++j)
        {
            assert(m1[i][j] == m2[i][j]);
        }
    }
}
