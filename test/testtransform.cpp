#define BOOST_TEST_MODULE transform
#define TOLERANCE 0.0001  // Allow tolerance % difference for floating point comparisons.

#include <boost/test/included/unit_test.hpp>
#include <maths/vector.hpp>
#include <maths/transform.hpp>

struct Transforms {

    Transforms() 
    : t(), 
      p1(),
      p2(1.f, 1.f),
      p3(-8.f, 2.f),
      p4(1000.f, 5092.f),
      p5(-19.f, -93.f) {}
    
    snk::Transform t;
    snk::Point2f p1;
    snk::Point2f p2;
    snk::Point2f p3;
    snk::Point2f p4;
    snk::Point2f p5;

};

BOOST_FIXTURE_TEST_SUITE(TransformTests, Transforms)

// No transform.
BOOST_AUTO_TEST_CASE(noTransform) {

    snk::Point2f transformed = t * p3;

    BOOST_CHECK_CLOSE(p3.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(p3.y, transformed.y, TOLERANCE);

}

// Scale.
BOOST_AUTO_TEST_CASE(scale1) {

    snk::Point2f expected(105.f, 0.f);
    t.scale(105.f, 0.f);
    snk::Point2f transformed = t * p2;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(scale2) {

    snk::Point2f expected(3000.f, -2546.f);
    t.scale(3, -0.5);
    snk::Point2f transformed = t * p4;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(scale3) {

    snk::Point2f expected(16.53f, 80.91f);
    t.scale(-0.87, -0.87);
    snk::Point2f transformed = t * p5;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(scale4) {

    t.scale(0.3948787f, 239847.f);
    snk::Point2f transformed = t * p1;

    BOOST_CHECK_CLOSE(p1.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(p1.y, transformed.y, TOLERANCE);

}

// Uniform Scale.
BOOST_AUTO_TEST_CASE(uniformScale1) {

    snk::Point2f expected(100.f, 100.f);
    t.scale(100);
    snk::Point2f transformed = t * p2;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(uniformScale2) {

    snk::Point2f expected(16.53f, 80.91f);
    t.scale(-0.87);
    snk::Point2f transformed = t * p5;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

// Rotate.
BOOST_AUTO_TEST_CASE(rotate1) {

    snk::Point2f expected(-1.f, 1.f);
    t.rotate(90);
    snk::Point2f transformed = t * p2;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(rotate2) {

    t.rotate(-178.232f);
    snk::Point2f transformed = t * p1;

    BOOST_CHECK_CLOSE(p1.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(p1.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(rotate3) {

    t.rotate(360);
    snk::Point2f transformed = t * p4;

    BOOST_CHECK_CLOSE(p4.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(p4.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(rotate4) {

    snk::Point2f expected(77.321564f, 55.057934f);
    t.rotate(-223.f);
    snk::Point2f transformed = t * p5;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

// Translate.
BOOST_AUTO_TEST_CASE(translate1) {

    snk::Point2f expected(100.f, -20.f);
    t.translate(100.f, -20.f);
    snk::Point2f transformed = t * p1;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

BOOST_AUTO_TEST_CASE(translate2) {

    snk::Point2f expected(7.2f, 4.f);
    snk::Vector2f move(15.2f, 2.f);
    t.translate(move);
    snk::Point2f transformed = t * p3;

    BOOST_CHECK_CLOSE(expected.x, transformed.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed.y, TOLERANCE);

}

// Compound transformations.
BOOST_AUTO_TEST_CASE(compound1) {

    snk::Point2f expected(-43.395481f, 55.550556f);

    float scaleX = 2.f;
    float scaleY = -0.5f;
    float angle = 169.f;
    snk::Vector2f move(-0.9f, 112.2f);

    snk::Transform scaler;
    scaler.scale(scaleX, scaleY);

    snk::Transform rotater;
    rotater.rotate(angle);

    snk::Transform translater;
    translater.translate(move);

    t.scale(scaleX, scaleY).rotate(angle).translate(move);
    snk::Point2f transformed1 = scaler * rotater * translater * p2;
    snk::Point2f transformed2 = t * p2;

    BOOST_CHECK_CLOSE(expected.x, transformed1.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed1.y, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.x, transformed2.x, TOLERANCE);
    BOOST_CHECK_CLOSE(expected.y, transformed2.y, TOLERANCE);

}

// Transform data initialisation.
BOOST_AUTO_TEST_CASE(dataInit1) {

    snk::Transform::TData initData;
    initData.origin = {15.f, -0.9f};
    initData.angle = 189.f;
    initData.scale= {-6.4f, -2.f};
    initData.translation = {1.f, 101.f};

    t.translate(initData.translation);
    t.rotate(initData.angle);
    t.scale(initData.scale);
    t.translate(-initData.origin);
    snk::Transform t2(initData);

    snk::Point2f transformed1 = t * p3;
    snk::Point2f transformed2 = t2 * p3;

    BOOST_CHECK_CLOSE(transformed1.x, transformed2.x, TOLERANCE);
    BOOST_CHECK_CLOSE(transformed1.y, transformed2.y, TOLERANCE);

}


BOOST_AUTO_TEST_SUITE_END()
