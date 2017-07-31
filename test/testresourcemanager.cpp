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
    TestRes& r1 = manager.dereference(h); 
    r1.val = testVal;
    TestRes& r2 = manager.dereference(h);

    BOOST_CHECK_EQUAL(testVal, r2.val);

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

    TestRes& a1 = manager.dereference(h1); 
    a1.val = testVal1;
    TestRes& a2 = manager.dereference(h2); 
    a2.val = testVal2;
    TestRes& a3 = manager.dereference(h3); 
    a3.val = testVal3;

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

    TestRes& a1 = manager.dereference(h1); 
    a1.val = testVal1;
    TestRes& a2 = manager.dereference(h2); 
    a2.val = testVal2;
    TestRes& a3 = manager.dereference(h3); 
    a3.val = testVal3;

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

// TODO: Iterator tests.

BOOST_AUTO_TEST_SUITE_END()
