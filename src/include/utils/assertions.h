#include <assert.h>
#include <string.h>

// Help text for assertions
#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

// Float / Double Constants and Comparisons
#define EPSILON               0.00001
#define FLOAT_EQUAL(a, b)     (fabs((a) - (b)) < EPSILON)
#define FLOAT_NOT_EQUAL(a, b) (fabs((a) - (b)) >= EPSILON)

// ASSERTIONS
#define ASSERT_NOT_NULL(ptr) assert((ptr) != NULL)

#define ASSERT_STRING_EQUAL(str1, str2)     assert(strcmp(str1, str2) == 0)
#define ASSERT_STRING_NOT_EQUAL(str1, str2) assert(strcmp(str1, str2) != 0)

#define ASSERT_INT_EQUAL(a, b)     assert((a) == (b))
#define ASSERT_INT_NOT_EQUAL(a, b) assert((a) != (b))

#define ASSERT_INT_GREATER_THAN(a, b) assert((a) > (b))
#define ASSERT_INT_LESS_THAN(a, b)    assert((a) < (b))

#define ASSERT_TRUE(a)  assert(a)
#define ASSERT_FALSE(a) assert(!(a))

#define ASSERT_FLOAT_EQUAL(a, b) assert(FLOAT_EQUAL(a, b))
