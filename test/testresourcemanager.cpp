#define BOOST_TEST_MODULE resourcemanager

#include <boost/test/included/unit_test.hpp>
#include <resourcemanager.hpp>
#include <resource.hpp>

struct Manager {

    // Test Resource.
    struct TestRes : public snk::Resource {

        int val;

        TestRes()
        : val(0) {}
    
        void reset() { val = 0; }
        
    };

    snk::ResourceManager<TestRes> manager;

    Manager() {}

};

BOOST_FIXTURE_TEST_SUITE(ResourceManagerTests, Manager)

BOOST_AUTO_TEST_CASE(create1) {

    int testVal = 6;
    snk::Handle h = manager.create(); 
    manager.dereference(h).val = testVal; 
    TestRes& r = manager.dereference(h);
    BOOST_CHECK_EQUAL(testVal, r.val);

}

BOOST_AUTO_TEST_CASE(create2) {

    int testVal1 = -9;
    int testVal2 = 109;
    int testVal3 = 43;

    manager.create();
    snk::Handle h1 = manager.create(); 
    manager.create();
    manager.create();
    snk::Handle h2 = manager.create(); 
    manager.create();
    manager.create();
    manager.create();
    snk::Handle h3 = manager.create(); 
    manager.create();
    manager.create();

    manager.dereference(h1).val = testVal1; 
    manager.dereference(h2).val = testVal2; 
    manager.dereference(h3).val = testVal3; 

    TestRes& r1 = manager.dereference(h1);
    TestRes& r2 = manager.dereference(h2);
    TestRes& r3 = manager.dereference(h3);

    BOOST_CHECK_EQUAL(testVal1, r1.val);
    BOOST_CHECK_EQUAL(testVal2, r2.val);
    BOOST_CHECK_EQUAL(testVal3, r3.val);

}

BOOST_AUTO_TEST_CASE(destroy1) {

    snk::Handle h = manager.create(); 
    manager.destroy(h);
    BOOST_CHECK_THROW(manager.dereference(h), snk::SnakeException);

}

BOOST_AUTO_TEST_CASE(destroy2) {

    snk::Handle h = manager.create(); 
    manager.destroy(h);
    BOOST_CHECK_THROW(manager.dereference(h), snk::SnakeException);

}

BOOST_AUTO_TEST_CASE(destroy3) {

    int testVal = 8475;
    snk::Handle h = manager.create(); 
    manager.dereference(h).val = testVal;
    manager.destroy(h);
    h = manager.create(); 

    // check object in pool was indeed reset.
    BOOST_CHECK_EQUAL(0, manager.dereference(h).val);

}

BOOST_AUTO_TEST_CASE(destroy4) {

    int testVal1 = 78;
    int testVal2 = -907;
    int testVal3 = 1;

    snk::Handle d1 = manager.create(); 
    snk::Handle h1 = manager.create(); 
    snk::Handle d2 = manager.create(); 
    manager.destroy(d1);
    snk::Handle h2 = manager.create(); 
    snk::Handle d3 = manager.create();
    snk::Handle d4 = manager.create();
    manager.destroy(d4);
    snk::Handle d5 = manager.create();
    snk::Handle h3 = manager.create(); 
    manager.destroy(d3);
    manager.destroy(d5);
    manager.create();
    manager.create();
    manager.destroy(d2);

    manager.dereference(h1).val = testVal1; 
    manager.dereference(h2).val = testVal2; 
    manager.dereference(h3).val = testVal3; 

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

    manager.create();
    auto it = manager.begin();
    BOOST_CHECK(it != manager.end());
    ++it;
    BOOST_CHECK(it == manager.end());

}

BOOST_AUTO_TEST_CASE(itMovement2) {

    manager.create();
    auto it1 = manager.begin();
    BOOST_CHECK(it1 != manager.end());
    auto it2 = it1++;
    BOOST_CHECK(it1 == manager.end());
    BOOST_CHECK(it2 == manager.begin());

}

BOOST_AUTO_TEST_CASE(itDestruction) {

    snk::Handle h = manager.create();
    BOOST_CHECK(manager.begin() != manager.end());
    manager.destroy(h);
    BOOST_CHECK(manager.begin() == manager.end());

}

BOOST_AUTO_TEST_CASE(itNormal1) {

    int testVal1 = -425;
    int testVal2 = 2965;
    int testVal3 = 9;
    int testVal4 = 123;
    snk::Handle h1 = manager.create();
    snk::Handle h2 = manager.create();
    snk::Handle h3 = manager.create();
    snk::Handle h4 = manager.create();

    manager.dereference(h1).val = testVal1; 
    manager.dereference(h2).val = testVal2; 
    manager.dereference(h3).val = testVal3; 
    manager.dereference(h4).val = testVal4; 

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
    snk::Handle d1 = manager.create();
    snk::Handle d2 = manager.create();
    snk::Handle h1 = manager.create();
    snk::Handle h2 = manager.create();
    snk::Handle d3 = manager.create();
    snk::Handle h3 = manager.create();
    snk::Handle d4 = manager.create();
    snk::Handle d5 = manager.create();

    manager.dereference(h1).val = testVal; 
    manager.dereference(h2).val = testVal; 
    manager.dereference(h3).val = testVal; 

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
