/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "example_test.h"

static MatrixTestSuite suite_MatrixTestSuite;

static CxxTest::List Tests_MatrixTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MatrixTestSuite( "example_test.h", 12, "MatrixTestSuite", suite_MatrixTestSuite, Tests_MatrixTestSuite );

static class TestDescription_MatrixTestSuite_testConstructors : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testConstructors() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 74, "testConstructors" ) {}
 void runTest() { suite_MatrixTestSuite.testConstructors(); }
} testDescription_MatrixTestSuite_testConstructors;

static class TestDescription_MatrixTestSuite_testAssignment : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testAssignment() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 100, "testAssignment" ) {}
 void runTest() { suite_MatrixTestSuite.testAssignment(); }
} testDescription_MatrixTestSuite_testAssignment;

static class TestDescription_MatrixTestSuite_testArithmetics : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testArithmetics() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 119, "testArithmetics" ) {}
 void runTest() { suite_MatrixTestSuite.testArithmetics(); }
} testDescription_MatrixTestSuite_testArithmetics;

static class TestDescription_MatrixTestSuite_testTranspose : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testTranspose() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 180, "testTranspose" ) {}
 void runTest() { suite_MatrixTestSuite.testTranspose(); }
} testDescription_MatrixTestSuite_testTranspose;

static class TestDescription_MatrixTestSuite_testDimensions : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testDimensions() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 199, "testDimensions" ) {}
 void runTest() { suite_MatrixTestSuite.testDimensions(); }
} testDescription_MatrixTestSuite_testDimensions;

static class TestDescription_MatrixTestSuite_testIndexOperator : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testIndexOperator() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 230, "testIndexOperator" ) {}
 void runTest() { suite_MatrixTestSuite.testIndexOperator(); }
} testDescription_MatrixTestSuite_testIndexOperator;

static class TestDescription_MatrixTestSuite_testIndex : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testIndex() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 247, "testIndex" ) {}
 void runTest() { suite_MatrixTestSuite.testIndex(); }
} testDescription_MatrixTestSuite_testIndex;

static class TestDescription_MatrixTestSuite_testInput : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testInput() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 260, "testInput" ) {}
 void runTest() { suite_MatrixTestSuite.testInput(); }
} testDescription_MatrixTestSuite_testInput;

static class TestDescription_MatrixTestSuite_test59 : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test59() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 269, "test59" ) {}
 void runTest() { suite_MatrixTestSuite.test59(); }
} testDescription_MatrixTestSuite_test59;

static class TestDescription_MatrixTestSuite_testNegativeDimensions : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testNegativeDimensions() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 291, "testNegativeDimensions" ) {}
 void runTest() { suite_MatrixTestSuite.testNegativeDimensions(); }
} testDescription_MatrixTestSuite_testNegativeDimensions;

static class TestDescription_MatrixTestSuite_testOutput : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testOutput() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 312, "testOutput" ) {}
 void runTest() { suite_MatrixTestSuite.testOutput(); }
} testDescription_MatrixTestSuite_testOutput;

static class TestDescription_MatrixTestSuite_testChain : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_testChain() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 332, "testChain" ) {}
 void runTest() { suite_MatrixTestSuite.testChain(); }
} testDescription_MatrixTestSuite_testChain;

static class TestDescription_MatrixTestSuite_test1Dimension : public CxxTest::RealTestDescription {
public:
 TestDescription_MatrixTestSuite_test1Dimension() : CxxTest::RealTestDescription( Tests_MatrixTestSuite, suiteDescription_MatrixTestSuite, 359, "test1Dimension" ) {}
 void runTest() { suite_MatrixTestSuite.test1Dimension(); }
} testDescription_MatrixTestSuite_test1Dimension;

#include <cxxtest/Root.cpp>
