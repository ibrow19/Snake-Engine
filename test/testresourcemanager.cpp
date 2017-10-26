#define BOOST_TEST_MODULE resourcemanager

#include <boost/test/included/unit_test.hpp>
#include <snk/resource/resourcemanager.hpp>
#include <snk/resource/resource.hpp>

// Handle tag.
struct TestTag {};

typedef snk::Handle<TestTag> TestHandle;

struct Manager {

    // Test Resource.
    struct TestRes : public snk::Resource {

        int val;

        TestRes()
        : val(0) {}
    
        void reset() { val = 0; }
        
    };

    snk::ResourceManager<TestRes, TestTag> manager;

    Manager() {}

};

BOOST_FIXTURE_TEST_SUITE(ResourceManagerTests, Manager)

BOOST_AUTO_TEST_CASE(create1) {

    int testVal = 6;
    TestHandle h;
    TestRes& a = manager.create(h); 
    a.val = testVal; 
    TestRes& r = manager.dereference(h);
    BOOST_CHECK_EQUAL(testVal, r.val);

}

BOOST_AUTO_TEST_CASE(create2) {

    int testVal1 = -9;
    int testVal2 = 109;
    int testVal3 = 43;

    TestHandle dummy;
    TestHandle h1;
    TestHandle h2;
    TestHandle h3;

    manager.create(dummy);
    TestRes& a1 = manager.create(h1); 
    a1.val = testVal1; 
    manager.create(dummy);
    manager.create(dummy);
    TestRes& a2 = manager.create(h2); 
    a2.val = testVal2; 
    manager.create(dummy);
    manager.create(dummy);
    manager.create(dummy);
    TestRes& a3 = manager.create(h3); 
    a3.val = testVal3; 
    manager.create(dummy);
    manager.create(dummy);

    TestRes& r1 = manager.dereference(h1);
    TestRes& r2 = manager.dereference(h2);
    TestRes& r3 = manager.dereference(h3);

    BOOST_CHECK_EQUAL(testVal1, r1.val);
    BOOST_CHECK_EQUAL(testVal2, r2.val);
    BOOST_CHECK_EQUAL(testVal3, r3.val);

}

BOOST_AUTO_TEST_CASE(destroy1) {

    TestHandle h;
    manager.create(h); 
    manager.destroy(h);
    BOOST_CHECK_THROW(manager.dereference(h), snk::SnakeException);
    BOOST_CHECK_THROW(manager.checkDestroy(h), snk::SnakeException);

}

BOOST_AUTO_TEST_CASE(destroy2) {

    TestHandle h(143827, 21387);
    BOOST_CHECK_THROW(manager.dereference(h), snk::SnakeException);
    BOOST_CHECK_THROW(manager.checkDestroy(h), snk::SnakeException);

}

BOOST_AUTO_TEST_CASE(destroy3) {

    int testVal = 8475;
    TestHandle h;
    TestRes& r = manager.create(h); 
    r.val = testVal;
    manager.destroy(h);
    manager.create(h); 

    // check object in pool was indeed reset.
    BOOST_CHECK_EQUAL(0, manager.dereference(h).val);

}

BOOST_AUTO_TEST_CASE(destroy4) {

    int testVal1 = 78;
    int testVal2 = -907;
    int testVal3 = 1;

    TestHandle dummy;
    TestHandle h1;
    TestHandle h2;
    TestHandle h3;
    TestHandle d1;
    TestHandle d2;
    TestHandle d3;
    TestHandle d4;
    TestHandle d5;

    manager.create(d1); 
    TestRes& a1 = manager.create(h1); 
    a1.val = testVal1; 
    manager.create(d2); 
    manager.destroy(d1);
    TestRes& a2 = manager.create(h2); 
    a2.val = testVal2; 
    manager.create(d3);
    manager.create(d4);
    manager.destroy(d4);
    manager.create(d5);
    TestRes& a3 = manager.create(h3); 
    a3.val = testVal3; 
    manager.destroy(d3);
    manager.destroy(d5);
    manager.create(dummy);
    manager.create(dummy);
    manager.destroy(d2);

    TestRes& r1 = manager.dereference(h1);
    TestRes& r2 = manager.dereference(h2);
    TestRes& r3 = manager.dereference(h3);

    BOOST_CHECK_EQUAL(testVal1, r1.val);
    BOOST_CHECK_EQUAL(testVal2, r2.val);
    BOOST_CHECK_EQUAL(testVal3, r3.val);
    BOOST_CHECK_THROW(manager.dereference(d1), snk::SnakeException);
    BOOST_CHECK_THROW(manager.dereference(d2), snk::SnakeException);
    BOOST_CHECK_THROW(manager.dereference(d3), snk::SnakeException);
    BOOST_CHECK_THROW(manager.dereference(d4), snk::SnakeException);
    BOOST_CHECK_THROW(manager.dereference(d5), snk::SnakeException);

}

