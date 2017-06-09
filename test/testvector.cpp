#include "vector.hpp"
#include <boost/test/included/unit_test.hpp>

#define BOOST_TEST_MODULE MyTest

struct Vectors {

    Vectors() 
    : v1(),
      v2(1, 1),
      v3(-8, 2),
      v4(1000, 5092),
      v5(-19, -93) {}

    Vector2di v1;
    Vector2di v2;
    Vector2di v3;
    Vector2di v4;
    Vector2di v5;

};

BOOST_FIXTURE_TEST_SUITE(VectorTests, Vectors)


// Unary operations.
// - tests.
BOOST_AUTO_TEST_CASE(unaryMinus1) {

    Vector2di expected(8, -2);
    Vector2di negated3(-v3);
    
    BOOST_CHECK_EQUAL(expected.x, negated3.x);
    BOOST_CHECK_EQUAL(expected.y, negated3.y);

}


BOOST_AUTO_TEST_CASE(unaryMinus2) {

    Vector2di negated1(-v1);

    BOOST_CHECK_EQUAL(v1.x, negated1.x);
    BOOST_CHECK_EQUAL(v1.y, negated1.y);

}

// Binary operations.
// + tests.
BOOST_AUTO_TEST_CASE(binaryAdd1) {

    Vector2di expected(-7, 3);
    Vector2di added(v2 + v3);
    
    BOOST_CHECK_EQUAL(expected.x, added.x);
    BOOST_CHECK_EQUAL(expected.y, added.y);

}

BOOST_AUTO_TEST_CASE(binaryAdd2) {

    Vector2di expected(981, 4999);
    Vector2di added(v4 + v5);
    
    BOOST_CHECK_EQUAL(expected.x, added.x);
    BOOST_CHECK_EQUAL(expected.y, added.y);

}

BOOST_AUTO_TEST_CASE(binaryAdd3) {

    Vector2di expected(0, 0);
    Vector2di added(v1 + v1);
    
    BOOST_CHECK_EQUAL(expected.x, added.x);
    BOOST_CHECK_EQUAL(expected.y, added.y);

}

// - tests.
BOOST_AUTO_TEST_CASE(binarySubtract1) {

    Vector2di expected(-9, 1);
    Vector2di subtracted(v3 - v2);
    
    BOOST_CHECK_EQUAL(expected.x, subtracted.x);
    BOOST_CHECK_EQUAL(expected.y, subtracted.y);

}

BOOST_AUTO_TEST_CASE(binarySubtract2) {

    Vector2di expected(0, 0);
    Vector2di subtracted(v4 - v4);
    
    BOOST_CHECK_EQUAL(expected.x, subtracted.x);
    BOOST_CHECK_EQUAL(expected.y, subtracted.y);

}

BOOST_AUTO_TEST_CASE(binarySubtract3) {

    Vector2di expected(-19, -93);
    Vector2di subtracted(v5 - v1);
    
    BOOST_CHECK_EQUAL(expected.x, subtracted.x);
    BOOST_CHECK_EQUAL(expected.y, subtracted.y);

}

// * tests.
BOOST_AUTO_TEST_CASE(binaryMultiply1) {

    Vector2di expected(-48, 12);
    int multiplier = 6;
    Vector2di multipliedr(v3 * multiplier);
    Vector2di multipliedl(multiplier * v3);
    
    BOOST_CHECK_EQUAL(expected.x, multipliedr.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedr.y);
    BOOST_CHECK_EQUAL(expected.x, multipliedl.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedl.y);

}

BOOST_AUTO_TEST_CASE(binaryMultiply2) {

    Vector2di expected(3000, 15276);
    int multiplier = 3;
    Vector2di multipliedr(v4 * multiplier);
    Vector2di multipliedl(multiplier * v4);
    
    BOOST_CHECK_EQUAL(expected.x, multipliedr.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedr.y);
    BOOST_CHECK_EQUAL(expected.x, multipliedl.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedl.y);

}

BOOST_AUTO_TEST_CASE(binaryMultiply3) {

    Vector2di expected(0, 0);
    int multiplier = 0;
    Vector2di multipliedr(v5 * multiplier);
    Vector2di multipliedl(multiplier * v5);
    
    BOOST_CHECK_EQUAL(expected.x, multipliedr.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedr.y);
    BOOST_CHECK_EQUAL(expected.x, multipliedl.x);
    BOOST_CHECK_EQUAL(expected.y, multipliedl.y);

}

// / tests.
BOOST_AUTO_TEST_CASE(binaryDivide1) {

    Vector2di expected(-4, 1);
    Vector2di divided(v3 / 2);
    
    BOOST_CHECK_EQUAL(expected.x, divided.x);
    BOOST_CHECK_EQUAL(expected.y, divided.y);

}

BOOST_AUTO_TEST_CASE(binaryDivide2) {

    Vector2di expected(125, 636);
    Vector2di divided(v4 / 8);
    
    BOOST_CHECK_EQUAL(expected.x, divided.x);
    BOOST_CHECK_EQUAL(expected.y, divided.y);

}

BOOST_AUTO_TEST_CASE(binaryDivide3) {

    Vector2di expected(-19, -93);
    Vector2di divided(v5 / 1);
    
    BOOST_CHECK_EQUAL(expected.x, divided.x);
    BOOST_CHECK_EQUAL(expected.y, divided.y);

}

