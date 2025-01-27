#include <Hello.hpp>
#include <catch2/catch_test_macros.hpp>

TEST_CASE("Hello") {
    Hello h;
    REQUIRE(h.hi() == "Hello World");
}