// Iterator tests.
BOOST_AUTO_TEST_CASE(itBounds) {

    BOOST_CHECK(manager.begin() == manager.end());

}

BOOST_AUTO_TEST_CASE(itMovement1) {

    TestHandle dummy;
    manager.create(dummy);
    auto it = manager.begin();
    BOOST_CHECK(it != manager.end());
    ++it;
    BOOST_CHECK(it == manager.end());

}

BOOST_AUTO_TEST_CASE(itMovement2) {

    TestHandle dummy;
    manager.create(dummy);
    auto it1 = manager.begin();
    BOOST_CHECK(it1 != manager.end());
    auto it2 = it1++;
    BOOST_CHECK(it1 == manager.end());
    BOOST_CHECK(it2 == manager.begin());

}

BOOST_AUTO_TEST_CASE(itDestruction) {

    TestHandle h;
    manager.create(h);
    BOOST_CHECK(manager.begin() != manager.end());
    manager.destroy(h);
    BOOST_CHECK(manager.begin() == manager.end());

}

BOOST_AUTO_TEST_CASE(itNormal1) {

    int testVal1 = -425;
    int testVal2 = 2965;
    int testVal3 = 9;
    int testVal4 = 123;

    TestHandle h1;
    TestHandle h2;
    TestHandle h3;
    TestHandle h4;

    TestRes& a1 = manager.create(h1);
    a1.val = testVal1; 
    TestRes& a2 = manager.create(h2);
    a2.val = testVal2; 
    TestRes& a3 = manager.create(h3);
    a3.val = testVal3; 
    TestRes& a4 = manager.create(h4);
    a4.val = testVal4; 

    int counter = 0;
    for (auto it = manager.begin(); it != manager.end(); ++it) {

        ++counter;
        --(it->val);

    }
    BOOST_CHECK_EQUAL(4, counter);

    TestRes& r1 = manager.dereference(h1);
    TestRes& r2 = manager.dereference(h2);
    TestRes& r3 = manager.dereference(h3);
    TestRes& r4 = manager.dereference(h4);

    BOOST_CHECK_EQUAL(--testVal1, r1.val);
    BOOST_CHECK_EQUAL(--testVal2, r2.val);
    BOOST_CHECK_EQUAL(--testVal3, r3.val);
    BOOST_CHECK_EQUAL(--testVal4, r4.val);

}

BOOST_AUTO_TEST_CASE(itNormal2) {

    int testVal = 97;

    TestHandle h1;
    TestHandle h2;
    TestHandle h3;
    TestHandle d1;
    TestHandle d2;
    TestHandle d3;
    TestHandle d4;
    TestHandle d5;

    manager.create(d1);
    manager.create(d2);
    TestRes& a1 = manager.create(h1);
    a1.val = testVal; 
    TestRes& a2 = manager.create(h2);
    a2.val = testVal; 
    manager.create(d3);
    TestRes& a3 = manager.create(h3);
    a3.val = testVal; 
    manager.create(d4);
    manager.create(d5);

    manager.destroy(d1);
    manager.destroy(d2);
    manager.destroy(d3);
    manager.destroy(d4);
    manager.destroy(d5);

    int counter = 0;
    for (auto it = manager.cbegin(); it != manager.cend(); ++it) {

        // Test * and ->
        const TestRes& r = *it;
        BOOST_CHECK_EQUAL(testVal, r.val);
        BOOST_CHECK_EQUAL(testVal, it->val);
        ++counter;

    }
    BOOST_CHECK_EQUAL(3, counter);

}

BOOST_AUTO_TEST_SUITE_END()
