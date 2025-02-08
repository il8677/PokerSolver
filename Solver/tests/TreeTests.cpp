#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include <TreeNode.hpp>

SCENARIO("Tree children management") {
	GIVEN("A tree node") {
		TreeNode node;
		THEN("It starts with no children") {
			REQUIRE(node.getChildCount() == 0);
		}
	}
}
