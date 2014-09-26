#include <cxxtest/TestSuite.h>

#include "count_if_followed_by.h"


class MyTestSuite : public CxxTest::TestSuite {
public:
    void test1 () {
        char const  data[6] = {'G','G','X','G','X','G'};
        int  const test_len = 4;

        int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

        // SYNOPSIS:
        //   result should be 1 since the length specified is 4,
        //   and only one pair of [X, G] is present in that range!

        TS_ASSERT_EQUALS(result, 1);
    }
    void test2 () {
        char const  data[6] = {'G','X','G','X','G','G'};
        int  const test_len = 5;

        int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

        // SYNOPSIS:
        //   result should be 2 since there are two sequences in [data[0], data[5])

        TS_ASSERT_EQUALS(result, 2);
    }

    void test3 () {
        char const  data[6] = {'G','G','X','G','X','G'};
        int  const test_len = 5;

        int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

        // SYNOPSIS:
        //   result should be 1 since there is only one 'XG' pair in the range
	// [data[0], data[5])

        TS_ASSERT_EQUALS(result, 1);
    }

    void test4(){
        char const  data[6] = {'X','G'};
        int  const test_len = 1;

        int  const   result = count_if_followed_by (data, test_len, 'X', 'G');

        // SYNOPSIS:
	// The result should be 0 since it should only analyze the first character

        TS_ASSERT_EQUALS(result, 0);
    }


};