// Compound operations.
// += tests.
BOOST_AUTO_TEST_CASE(compoundAdd1) {

    Vector2di expected(1001, 5093);
    v2 += v4;
    
    BOOST_CHECK_EQUAL(expected.x, v2.x);
    BOOST_CHECK_EQUAL(expected.y, v2.y);

}

BOOST_AUTO_TEST_CASE(compoundAdd2) {

    Vector2di expected(2, 2);
    v2 += v2;
    
    BOOST_CHECK_EQUAL(expected.x, v2.x);
    BOOST_CHECK_EQUAL(expected.y, v2.y);

}

BOOST_AUTO_TEST_CASE(compoundAdd3) {

    Vector2di expected(0, 0);
    v1 += v1;
    
    BOOST_CHECK_EQUAL(expected.x, v1.x);
    BOOST_CHECK_EQUAL(expected.y, v1.y);

}

// -= tests.
BOOST_AUTO_TEST_CASE(compoundSubtract1) {

    Vector2di expected(1008, 5090);
    v4 -= v3;
    
    BOOST_CHECK_EQUAL(expected.x, v4.x);
    BOOST_CHECK_EQUAL(expected.y, v4.y);

}

BOOST_AUTO_TEST_CASE(compoundSubtract2) {

    Vector2di expected(0, 0);
    v5 -= v5;
    
    BOOST_CHECK_EQUAL(expected.x, v5.x);
    BOOST_CHECK_EQUAL(expected.y, v5.y);

}

BOOST_AUTO_TEST_CASE(compoundSubtract3) {

    Vector2di expected(0, 0);
    v1 -= v1;
    
    BOOST_CHECK_EQUAL(expected.x, v1.x);
    BOOST_CHECK_EQUAL(expected.y, v1.y);

}

// *= tests.
BOOST_AUTO_TEST_CASE(compoundMultiply1) {

    Vector2di expected(-24, 6);
    v3 *= 3;
    
    BOOST_CHECK_EQUAL(expected.x, v3.x);
    BOOST_CHECK_EQUAL(expected.y, v3.y);

}

BOOST_AUTO_TEST_CASE(compoundMultiply2) {

    Vector2di expected(10000, 50920);
    v4 *= 10;
    
    BOOST_CHECK_EQUAL(expected.x, v4.x);
    BOOST_CHECK_EQUAL(expected.y, v4.y);

}

BOOST_AUTO_TEST_CASE(compoundMultiply3) {

    Vector2di expected(0, 0);
    v1 *= 982347;
    
    BOOST_CHECK_EQUAL(expected.x, v1.x);
    BOOST_CHECK_EQUAL(expected.y, v1.y);

}

// /= tests.
BOOST_AUTO_TEST_CASE(compoundDivide1) {

    Vector2di expected(-4, 1);
    v3 /= 2;
    
    BOOST_CHECK_EQUAL(expected.x, v3.x);
    BOOST_CHECK_EQUAL(expected.y, v3.y);

}

BOOST_AUTO_TEST_CASE(compoundDivide2) {

    Vector2di expected(125, 636);
    v4 /= 8;
    
    BOOST_CHECK_EQUAL(expected.x, v4.x);
    BOOST_CHECK_EQUAL(expected.y, v4.y);

}

BOOST_AUTO_TEST_CASE(compoundDivide3) {

    Vector2di expected(-19, -93);
    v5 /= 1;
    
    BOOST_CHECK_EQUAL(expected.x, v5.x);
    BOOST_CHECK_EQUAL(expected.y, v5.y);

}


// Comparison operations.
// == tests.

BOOST_AUTO_TEST_CASE(equal1) {

    BOOST_CHECK(v1 == v1);

}

BOOST_AUTO_TEST_CASE(equal2) {

    Vector2di v(-19, -93);

    BOOST_CHECK(v5 == v);

}

BOOST_AUTO_TEST_CASE(equal3) {

    BOOST_CHECK(!(v5 == v4));

}

// != tests.
BOOST_AUTO_TEST_CASE(notEqual1) {

    BOOST_CHECK(v1 != v2);

}

BOOST_AUTO_TEST_CASE(notEqual2) {

    BOOST_CHECK(v3 != v4);

}

BOOST_AUTO_TEST_CASE(notEqual3) {

    BOOST_CHECK(!(v5 != v5));

}

// Utility functions.
// Dot product.
BOOST_AUTO_TEST_CASE(dot1) {

    int expected = -34;
    BOOST_CHECK_EQUAL(expected, dot(v3, v5));

}

BOOST_AUTO_TEST_CASE(dot2) {

    int expected = 0;
    BOOST_CHECK_EQUAL(expected, dot(v1, v2));

}

// Magnitude.
BOOST_AUTO_TEST_CASE(magnitude1) {

    int expected = 0;
    BOOST_CHECK_EQUAL(expected, magnitude(v1));

}

BOOST_AUTO_TEST_CASE(magnitude2) {

    int expected = 94;
    BOOST_CHECK_EQUAL(expected, magnitude(v5));

}

BOOST_AUTO_TEST_SUITE_END()
